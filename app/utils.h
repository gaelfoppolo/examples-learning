#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

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
*	@brief Reads a file from the current position and returns the first character not in the set given
*	@param f The file to be read
*	@param chars A nul terminated array of char that contains the set of characters
*
*	@return Returns the first char not in the set found or 0 in case of EOF
*/
char readTrim(FILE* f, char const* chars);

#endif // _UTILS_H_
