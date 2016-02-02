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
*   @brief Represent the indices of the objects combined
*   @field indices the indices of the objects combined
*/
typedef struct __basic_objindex {
    Vector(int) indices;
} ObjectIndice;

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

/**
 * @brief Fill an empty OutObject based on a object values
 *
 * @param o Pointer to the outobject
 * @param o Pointer to the object
 * 
 */
void initEmptyOutObject(OutObject* oo, Object* o);

/**
 * @brief Combine an OutObject and an Object into an OutObject
 *
 * @param first Pointer to the first OutObject (and also the result of the combinaison)
 * @param second Pointer to the second OutObject to combine
 * @param mdl Pointer to the model (structure of our model is inside)
 * 
 */
void genCombi(OutObject* first, Object* second, Model* mdl);

/**
 * @brief Get the index of the combinaisons of object in the array
 *
 * @param exp Pointer to the examples
 * @param oi Pointer to the objects's indices
 * 
 * @return An integer
 */
int getIndex(Examples* exp, ObjectIndice* oi);

#endif // _CORE_H_