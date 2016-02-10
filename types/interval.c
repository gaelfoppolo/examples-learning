/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Structure of our interval - Implementation
 */

#include "interval.h"

void addToInterval(Interval* inter, int x) {
	if(x < inter->min) {
		inter->min = x;
	}
 	else if(inter->max < x)  {
		inter->max = x;
	}
}

int compareInterval(Interval int1, Interval int2) {

	// are interval bounds the same? -> 0
	// are the intervals (max-min) difference the same? -> 1
	// is the interval 2 bigger? -> 0
	// is the interval 2 smaller? -> 1
	int diffI1 = int1.max-int1.min;
	int diffI2 = int2.max-int2.min;
	return (diffI1 == diffI2) ? (((int1.min == int2.min) && (int1.max == int2.max)) ? 0 : 1) : ((diffI1 > diffI2) ? 0 : 1);
	
}
