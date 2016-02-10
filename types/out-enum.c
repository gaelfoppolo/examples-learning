/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
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
	// is the size the same? then:
					// all values the same? -> 0
					// at least one different? -> 1
	// is the size smaller? -> 1
	// is the size bigger? -> 0

	int tmp = 0;

	if (vectSize(oenu1.oenu) == vectSize(oenu2.oenu)) {
		for (int i = 0; i < vectSize(oenu1.oenu) && tmp != 0; ++i) {
			tmp += (vectAt(oenu1.oenu, i) == vectAt(oenu2.oenu, i)) ? 0 : 1;
		}
	} else {
		tmp = 1;
	}

	return tmp;
}