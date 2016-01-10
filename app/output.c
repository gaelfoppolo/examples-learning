#include "output.h"

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
