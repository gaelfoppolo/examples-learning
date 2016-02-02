#include "output.h"

// Indicate the max importance of the messages to show to the user (0 : show only critical messages, 1, 2, 3, ... less and less critical messages)
static unsigned int __output_importance_level = 0;

void genOutput(Solution* sol, Model* mdl) {
    // out final string to display

    ModelAttribute ma;
    OutObject oo;
    OutAttribute oa;

    for(int i = 0; i < vectSize(sol->outobjects); ++i) {
        
        // get current OutObject
        oo = vectAt(sol->outobjects, i);

        for (int j = 0; j < vectSize(oo.attributes); ++j) {
            // get current model attribute data
            ma = vectAt(mdl->ma, j);
            oa = vectAt(oo.attributes, j);

            // add attribute name
            printf("%s(", ma.name);

            switch (ma.mt.type) {
                case TYPE_INT:
                    // get interval value as char*
                    printf("%d-%d", oa.inter.min, oa.inter.max);
                    break;
                case TYPE_ENUM:
                    for (int k = 0; k < vectSize(oa.oenu.oenu); ++k) {
                        printf("%s", getEnumStr(vectAt(oa.oenu.oenu, k), mdl, j));
                        if (k+1 < vectSize(oa.oenu.oenu)) printf(", ");
                    }
                    break;
                case TYPE_TREE:
                    printf("%s", getTreeStr(oa.tree, mdl, j));
                    break;
            }
            printf(")");
            if (j+1 < vectSize(oo.attributes)) printf(", ");
        }
        printf("\n");
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

void output(unsigned int level, const char* fmt, ...) {
	// check if the message is important enough to be printed given the current setting value (&7 discard the error bit)
	if((level & 7) > __output_importance_level) {
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