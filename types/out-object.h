/**
 *	@file out-object.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the out-objects. Generated when combining multiple objects
 */

#ifndef _OUTOBJECT_H_
#define _OUTOBJECT_H_

#include "out-attribute.h"

/**
*	@struct OutObject
*	@brief Contains all the attributes and relations that compose an outObject
*/
typedef struct OutObject {
	/** @brief Level of specificity of the OutputObject: 0 (duplicate or less specific) and 1 (specific) */
	unsigned char specificity;
	/** 
	*	@brief Array of the attributes of the out object.
	*	Each attribute must be at the same index as its definition in the Model
	*/
	Vector(OutAttribute) attributes;
	/** 
	*	@brief Array of the relations of the out object.
	*	Each relation must be at the same index as its definition in the Model
	*/
	Vector(struct OutObject*) relations;
} OutObject;

/**
*	@brief Init the outobject
*	@param oo A pointer to the outobject to init
*/
void initOutObject(OutObject* oo);

/**
*	@brief Free the outobject previously initialized by initOutObject
*	@param oo A pointer to the outobject to free
*	@param freeItself Boolean to know wether the OutObject is to be freed or not
*/
void freeOutObject(OutObject* oo, int freeItself);

#endif // _OUTOBJECT_H_
