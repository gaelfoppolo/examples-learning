/**
 *	@file interval.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the interval type
 */

#ifndef _INTERVAL_H_
#define _INTERVAL_H_

/**
*	@struct Interval
*   @brief Structure that contains a signed integer interval.
*
*	An Interval represents the interval between a lower and an upper bound
*/
typedef struct Interval {
	/** @brief The lower bound */
    int min;
	/** @brief The upper bound */
    int max;
} Interval;

/**
 * @brief Change the interval (if needed) to contain a new value
 *
 * @param inter The interval to change
 * @param x The integer to add in the interval
 */
void addToInterval(Interval* inter, int x);

/**
 * 	@brief Is int1 include in int2?
 *
 * 	@param int1 First interval
 * 	@param int2 Second interval
 * 	
 * @return 1, int1 include in int2, else 0
 */
int isIntervalIncludeInAnother(Interval int1, Interval int2);

#endif // _INTERVAL_H_
