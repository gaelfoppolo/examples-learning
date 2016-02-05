/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our interval
 */

#ifndef _INTERVAL_H_
#define _INTERVAL_H_

/**
*   @brief Represents an integer interval
*   @field min Lower bound
*   @field max Upper bound
*/
typedef struct __interval {
    int min;
    int max;
} Interval;

/**
 * @brief Increase the interval to contains x
 *
 * @param inter The interval to increase
 * @param x An integer to add into the interval
 */
void addToInterval(Interval* inter, int x);

#endif // _INTERVAL_H_
