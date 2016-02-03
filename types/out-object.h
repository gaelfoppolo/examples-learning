/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our output object
 */

#ifndef _OUTOBJECT_H_
#define _OUTOBJECT_H_

#include "out-attribute.h"

/**
*   @brief All the attributes composing the output object
*   @field name Name of the OutObject
*   @field attributes All the attributes of the object
*	@field relations All the relations of the object
*/
typedef struct __basic_outobject {
	char* name;
	Vector(OutAttribute) attributes;
	Vector(struct __basic_outobject*) relations;
} OutObject;

/**
*	@brief Init the outobject
*	@param oo A pointer to the outobject to init
*/
void initOutObject(OutObject* oo);

/**
*	@brief Free the outobject previously initialized by initOutObject
*	@param oo A pointer to the outobject to free
*/
void freeOutObject(OutObject* oo);

#endif // _OUTOBJECT_H_
