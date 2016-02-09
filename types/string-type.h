/**
 *	@file string-type.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the String type and some tools to use it
 */

#ifndef _STRING_TYPE_H_
#define _STRING_TYPE_H_

#include <stdlib.h>

/**
*	@struct String
*   @brief Dynamic string handler
*
*	Allows to work on string an perform additions to the string without having to care about
*	memory management and reallocations
*/
typedef struct String {
	/** @brief The normal, nul terminated char array that represents the string */
	char* str;
	/** @brief The current string length (number of characters in the string) */
	unsigned int length;
	/** @brief Size of the bloc allocated */
	unsigned int availableLength;
} String;

/**
*	@brief Transforms a char* to a string. The char* MUST be a nul terminated array allocated with malloc
*	@param str The original string (the original is used, no copy is performed)
*
*	@return The newly created string structure
*/
String strInit(char* str);

/**
*	@brief Returns the current string length
*	@param str The string of which the length is returned
*
*	@return The length of the string
*/
unsigned int strLength(String* str);

/**
*	@brief Adds a character at the end of the string
*	@param str The string at the end of which the char is added
*	@param c The char to be added
*/
void strPush(String* str, char c);

/**
*	@brief Add a string at the end of the current string
*	@param str The string at the end of which the second string is added
*	@param str2 The string to be added (need to be nul terminated)
*/
void strPushStr(String* str, char* str2);

/**
*	@brief Create a perfect copy of the string given. Used when a malloc created string is needed
*	@param str The original string
*
*	@return A new string created with malloc
*/
char* strDuplicate(char* str);

#endif // _STRING_TYPE_H_
