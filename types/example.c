/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "example.h"

void initExample(Example* exp) {
    vectInit(exp->objects);
}

void freeExample(Example* exp, int freeItself) {
	if(!exp) return;

	for(unsigned int i = 0; i < vectSize(exp->objects); ++i) {
		// specify to not free itself
		freeObject(&vectAt(exp->objects, i), 0);
	}
    vectFree(exp->objects);
    if (freeItself) free(exp);
}