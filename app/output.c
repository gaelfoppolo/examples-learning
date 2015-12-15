#include "output.h"

unsigned int strlength(char* str) {
	char* begin = str;
	while(*str++);
	return str - begin - 1;
}

char* concat(char* str1, char* str2) {
	unsigned int str1l = (str1 == NULL ? 0 : strlength(str1));
	unsigned int str2l = strlength(str2);
	str1 = (char*)realloc(str1, (str1l + str2l + 1) * sizeof(char));
	for(int i = 0, j = str1l; i < str2l; ++i, ++j) {
		str1[j] = str2[i];
	}
	str1[str1l + str2l] = '\0';

	return str1;
}

char* stringifyCommonObject(OutObject* out) {
	char* ret = NULL;

	ret = concat(ret, "C1\n\tx:shape(");

	ret = concat(ret, "), color(");

	ret = concat(ret, "), size(");

	ret = concat(ret, ")\n");

	return ret;
}