/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our output attribute - Implementation
 */

#include "out-attribute.h"

void freeOutAttribute(OutAttribute* oa, int freeItself){
	if(oa->type == TYPE_ENUM) {
		freeOutEnum(&oa->oenu, 0);
	}
	if (freeItself) free(oa);
}