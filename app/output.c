/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Convertion tools from structures to human readable strings
 */

#include "output.h"

// Indicate the max importance of the messages to show to the user (0 : show only critical messages, 1, 2, 3, ... less and less critical messages)
static unsigned int __output_importance_level = 0;

void genOutput(Solution* sol, Model* mdl) {
    // out final string to display

    ModelAttribute ma;
    OutObject oo, *ooo;
    OutAttribute oa;
    int attributeDisplayed;
    String toDisplay;

    for(int i = 0; i < vectSize(sol->outobjects); ++i) {
        
        // get current OutObject
        oo = vectAt(sol->outobjects, i);

        if(oo.specificity != 0) {

            // add name
            output(L0, SBPURPLE "%s: " SDEFAULT, oo.name);

            // display attribute name & value
            for (int j = 0; j < vectSize(oo.attributes); ++j) {

                attributeDisplayed = 1;
                toDisplay = strInit(cPrint(""));

                // get current model attribute data
                ma = vectAt(mdl->ma, j);
                oa = vectAt(oo.attributes, j);

                // add attribute name
                
                if (j != 0) strPushStr(&toDisplay, cPrint(", "));

                strPushStr(&toDisplay, cPrint(SBGREEN "%s" SDEFAULT, ma.name));         
                strPushStr(&toDisplay, cPrint(" (" SBCYAN));                  

                switch (ma.mt.type) {
                    // attribute is an interval
                    case TYPE_INT:
                        strPushStr(&toDisplay, cPrint("%d ; %d" SDEFAULT, oa.inter.min, oa.inter.max));
                        break;
                    // attribute is a list
                    case TYPE_ENUM:
                        for (int k = 0; k < vectSize(oa.oenu.oenu); ++k) {
                            strPushStr(&toDisplay, cPrint("%s" SDEFAULT, getEnumStr(vectAt(oa.oenu.oenu, k), mdl, j)));
                            if (k+1 < vectSize(oa.oenu.oenu)) strPushStr(&toDisplay, cPrint(", " SBCYAN)); //output(L0, ", " SBCYAN);
                        }
                        break;
                    // attribute is a tree
                    case TYPE_TREE:
                        if (oa.tree != 0) {
                            strPushStr(&toDisplay, cPrint("%s" SDEFAULT, getTreeStr(oa.tree, mdl, j)));
                        } else {
                            attributeDisplayed = 0;
                        }    
                        break;
                }
                if (attributeDisplayed) {
                    strPushStr(&toDisplay, cPrint(")"));
                    output(L0, "%s", toDisplay.str);
                }  
            }
            
            // display relations
            for (int j = 0; j < vectSize(oo.relations); ++j) {
            	ooo = vectAt(oo.relations, j);
            	if (ooo != NULL) {
            		if (j+1 < vectSize(oo.relations)) output(L0, ", ");
            		output(L0, SBGREEN "%s " SDEFAULT, vectAt(mdl->rel, j));
                    output(L0, "(" SBPURPLE "%s" SDEFAULT") ", ooo->name);
            	}
            }
            output(L0, "\n");
        }    
    }
}

char* cPrint(const char* fmt, ...) {
	va_list args;
    va_start(args, fmt); // inits the valist

	unsigned long sz = vsnprintf(NULL, 0, fmt, args) + 1; // get the size of the formatted output but does not write it yet
	char* c = (char*)malloc(sizeof(char) * sz);

	va_end(args); // refresh the valist
	va_start(args, fmt);
	vsnprintf(c, sz, fmt, args); // write the formatted output in a string with the right length calculated before

	va_end(args);
	return c;
}

void setOutputImportance(unsigned int level) {
	__output_importance_level = level;
}

unsigned int getOutputImportance() {
    return __output_importance_level;
}

void output(unsigned int level, const char* fmt, ...) {
	// check if the message is important enough to be printed given the current setting value (&7 discard the error bit)
	if((level & 7) > getOutputImportance()) {
		return;
	}

	va_list args;
	va_start(args, fmt);

	vfprintf((level & 8) ? stderr : stdout, fmt, args); // output in error stream if the error bit is set

	va_end(args);
}

unsigned int extractVerbosityFromArg(const char* verbosity) {
	unsigned int value = 0;
	while(*verbosity) {
		if(*(verbosity++) == 'v') {
			++value;
		}
	}

	return value;
}