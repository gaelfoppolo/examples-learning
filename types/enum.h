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

#endif // _ENUM_H_