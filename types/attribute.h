/**
 *	@file attribute.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the attributes
 */

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

#include "attribute-types.h"

/**
*	@struct Attribute
*	@brief Represents an attribute and the value it holds
*	
*	This structure holds an attribute of an object. Attributes can hold values of different types
*	(signed integer, item of an enumeration, node or leaf of a tree), each of these types can be
*	represented by an integer (either the true value, or the ID of the real value).
*/
typedef struct Attribute {
	/** @brief The type of the attribute */
    attrType type;
    /** @brief The value of the attribute */
    int value;
} Attribute;

#endif // _ATTRIBUTE_H_
