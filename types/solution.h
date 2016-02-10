/**
 *	@file solution.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the solution
 */

#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include "vector.h"
#include "out-object.h"

/**
*	@struct Solution
*   @brief Contains all the possible solutions
*/
typedef struct Solution {
	/** @brief An array of OutObject, each one representing a solution */
    Vector(OutObject) outobjects;
} Solution;

/**
*	@brief Init the solution
*	@param sol A pointer to the solution to init
*/
void initSolution(Solution* sol);

/**
*	@brief Free the solution previously initialized by initSolution
*	@param sol A pointer to the solution to free
*/
void freeSolution(Solution* sol);

#endif // _SOLUTION_H_