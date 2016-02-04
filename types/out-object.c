/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our output object
 */

#include "out-object.h"

void initOutObject(OutObject* oo) {
	vectInit(oo->attributes);
	vectInit(oo->relations);
}

void freeOutObject(OutObject* oo) {
	if(oo->name) {
		free(oo->name);
	}
	for(unsigned int i = 0; i < vectSize(oo->attributes); ++i) {
		if(vectAt(oo->attributes, i).type == TYPE_ENUM) {
			freeOutEnum(&vectAt(oo->attributes, i).oenu);
		}
	}
	vectFree(oo->attributes);
	vectFree(oo->relations);
}
