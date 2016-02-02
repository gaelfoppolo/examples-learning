/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions used by the example
 */

#include "example.h"

void initExample(Example * e) {
    vectInit(e->objects);
}

void freeExample(Example * e) {
	for(unsigned int i = 0; i < vectSize(e->objects); ++i) {
		free(vectAt(e->objects, i).name);
		vectFree(vectAt(e->objects, i).attributes);
		vectFree(vectAt(e->objects, i).relations);
	}
    vectFree(e->objects);
}