#include "output.h"

char* genOutput(Solution* sol, Model* mdl) {
	// out final string to display
	String str = strInit(strDuplicate("Solution: "));

	ModelAttribute ma;
	OutObject oo;

	char minSz[20];
	char maxSz[20];

	for(int i = 0; i < vectSize(sol->outobjects); ++i) {
		// get current model attribute data
		ma = vectAt(mdl->ma, i);
		// get current OutObject
		oo = vectAt(sol->outobjects, i);
		// add attribute name
		strPushStr(&str, ma.name);
		//then value
		strPushStr(&str, "(");

		switch (ma.mt.type) {
			case TYPE_INT:
				// get interval value as char*
                snprintf(minSz, 20, "%d", oo.inter.min);
                snprintf(maxSz, 20, "%d", oo.inter.max);
                strPushStr(&str, minSz);
                strPushStr(&str, "-");
                strPushStr(&str, maxSz);
                break;
            case TYPE_ENUM:
            	for (int j = 0; j < vectSize(oo.oenu.oenu); ++j) {
            		strPushStr(&str, getEnumStr(vectAt(oo.oenu.oenu, j), mdl, i));
            		if (j+1 < vectSize(oo.oenu.oenu)) strPushStr(&str, ", ");
            	}
                break;
            case TYPE_TREE:
                strPushStr(&str, getTreeStr(oo.tree, mdl, i));
                break;
		}
		strPushStr(&str, ")");
		if (i+1 < vectSize(sol->outobjects)) strPushStr(&str, ", ");
	}
	strPushStr(&str, "\n");

	return str.str;
}

char* cPrint(const char * fmt, ...) {
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
