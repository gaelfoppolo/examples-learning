/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin     PHILIP Bastien
 *
 * @brief Structure of our model type - Implementation
 */

#include "model-type.h"

void freeModelType(ModelType* mt, int freeItself) {
    if (!mt) return;
    
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
