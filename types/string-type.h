#ifndef _STRING_TYPE_H_
#define _STRING_TYPE_H_

/**
*   @brief Dynamic string handler
*   @field str The normal nul terminated char array that represents the string
*	@field length The current string length
*	@field availableLength The current available max length for the string
*/
typedef struct __basic_string {
	char* str;
	unsigned int length;
	unsigned int availableLength;
} String;

/**
*	@brief Transforms a char* to a string. The char* MUST be a nul terminated array
*	@param str The basic C char array
*
*	@return The newly created string
*/
String strInit(char* str);

/**
*	@brief Returns the current string size
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
void strPushStr(String* str, char const* str2);

/**
*	@brief Create a perfect copy of the string given. Used when a malloc created string is needed
*	@param str The original string
*
*	@return A new string created with malloc
*/
char* strDuplicate(char* str);

#endif // _STRING_TYPE_H_
