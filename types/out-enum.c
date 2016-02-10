/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Structure of our output enumeration - Implementation
 */

#include "out-enum.h"

void initOutEnum(OutEnum* oenu) {
	vectInit(oenu->oenu);
}

void freeOutEnum(OutEnum* oenu, int freeItself) {
	vectFree(oenu->oenu);
	if (freeItself) free(oenu);
}

int compareOutEnum(OutEnum oenu1, OutEnum oenu2) {
	
	// is the size the same or oenu2 smaller? then:
		// all values of oenu2 are inside oenu1? -> 0
		// at least one different? -> 1
	// is the size oenu2 bigger? -> 1

	int tmp = 0, index;

	if (vectSize(oenu1.oenu) <= vectSize(oenu2.oenu)) {
		for (int i = 0; i < vectSize(oenu2.oenu); ++i) {
			// check if each oenu2.oenu is inside oenu1.oenu
			vectIndexOf(oenu1.oenu, vectAt(oenu2.oenu, i), index);
			if (index == -1) tmp += 1;
		}
	} else {
		tmp = 1;
	}

	return (tmp == 0) ? 0 : 1;
}