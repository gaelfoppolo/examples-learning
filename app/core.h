/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "../types/model.h"
#include "../types/examples.h"

/**
 * @brief Process examples of a model and produces solution object
 *
 * @param mdl Pointer to the model object containing structure of the model
 * @param exp Pointer to the structure containing examples and counter examples
 *
 * @return An solution object
 */
Solution* genSolution(Model* mdl, Examples* exp);

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