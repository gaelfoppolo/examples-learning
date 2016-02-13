/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "out-attribute.h"

void freeOutAttribute(OutAttribute* oa, int freeItself){
	if(oa->type == TYPE_ENUM) {
		freeOutEnum(&oa->oenu, 0);
	}
	if (freeItself) free(oa);
}