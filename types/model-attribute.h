/**
 *	@file model-attribute.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the attributes (as defined by the model file)
 */

#ifndef _MODEL_ATTRIB_H_
#define _MODEL_ATTRIB_H_

#include <string.h>

#include "model-type.h"

/**
*	@brief Contains the definition of an attribute and its type
*
*	Each attribute can be of 4 types (signed integer, enumeration item, tree node or leaf, relation)
*	This structure contains the link between an attribute, its name and the type it holds (and 
*	the boundaries of this type (bounds of the interval, possible values of the enumerations, etc...))
*/
typedef struct ModelAttribute {
	/** @brief The definition of the value this attribute can hold */
	ModelType mt;
	/** @brief The name of this attribute, as found in the model file */
	char* name;
} ModelAttribute;

/**
*	@brief Free the ModelAttribute
*	@param ma A pointer to the ModelAttribute to be freed
*	@param freeItself Boolean to know whether the ModelAttribute is to be freed or not
*/
void freeModelAttribute(ModelAttribute* ma, int freeItself);

#endif // _MODEL_ATTRIB_H_