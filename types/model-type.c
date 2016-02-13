/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "model-type.h"

void freeModelType(ModelType* mt, int freeItself) {
    if (!mt) return;
    
    // free recursively the union depend on type
    switch(mt->type) {
		case TYPE_INT: break;
		case TYPE_ENUM:
			freeEnum(&mt->enu, 0);
			break;
		case TYPE_TREE:
			freeTree(&mt->tree);
			break;
	}

    if (freeItself) free(mt);    
}
