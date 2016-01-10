/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "../types/examples.h"
#include "../types/out-object.h"

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

#endif // _CORE_H_