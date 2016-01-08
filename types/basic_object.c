/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our object - Implementation
 */

#include "basic_object.h"


void initObject(Object* obj) {
	vectInit(obj->attributes);
}

void freeObject(Object* obj) {
	vectFree(obj->attributes);
	free(obj);
}