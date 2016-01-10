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
#include "out-enum.h"

/**
*   @brief All the attributes composing the output object
*   @field union (inter or oenum or tree) The attribute depending on the type
*/
typedef struct __basic_outobject {
    union {
    	Interval inter;
    	OutEnum oenu;
    	int tree;
    };
} OutObject;

#endif // _OUTOBJECT_H_