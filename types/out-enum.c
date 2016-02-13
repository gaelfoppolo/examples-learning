/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "out-enum.h"

void initOutEnum(OutEnum* oenu) {
	vectInit(oenu->oenu);
}

void freeOutEnum(OutEnum* oenu, int freeItself) {
	vectFree(oenu->oenu);
	if (freeItself) free(oenu);
}

int isOutEnumIncludeInAnother(OutEnum oenu1, OutEnum oenu2) {

	int isOutEnumInclude = 1, index;

	// if oenu2 have bigger or equal size that oenu1
	if (vectSize(oenu2.oenu) >= vectSize(oenu1.oenu)) {
		// for each value of oenu1
		// check if each oenu1 value is inside oenu2
		for (int i = 0; i < vectSize(oenu1.oenu) && isOutEnumInclude; ++i) {
			vectIndexOf(oenu2.oenu, vectAt(oenu1.oenu, i), index);
			if (index == -1) isOutEnumInclude = 0;
		}
	// else smaller
	} else {
		isOutEnumInclude = 0;
	}

	return isOutEnumInclude;
}