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