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
	/*switch(oo->type) {
		case TYPE_INT:
			free(&oo->inter);
			break;
		case TYPE_ENUM:
			freeOutEnum(&oo->oenu);
			break;
	}
	free(oo);*/
}
