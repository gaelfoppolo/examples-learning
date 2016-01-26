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
		strPushStr(&str, strDuplicate(ma.name));
		//then value
		strPushStr(&str, strDuplicate("("));
		switch (ma.mt.type) {
			case TYPE_INT:
				// get interval value as char*
                snprintf(minSz, 20, "%d", oo.inter.min);
                snprintf(maxSz, 20, "%d", oo.inter.max);
                strPushStr(&str, minSz);
                strPushStr(&str, strDuplicate("-"));
                strPushStr(&str, maxSz);
                break;
            case TYPE_ENUM:
                //
                break;
            case TYPE_TREE:
                //
                break;
		}
		strPushStr(&str, strDuplicate(") "));
	}
	strPushStr(&str, strDuplicate("\n"));

	return str.str;
}

char* cPrint(const char * fmt, va_list args) {
	unsigned long sz = snprintf(NULL, 0, fmt, args);
	char* c = (char*)malloc(sizeof(char) * sz);
	snprintf(c, sz, fmt, args);
	return c;
}
