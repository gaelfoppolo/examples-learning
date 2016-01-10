/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our interval - Implementation
 */

#include "interval.h"

void addToInterval(Interval* inter, int x);
	if(x < inter.min) inter.min = x;
 	else if(inter.max < x) inter.max = x;
}