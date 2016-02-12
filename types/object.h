/**
 *	@file object.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the objects
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vector.h"
#include "attribute.h"

/**
*   @brief Contains all the attributes and relations that compose an object
*/
typedef struct Object {
	/** 
	*	@brief Array of the attributes of the object.
	*	Each attribute must be at the same index as its definition in the Model
	*/
	Vector(Attribute) attributes;	
	/** 
	*	@brief Array of the relations of the object.
	*	Each relation must be at the same index as its definition in the Model
	*/
	Vector(Attribute) relations;
	/** @brief The name of the object */
	char* name;
	/** @brief the unique identifier of the object */
	unsigned int id;
} Object;

/**
*	@brief Init the object
*	@param obj A pointer to the object to init
*/
void initObject(Object* obj);

/**
*	@brief Free the object previously initialized by initObject
*	@param obj A pointer to the object to free
*	@param freeItself Boolean to know wether the Object is to be freed or not
*/
void freeObject(Object* obj, int freeItself);

#endif // _OBJECT_H_
