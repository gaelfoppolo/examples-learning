/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "object.h"

void initObject(Object* obj) {
	vectInit(obj->attributes);
}

void freeObject(Object* obj, int freeItself) {
	if(!obj) return;

	vectFree(obj->attributes);
	vectFree(obj->relations);
	free(obj->name);
	if (freeItself)	free(obj);
}