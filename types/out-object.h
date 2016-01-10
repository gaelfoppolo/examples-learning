/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our output object
 */

#ifndef _OUTOBJECT_H_
#define _OUTOBJECT_H_

#include "attribute-type.h"
#include "interval.h"
#include "out-enum.h"
#include "tree.h"

/**
*   @brief All the attributes composing the output object
*   @field type The attribute's type
*   @field union (inter or oenum or tree) The attribute depending on the type
*/
typedef struct __basic_outobject {
    attrType id;
    union {
    	Interval inter;
    	OutEnum oenu;
    	Tree tree;
    };
} OutObject;

#endif // _OUTOBJECT_H_