/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our enumeration model
 */

#ifndef _ENUM_H_
#define _ENUM_H_

/**
*   @brief Structure that contains the enum attributes
*   @field id The unique identifier of the enum
*   @field str String matching the unique id
*/
typedef struct __basic_enum {
    int id;
    char* str;
} Enum;

/**
*	@brief Get the string from the identifier
*	@param id The identifier
*/
char* getString(int id);

/**
*	@brief Get the identifier from the string
*	@param str The string
*/
int getIdentifier(char* str);

#endif // _ENUM_H_