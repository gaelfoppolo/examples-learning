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
#include "out-attribute.h"

/**
*   @brief All the attributes composing the output object
*   @field attributes All the attributes og the object
*	@field relations All the relations of the object
*/
typedef struct __basic_outobject {
	Vector(OutAttribute) attributes;
	Vector(struct __basic_outobject*) relations;
} OutObject;

void freeOutObject(OutObject* oo);

#endif // _OUTOBJECT_H_
