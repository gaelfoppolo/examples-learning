/**
 *	@file out-object.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the OutObject
 */

#ifndef _OUTOBJECT_H_
#define _OUTOBJECT_H_

#include "out-attribute.h"

/**
*	@brief Contains all the attributes and relations that compose an OutObject
*/
typedef struct OutObject {
	/** @brief Name of the out object */
	char* name;
	/** @brief Pointer to the out object that generalize this out object */
	struct OutObject* generalizeBy;
	/** @brief If the OutObject has been disabled during the counter-example step */
	unsigned char disabled;
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
*	@brief Free the OutObject previously initialized by initOutObject
*	@param oo A pointer to the OutObject to free
*	@param freeItself Boolean to know whether the OutObject is to be freed or not
*/
void freeOutObject(OutObject* oo, int freeItself);

/**
*	@brief Test if two OutObject have the same relations
*	@param oo1 A pointer to the first OutObject
*	@param oo2 A pointer to the second OutObject
*	
*	@return 1 if the same, 0 else
*/
int haveSameRelations(OutObject* oo1, OutObject* oo2);

/**
*	@brief Check if one of the relations of @a oo is disabled, recursively
*	@param oo The OutObject to check
*
*	@return Returns 1 if a relation is disabled, 0 otherwise
*/
int haveDisabledRelations(OutObject* oo);

#endif // _OUTOBJECT_H_
