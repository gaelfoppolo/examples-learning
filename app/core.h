/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "../types/model.h"
#include "../types/tree.h"

/**
 * @brief Process examples of a model and produces output object
 *
 * @param ms Pointer to the structure containing examples and counter examples
 * @param root Root of the tree we use
 *
 * @return An output object
 */
OutObject* learning(ModelSample* ms, Tree* root);

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