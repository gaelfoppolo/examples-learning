/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our solution
 */

#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include "vector.h"
#include "out-object.h"

/**
*   @brief All the attributes composing the object
*   @field attributes The list of the object's attributes
*/
typedef struct __basic_solution {
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