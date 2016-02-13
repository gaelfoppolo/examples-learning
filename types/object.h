/**
 *	@file object.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the Object
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vector.h"
#include "attribute.h"

/**
*   @brief Contains all the attributes and relations that compose an Object
*/
typedef struct Object {
	/** 
	*	@brief Array of the attributes of the Object.
	*	Each attribute must be at the same index as its definition in the Model
	*/
	Vector(Attribute) attributes;	
	/** 
	*	@brief Array of the relations of the Object.
	*	Each relation must be at the same index as its definition in the Model
	*/
	Vector(Attribute) relations;
	/** @brief The name of the Object */
	char* name;
	/** @brief the unique identifier of the Object */
	unsigned int id;
} Object;

/**
*	@brief Initialize the Object
*	@param obj A pointer to the Object to init
*/
void initObject(Object* obj);

/**
*	@brief Free the Object previously initialized by initObject
*	@param obj A pointer to the Object to be freed
*	@param freeItself Boolean to know whether the Object is to be freed or not
*/
void freeObject(Object* obj, int freeItself);

#endif // _OBJECT_H_
