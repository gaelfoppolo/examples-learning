/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our enumeration model
 */

#ifndef _ENUM_H_
#define _ENUM_H_

#include "vector.h"

/**
*   @brief Structure that contains the enum attributes
*   @field id The unique identifier of the enum
*   @field str String matching the unique id
*/
typedef struct __basic_type_enum {
    int id;
    char* str;
} EnumType;

typedef struct __basic_enum {
	Vector(EnumType) enu;
} Enum;

#endif // _ENUM_H_