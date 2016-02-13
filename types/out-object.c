/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "out-object.h"

void initOutObject(OutObject* oo) {
	vectInit(oo->attributes);
	vectInit(oo->relations);
}

void freeOutObject(OutObject* oo, int freeItself) {
	if(oo->name) free(oo->name);

	for(unsigned int i = 0; i < vectSize(oo->attributes); ++i) {
		freeOutAttribute(&vectAt(oo->attributes, i), 0);
	}
	vectFree(oo->attributes);
	vectFree(oo->relations);

	if(freeItself) free(oo);
}

int haveSameRelations(OutObject* oo1, OutObject* oo2) {

	// both null or both not null
	
	int tmp = 0;

	for (int i = 0; i < vectSize(oo1->relations); ++i){
		tmp += ((vectAt(oo1->relations, i) != NULL && vectAt(oo2->relations, i) != NULL) || (vectAt(oo1->relations, i) == NULL && vectAt(oo2->relations, i) == NULL));
	}
	
	// if tmp = vectSize(oo1->relations), all relations the same
	// else at least one different

	return (tmp == vectSize(oo1->relations)) ? 1 : 0;
}

int haveDisabledRelations(OutObject* oo) {
	if(oo->disabled) {
		return 1;
	}
	for(unsigned int i = 0; i < vectSize(oo->relations); ++i) {
		if(vectAt(oo->relations, i)) {
			if(haveDisabledRelations(vectAt(oo->relations, i))) {
				oo->disabled = 1;
				return 1;
			}
		}
	}

	return 0;
}