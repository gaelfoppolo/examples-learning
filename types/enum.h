/**
 *	@file enum.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the Enum and EnumType
 */

#ifndef _ENUM_H_
#define _ENUM_H_

#include "vector.h"

/**
*   @brief Structure that contains an item of the enumeration
*
*	Enumerations are arrays of EnumType, each of which contain an item of the enumeration,
*	caracterized by a unique identifier and his name as a string
*/
typedef struct EnumType {
	/** @brief The unique identifier of the value */
    int id;
    /** @brief The name of this item of the enumeration */
    char* str;
} EnumType;

/**
*   @brief Structure that defines the enumeration type
*/
typedef struct Enum {
	/** @brief Array of each items composing the enumeration */
	Vector(EnumType) enu;
} Enum;

/**
*	@brief Free the EnumType
*	@param enuty A pointer to the EnumType to be freed
*	@param freeItself Boolean to know whether the EnumType is to be freed or not
*/
void freeEnumType(EnumType* enuty, int freeItself);

/**
*	@brief Free the Enum
*	@param enu A pointer to the Enum to be freed
*	@param freeItself Boolean to know whether the Enum is to be freed or not
*/
void freeEnum(Enum* enu, int freeItself);

#endif // _ENUM_H_