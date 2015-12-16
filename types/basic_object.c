/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our object - Implementation
 */

#include "basic_object.h"


void initOutObject(OutObject* out) {
	vectInit(out->colors);
}

void freeOutObject(OutObject* out) {
	vectFree(out->colors);
	free(out);
}