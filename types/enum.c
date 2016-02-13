/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "enum.h"

void freeEnumType(EnumType* enuty, int freeItself) {
	if (!enuty) return;
    if (enuty->str) free(enuty->str);
    if (freeItself) free(enuty);
}

void freeEnum(Enum* enu, int freeItself) {
    if (!enu) return;
    
    // free each EnumType of the Enum
    for(unsigned int i = 0; i < vectSize(enu->enu); ++i) {
		freeEnumType(&vectAt(enu->enu, i), 0);
    }
    vectFree(enu->enu);

    if (freeItself) free(enu);    
}
