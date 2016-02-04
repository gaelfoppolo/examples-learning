/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our object
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vector.h"
#include "attribute.h"

/**
*   @brief All the attributes composing the object
*   @field attributes The list of the object's attributes
*	@field relations The list of the object's relations
*	@field name The name of the object
*	@field id Unique identifier of the object
*/
typedef struct __basic_object {
	Vector(Attribute) attributes;
	Vector(Attribute) relations;
	char* name;
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
*	@param freeItself Boolean to know if the object needs to free itself
*/
void freeObject(Object* obj, int freeItself);

#endif // _OBJECT_H_
