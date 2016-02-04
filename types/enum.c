/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin     PHILIP Bastien
 *
 * @brief Structure of our enum - Implementation
 */

#include "enum.h"

void freeEnumType(EnumType* enuty, int freeItself) {
	if (!enuty) return;
    if (enuty->str) free(enuty->str);
    if (freeItself) free(enuty);
}

void freeEnum(Enum* enu, int freeItself) {
    if (!enu) return;
    
    for(int i = 0; i < vectSize(enu->enu); ++i) {
		freeEnumType(&vectAt(enu->enu, i), 0);
    }
    vectFree(enu->enu);

    if (freeItself) free(enu);    
}
