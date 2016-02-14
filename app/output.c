/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
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

void genOutput(Solution* sol, Model* mdl, int recur) {
	// print each object in the solution
	for(int i = 0; i < vectSize(sol->outobjects); ++i) {
		genObjectOutput(&vectAt(sol->outobjects, i), mdl, recur ? 0 : -1);
	}
}

void genObjectOutput(OutObject* oo, Model* m, int recur) {
	ModelAttribute* ma;
	OutObject* ooo;
	OutAttribute* oa;
	int nbOfRelation = 0;
	int printed = 0;

	// check whether the object has been disabled or not and if is not too general
	if(haveDisabledRelations(oo) || oo->generalizeBy != NULL) {
		return;
	}

	if(recur > -1) {
		printNChar(L0, '\t', recur);
	}
	
	// print the name
	output(L0, "%s%s: %s", SBPURPLE, oo->name, SDEFAULT);

	// print attributes
	for(unsigned int i = 0; i < vectSize(oo->attributes); ++i) {
		// the model of the attribute
		ma = &vectAt(m->ma, i);
		// the attribute itself
		oa = &vectAt(oo->attributes, i);

		// check the type of the attribute to print
		switch(ma->mt.type) {
			case TYPE_INT:
				// check if the attribute needs to be printed
				if(oa->inter.max != vectAt(m->ma, i).mt.inter.max 
					|| oa->inter.min != vectAt(m->ma, i).mt.inter.min) {
					// print the separator
					if(printed) {
						output(L0, ", ");
					}
					else {
						printed = 1;
					}
					// print : attrName(min;max)
					output(L0, "%s%s%s(%s%d;%d%s)", SBGREEN, ma->name, SDEFAULT, SBCYAN, oa->inter.min, oa->inter.max, SDEFAULT);
				}
				break;
			case TYPE_ENUM:
				// check if the attribute needs to be printed
				if(vectSize(oa->oenu.oenu) != vectSize(vectAt(m->ma, i).mt.enu.enu)) {
					// print the separator
					if(printed) {
						output(L0, ", ");
					}
					else {
						printed = 1;
					}
					// print attrName(item1, item2, item3, ...)
					output(L0, "%s%s%s(%s", SBGREEN, ma->name, SDEFAULT, SBCYAN);
					for(unsigned int j = 0; j < vectSize(oa->oenu.oenu); ++j) {
						output(L0, "%s%s", getEnumStr(vectAt(oa->oenu.oenu, j), m, i), SDEFAULT);
						// print the ',' only if not last item
						if(j+1 < vectSize(oa->oenu.oenu)) {
							output(L0, ", %s", SBCYAN);
						}
					}
					output(L0, ")");
				}
				break;
			case TYPE_TREE:
				// check if the attribute needs to be printed
				if(oa->tree != vectAt(m->ma, i).mt.tree.id) {
					// print the separator
					if(printed) {
						output(L0, ", ");
					}
					else {
						printed = 1;
					}
					// print attrName(item1, item2, item3, ...)
					output(L0, "%s%s%s(%s%s%s)", SBGREEN, ma->name, SDEFAULT, SBCYAN, getTreeStr(oa->tree, m, i), SDEFAULT);
				}
		}
	}

	//print relations
	for(unsigned int i = 0; i < vectSize(oo->relations); ++i) {
		ooo = vectAt(oo->relations, i);
		// if the relation is defined for this object
		if(ooo != NULL) {			
			nbOfRelation++;
			// retrieve the most specific solution
			while(ooo->generalizeBy != NULL) {
				ooo = ooo->generalizeBy;
			}
			// inline print
			if(recur < 0) {
				if(i < vectSize(oo->relations)) {
					output(L0, ", ");
				}
				output(L0, "%s%s%s", SBYELLOW, vectAt(m->rel, i), SDEFAULT);
				output(L0, "(%s%s%s)", SBPURPLE, ooo->name, SDEFAULT);
			}
			else {
				// print the relation name
				output(L0, "\n");
				printNChar(L0, '\t', recur+1);
				// print the relation name
				output(L0, "%s%s%s:\n", SBYELLOW, vectAt(m->rel, i), SDEFAULT);
				// print the object linked
				genObjectOutput(ooo, m, recur + 1);
			}
		}
	}
	if(recur <= 0 && nbOfRelation <= 1) {
		output(L0, "\n");
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

void printNChar(unsigned int level, char c, unsigned int n) {
	while(n--) {
		output(level, "%c", c);
	}
}