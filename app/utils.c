#include "utils.h"

unsigned int strlength(char const* str) {
	char const* begin = str;
	while(*str++);
	return str - begin - 1;
}

char* concat(char* str1, char const* str2) {
	unsigned int str1l = (str1 == NULL ? 0 : strlength(str1));
	unsigned int str2l = strlength(str2);
	str1 = (char*)realloc(str1, (str1l + str2l + 1) * sizeof(char));
	for(int i = 0, j = str1l; i < str2l; ++i, ++j) {
		str1[j] = str2[i];
	}
	str1[str1l + str2l] = '\0';

	return str1;
}

char readTrim(FILE* f, char const* chars) {
	if(!f) return NULL;

	char current;
	unsigned int i, inSet;
	while((c = fgetc(f))) {
		if(c == EOF) {
			return 0;
		}
		i = 0;
		inSet = 0;
		while(chars[i]) {
			if(chars[i] == c) {
				inSet = 1;
				break;
			}
			++i;
		}
		if(!inSet) {
			return c;
		}
	}
}
