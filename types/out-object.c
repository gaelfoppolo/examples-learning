/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our output object
 */

#include "out-object.h"

void initOutObject(OutObject* oo) {
	vectInit(oo->attributes);
	vectInit(oo->relations);
}

void freeOutObject(OutObject* oo, int freeItself) {
	
	for(unsigned int i = 0; i < vectSize(oo->attributes); ++i) {
		freeOutAttribute(&vectAt(oo->attributes, i), 0);
	}
	vectFree(oo->attributes);
	vectFree(oo->relations);

	if(freeItself) free(oo);
}
