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
 *
 * @return An solution object
 */
Solution* genSolution(Examples* exp);

/**
 * @brief Init the solution with the first object as "base"
 *
 * @param sol Pointer to the empty solution
 * @param o First object of the example to init the solution
 *
 * @return An solution object
 */
Solution* initSol(Solution* sol, Object o) {


/**
 * @brief Increase the range [min, max] to contains x
 *
 * @param min Minimum bound
 * @param max Maximum bound
 * @param[in] x An integer to add into the range
 */
void addToInterval(int *min, int*max, int x);

/**
 * @brief Tests if a color is in a vector
 *
 * @param v The vector of color
 * @param[in] c The color
 *
 * @return A boolean
 */
int colorIsInVector(OutObject* v, Color c);

#endif // _CORE_H_