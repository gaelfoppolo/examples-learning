/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Convertion tools from structures to strings
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdlib.h>
#include <stdio.h>

#include "../types/basic_object.h"

/**
*	@brief Returns the length of a string
*	@str The string
*	@return The length of the string
*/
unsigned int strlength(char const* str);

/**
*	@brief Append a string at the end of another
*	@str1 The first string
*	@str2 The string to be appened
*	@return The address of the string
*/
char* concat(char* str1, char const* str2);

/**
*	@brief returns a string that contains the representation of the object in a readable presentation
*	@param out The object grouping the common traits of the other objects int the examples
*	@return A string representing the object in a readable way. Need to be freed by the user
*/
char* stringifyCommonObject(OutObject* out);

#endif // _OUTPUT_H_