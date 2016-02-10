/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Structure of our model attribute - Implementation
 */

#include "model-attribute.h"

void freeModelAttribute(ModelAttribute* ma, int freeItself) {
    if (!ma) return;
    if (ma->name) free(ma->name);
    freeModelType(&ma->mt, 0);
    if (freeItself) free(ma);    
}
