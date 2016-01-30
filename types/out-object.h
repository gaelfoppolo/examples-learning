/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our output object
 */

#ifndef _OUTOBJECT_H_
#define _OUTOBJECT_H_

#include "interval.h"
#include "attribute-types.h"
#include "out-enum.h"

/**
*   @brief All the attributes composing the output object
*   @field union (inter or oenum or tree) The attribute depending on the type
*/
typedef struct __basic_outobject {
    attrType type;
	union {
    	Interval inter;
    	OutEnum oenu;
    	int tree;
    };
} OutObject;

void freeOutObject(OutObject* oo);

#endif // _OUTOBJECT_H_