#include "string-type.h"

String strInit(char* str) {
	String s;

	s.str = str;

	char const* begin = str;
	while(*str++);
	s.length = str - begin - 1;
	s.availableLength = s.length + 1;

	s.str[s.length] = '\0';

	return s;
}

unsigned int strLength(String* str) {
	return str->length;
}

void strPush(String* str, char c) {
	if(str->length >= str->availableLength - 1) {
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

	if(str->length + length >= str->availableLength - 1) {
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
