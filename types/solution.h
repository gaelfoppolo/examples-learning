/**
 *	@file solution.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the Solution
 */

#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include "vector.h"
#include "out-object.h"

/**
*   @brief Contains all the possible solutions
*/
typedef struct Solution {
	/** @brief An array of OutObject, each one representing a solution */
    Vector(OutObject) outobjects;
} Solution;

/**
*	@brief Initilialize the Solution
*	@param sol A pointer to the Solution to init
*/
void initSolution(Solution* sol);

/**
*	@brief Free the Solution previously initialized by initSolution
*	@param sol A pointer to the Solution to be freed
*/
void freeSolution(Solution* sol);

#endif // _SOLUTION_H_