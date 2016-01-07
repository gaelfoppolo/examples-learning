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
*   @brief All the attributes of the abstracted value
*   @field type The value's type
*   @field value The value's value
*/
typedef struct __value_abstracted {
    attrType type;
    int value;
} Value;

#endif // _ABSTR_VALUE_H_
