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
	// is the interval int2 smaller? -> 0
	// else: 1

	return (int1.min <= int2.min && int1.max >= int2.max) ? 0 : 1;
	
}
