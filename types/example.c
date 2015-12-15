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
    vectFree(e->objects);
}