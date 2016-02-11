/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Convertion tools from structures to human readable strings
 */

#include "output.h"

char* SDEFAULT     =   "\e[0m";
char* SBDEFAULT    =   "\e[1m";
char* SBLACK       =   "\e[0;30m";
char* SRED         =   "\e[0;31m";
char* SGREEN       =   "\e[0;32m";
char* SYELLOW      =   "\e[0;33m";
char* SBLUE        =   "\e[0;34m";
char* SPURPLE      =   "\e[0;35m";
char* SCYAN        =   "\e[0;36m";
char* SWHITE       =   "\e[0;37m";
char* SBBLACK      =   "\e[1;30m";
char* SBRED        =   "\e[1;31m";
char* SBGREEN      =   "\e[1;32m";
char* SBYELLOW     =   "\e[1;33m";
char* SBBLUE       =   "\e[1;34m";
char* SBPURPLE     =   "\e[1;35m";
char* SBCYAN       =   "\e[1;36m";
char* SBWHITE      =   "\e[1;37m";
char* SUBLACK      =   "\e[4;30m";
char* SURED        =   "\e[4;31m";
char* SUGREEN      =   "\e[4;32m";
char* SUYELLOW     =   "\e[4;33m";
char* SUBLUE       =   "\e[4;34m";
char* SUPURPLE     =   "\e[4;35m";
char* SUCYAN       =   "\e[4;36m";
char* SUWHITE      =   "\e[4;37m";
char* SBUBLACK     =   "\e[1;4;30m";
char* SBURED       =   "\e[1;4;31m";
char* SBUGREEN     =   "\e[1;4;32m";
char* SBUYELLOW    =   "\e[1;4;33m";
char* SBUBLUE      =   "\e[1;4;34m";
char* SBUPURPLE    =   "\e[1;4;35m";
char* SBUCYAN      =   "\e[1;4;36m";
char* SBUWHITE     =   "\e[1;4;37m";

// Indicate the max importance of the messages to show to the user (0 : show only critical messages, 1, 2, 3, ... less and less critical messages)
static unsigned int __output_importance_level = 0;

void genOutput(Solution* sol, Model* mdl) {

	ModelAttribute ma;
	OutObject oo, *ooo;
	OutAttribute oa;
	int attributeDisplayed = 0;
	String toDisplay;
	char* tmp;

	for(int i = 0; i < vectSize(sol->outobjects); ++i) {
		
		// get current OutObject
		oo = vectAt(sol->outobjects, i);

		// OO is final (the most accurate)
		if(oo.generalizeBy == NULL) {

			// add name
			output(L0, "%s%s: %s", SBPURPLE, oo.name, SDEFAULT);

			// display attribute name & value
			for (int j = 0; j < vectSize(oo.attributes); ++j) {

				toDisplay = strInit(cPrint(""));

				// get current model attribute data
				ma = vectAt(mdl->ma, j);
				oa = vectAt(oo.attributes, j);

				// add attribute name
				
				if (j != 0 && attributeDisplayed) {
					strPushStr(&toDisplay, ", ");
				}

				attributeDisplayed = 1;

				tmp = cPrint("%s%s%s", SBGREEN, ma.name, SDEFAULT);
				strPushStr(&toDisplay, tmp);	 
				free(tmp);
				tmp = cPrint("(%s", SBCYAN);
				strPushStr(&toDisplay, tmp);
				free(tmp);				  

				switch (ma.mt.type) {
					// attribute is an interval
					case TYPE_INT:
						if (oa.inter.max-oa.inter.min != vectAt(mdl->ma, j).mt.inter.max-vectAt(mdl->ma, j).mt.inter.min) {
							tmp = cPrint("%d ; %d%s", oa.inter.min, oa.inter.max, SDEFAULT);
							strPushStr(&toDisplay, tmp);
							free(tmp);
						} else {
							attributeDisplayed = 0;
						}	
						break;
					// attribute is a list
					case TYPE_ENUM:
						if (vectSize(oa.oenu.oenu) != vectSize(vectAt(mdl->ma, j).mt.enu.enu)) {
							for (int k = 0; k < vectSize(oa.oenu.oenu); ++k) {
								tmp = cPrint("%s%s", getEnumStr(vectAt(oa.oenu.oenu, k), mdl, j), SDEFAULT);
								strPushStr(&toDisplay, tmp);
								free(tmp);
								tmp = cPrint(", %s", SBCYAN);
								if (k+1 < vectSize(oa.oenu.oenu)) strPushStr(&toDisplay, tmp); //output(L0, ", " SBCYAN);
								free(tmp);
							}
						} else {
							attributeDisplayed = 0;							
						}	
						break;
					// attribute is a tree
					case TYPE_TREE:
						if (oa.tree != vectAt(mdl->ma, j).mt.tree.id) {
							tmp = cPrint("%s%s", getTreeStr(oa.tree, mdl, j), SDEFAULT);
							strPushStr(&toDisplay, tmp);
							free(tmp);
						} else {
							attributeDisplayed = 0;
						}	
						break;
				}
				if (attributeDisplayed) {
					strPushStr(&toDisplay, ")");
					output(L0, "%s", toDisplay.str);
				}

				free(toDisplay.str);
			}
			
			// display relations
			for (int j = 0; j < vectSize(oo.relations); ++j) {
				ooo = vectAt(oo.relations, j);
				if (ooo != NULL) {
					while(ooo->generalizeBy != NULL) {
					    ooo = ooo->generalizeBy;
					}
					if (j < vectSize(oo.relations)) output(L0, ", ");
					output(L0, "%s%s%s", SBGREEN, vectAt(mdl->rel, j), SDEFAULT);
					output(L0, "(%s%s%s) ", SBPURPLE, ooo->name, SDEFAULT);
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


void enableColors(unsigned int enable) {
	if(enable) {
		SDEFAULT     =   "\e[0m";
		SBDEFAULT    =   "\e[1m";
		SBLACK       =   "\e[0;30m";
		SRED         =   "\e[0;31m";
		SGREEN       =   "\e[0;32m";
		SYELLOW      =   "\e[0;33m";
		SBLUE        =   "\e[0;34m";
		SPURPLE      =   "\e[0;35m";
		SCYAN        =   "\e[0;36m";
		SWHITE       =   "\e[0;37m";
		SBBLACK      =   "\e[1;30m";
		SBRED        =   "\e[1;31m";
		SBGREEN      =   "\e[1;32m";
		SBYELLOW     =   "\e[1;33m";
		SBBLUE       =   "\e[1;34m";
		SBPURPLE     =   "\e[1;35m";
		SBCYAN       =   "\e[1;36m";
		SBWHITE      =   "\e[1;37m";
		SUBLACK      =   "\e[4;30m";
		SURED        =   "\e[4;31m";
		SUGREEN      =   "\e[4;32m";
		SUYELLOW     =   "\e[4;33m";
		SUBLUE       =   "\e[4;34m";
		SUPURPLE     =   "\e[4;35m";
		SUCYAN       =   "\e[4;36m";
		SUWHITE      =   "\e[4;37m";
		SBUBLACK     =   "\e[1;4;30m";
		SBURED       =   "\e[1;4;31m";
		SBUGREEN     =   "\e[1;4;32m";
		SBUYELLOW    =   "\e[1;4;33m";
		SBUBLUE      =   "\e[1;4;34m";
		SBUPURPLE    =   "\e[1;4;35m";
		SBUCYAN      =   "\e[1;4;36m";
		SBUWHITE     =   "\e[1;4;37m";
	}
	else {
		SDEFAULT     =   "";
		SBDEFAULT    =   "";
		SBLACK       =   "";
		SRED         =   "";
		SGREEN       =   "";
		SYELLOW      =   "";
		SBLUE        =   "";
		SPURPLE      =   "";
		SCYAN        =   "";
		SWHITE       =   "";
		SBBLACK      =   "";
		SBRED        =   "";
		SBGREEN      =   "";
		SBYELLOW     =   "";
		SBBLUE       =   "";
		SBPURPLE     =   "";
		SBCYAN       =   "";
		SBWHITE      =   "";
		SUBLACK      =   "";
		SURED        =   "";
		SUGREEN      =   "";
		SUYELLOW     =   "";
		SUBLUE       =   "";
		SUPURPLE     =   "";
		SUCYAN       =   "";
		SUWHITE      =   "";
		SBUBLACK     =   "";
		SBURED       =   "";
		SBUGREEN     =   "";
		SBUYELLOW    =   "";
		SBUBLUE      =   "";
		SBUPURPLE    =   "";
		SBUCYAN      =   "";
		SBUWHITE     =   "";
	}
}