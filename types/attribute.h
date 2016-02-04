/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our attribute
 */

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

#include "attribute-types.h"

/**
*   @brief Represents an attribute and the value it holds
*   @field type The attribute's type
*   @field value The attribute's value
*/
typedef struct __basic_attribute {
    attrType type;
    int value;
} Attribute;

#endif // _ATTRIBUTE_H_
