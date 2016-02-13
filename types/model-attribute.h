/**
 *	@file model-attribute.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the ModelAttribute 
 */

#ifndef _MODEL_ATTRIB_H_
#define _MODEL_ATTRIB_H_

#include "model-type.h"

/**
*	@brief Contains the definition of an attribute and its type
*
*	Each attribute can be of 4 types (integer interval, enumeration item, tree node or leaf and relation)
*	This structure contains the link between an attribute's name and the type it holds (and 
*	the boundaries of this type (bounds of the interval, possible values of the enumerations, etc...))
*/
typedef struct ModelAttribute {
	/** @brief The definition of the value this attribute can hold */
	ModelType mt;
	/** @brief The name of this attribute, as found in the Model */
	char* name;
} ModelAttribute;

/**
*	@brief Free the ModelAttribute
*	@param ma A pointer to the ModelAttribute to be freed
*	@param freeItself Boolean to know whether the ModelAttribute is to be freed or not
*/
void freeModelAttribute(ModelAttribute* ma, int freeItself);

#endif // _MODEL_ATTRIB_H_