/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>

#include "../types/model.h"
#include "../types/examples.h"
#include "../types/solution.h"

/**
 * @brief Process examples of a model and produces solution object
 *
 * @param exp Pointer to the structure containing examples and counter examples
 * @param mdl Pointer to the model object containing structure of the model
 *
 * @return An solution object
 */
Solution* genSolution(Model* mdl, Examples* exp);

/**
 * @brief Init the solution with the first object as "base"
 *
 * @param sol Pointer to the empty solution
 * @param o First object of the example to init the solution
 *
 * @return An solution object
 */
Solution* initSol(Solution* sol, Object o);

/**
 * @brief Calculate the number of combinaisons possible for our examples
 *
 * @param exp Pointer to our array of exemple
 *
 * @return The number of combinaisons
 */
int nbCombi(Examples* exp);

/**
 * @brief Init the solution with nbCombi empty OutObject
 *
 * @param sol Pointer to the empty solution
 * @param nbCombi The number of combinaisons possible = size of the array
 * 
 * @return Solution filled
 */
Solution* genEmptySol(Solution* sol, int nbCombi);

#endif // _CORE_H_