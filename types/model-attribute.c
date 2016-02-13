/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "model-attribute.h"

void freeModelAttribute(ModelAttribute* ma, int freeItself) {
    if (!ma) return;
    if (ma->name) free(ma->name);
    freeModelType(&ma->mt, 0);
    if (freeItself) free(ma);    
}
