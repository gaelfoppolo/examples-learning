
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
void strPushStr(String* str, char* str2);

/**
*	@brief Create a perfect copy of the string given. Used when a malloc created string is needed
*	@param str The original string
*
*	@return A new string created with malloc
*/
char* strDuplicate(char* str);

#endif // _STRING_TYPE_H_


String strInit(char* str) {
	String s;

	s.str = str;

	char const* begin = str;
	while(*str++);
	s.length = str - begin - 1;
	s.availableLength = s.length;

	return s;
}

unsigned int strLength(String* str) {
	return str->length;
}

void strPush(String* str, char c) {
	if(str->length >= str->availableLength) {
		// double the string available size
		if(str->availableLength < 10) str->availableLength = 5;
		str->availableLength = str->availableLength * 2;
		str->str = (char*)realloc(str->str, str->availableLength * sizeof(char));
	}

	str->str[str->length] = c;
	str->str[++str->length] = '\0';
}

void strPushStr(String* str, char* str2) {
	char const* begin = str2;
	char* current = str2;
	while(*current++);
	unsigned int length = str->length + current - begin - 1;

	if(str->length + length >= str->availableLength) {
		if(str->availableLength < 10) str->availableLength = 10;

		while(str->length + length >= str->availableLength) {
			str->availableLength = str->availableLength * 2;
		}

		str->str = (char*)realloc(str->str, str->availableLength * sizeof(char));
	}

	for(unsigned int i = str->length, j = 0; j < length; ++j, ++i) {
		str->str[i] = str2[j];
	}
}

char* strDuplicate(char* str) {
	char* begin = str;
	char* current = str;
	while(*current++);
	unsigned int length = str - begin - 1;

	char* r = (char*)malloc(length * sizeof(char));
	unsigned int i = 0;
	while((r[i++] = *begin++));

	return r;
}


int main(int argc, char const *argv[])
{
	String str = strInit("test");
	strPush(&str, 'c');
	// strPushStr(&str, "har");

	// printf("%s\n", str->str);




	// OutEnum* test = (OutEnum*)malloc(sizeof(OutEnum));
	// initOutEnum(test);

	// int* x = (int *)malloc(sizeof(int));;
	// *x = 10;

	// vectPush(int, test->oenu, 1);
	// vectPush(int, test->oenu, 4);
	// vectPush(int, test->oenu, 12);
	// vectPush(int, test->oenu, 5);

	// vectIndexOf(test->oenu, 12, *x);
	// printf("%d\n", *x);

	// vectIndexOf(test->oenu, 234, *x);
	// printf("%d\n", *x);

	// freeOutEnum(test);
	// free(x);
	return 0;
}