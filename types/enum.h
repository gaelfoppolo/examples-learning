/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our enumeration model
 */

#ifndef _ENUM_H_
#define _ENUM_H_

#include "vector.h"

/**
*   @brief Structure that contains a value of an Enum
*   @field id The unique identifier of the value
*   @field str String matching the unique id
*/
typedef struct __basic_type_enum {
    int id;
    char* str;
} EnumType;

/**
*   @brief Structure that contains the Enum (array of values)
*   @field enum The vector that contains all the values of the Enum
*/
typedef struct __basic_enum {
	Vector(EnumType) enu;
} Enum;

/**
*	@brief Free the EnumType
*	@param enuty A pointer to the EnumType to be free
*	@param freeItself Boolean to know if the EnumType needs to free itself
*/
void freeEnumType(EnumType* enuty, int freeItself);

/**
*	@brief Free the Enum
*	@param enu A pointer to the Enum to be free
*	@param freeItself Boolean to know if the Enum needs to free itself
*/
void freeEnum(Enum* enu, int freeItself);

#endif // _ENUM_H_