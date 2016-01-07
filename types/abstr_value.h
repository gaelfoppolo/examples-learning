/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our values
 */

#ifndef _ABSTR_VALUE_H_
#define _ABSTR_VALUE_H_

#include "attributes_types.h"

/**
*   @brief Represents an attribute and the value it holds
*   @field type The value's type
*   @field value The value's value
*/
typedef struct __attribute{
    attrType type;
    int value;
} Attribute;

#endif // _ABSTR_VALUE_H_
