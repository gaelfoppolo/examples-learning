/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our enumeration - Implementation
 */

#include "out-enum.h"

void initOutEnum(OutEnum* oenu) {
	vectInit(oenu->oenu);
}

void freeOutEnum(OutEnum* oenu) {
	vectFree(oenu->oenu);
}