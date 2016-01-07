#include "output.h"

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

char* stringifyCommonObject(OutObject* out) {
	char* ret = NULL;
	char minSz[20];
	char maxSz[20];
	snprintf(minSz, 20, "%d", out->min); // converts an int to a string - (itoa is not ANSI-C compliant) - safe from bufferoverflow
	snprintf(maxSz, 20, "%d", out->max);

	ret = concat(ret, "C1\n\tx:shape(");
	ret = concat(ret, shapeString[out->shape]);
	ret = concat(ret, "), color(");
	for(unsigned int i = 0; i < vectSize(out->colors); ++i) { // goes through all the color values of the object
		ret = concat(ret, colorString[vectAt(out->colors, i)]);
		if(i < vectSize(out->colors) - 1) {
			ret = concat(ret, ", ");
		}
	}
	ret = concat(ret, "), size(");
	ret = concat(ret, minSz);
	ret = concat(ret, "..");
	ret = concat(ret, maxSz);
	ret = concat(ret, ")\n");

	return ret;
}
