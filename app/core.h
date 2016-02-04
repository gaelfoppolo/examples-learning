/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief The core
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>

#include "../types/model.h"
#include "../types/examples.h"
#include "../types/solution.h"
#include "output.h"

/**
*   @brief Represent the indices of the objects combined
*   @field indices the indices of the objects combined
*/
typedef struct __basic_objindex {
	Vector(int) indices;
} ObjectIndice;

/**
 * @brief Calculate the number of combinaisons possible for our examples from an example
 *
 * @param exp Pointer to our array of exemple
 * @param expIndice The example number (= indice)
 *
 * @return The number of combinaisons starting at expIndice example
 */
int nbCombi(Examples* exp, int expIndice);

/**
 * @brief Generate a filled OutObject based on an object values
 *
 * @param mdl Pointer to the Model
 * @param o Pointer to the Object
 * 
 * @return Pointer to OutObject
 */
OutObject* initOutObjectWithObject(Model* mdl, Object* o);

/**
 * @brief Init all combinaisons with last example objects
 *
 * @param mdl Pointer to the Model
 * @param exp Pointer to the Examples
 * 
 * @return Pointer to Solution inizialized
 */
Solution* initAllCombi(Model* mdl, Examples* exp);

/**
 * @brief Combine an OutObject and an Object into an OutObject
 *
 * @param mdl Pointer to the Model
 * @param oo Pointer to the OutObject to combine with Object
 * @param o Pointer to the Object to combine with OutObject
 * 
 */
void combiOutObjectObject(Model* mdl, OutObject* oo, Object*o);

/**
 * @brief Generate all the combinations for our examples
 *
 * @param mdl Pointer to the Model
 * @param eex Pointer to our Examples to combine
 * 
 * @return Pointer to Solution containing all our combinaisons
 */
Solution* genAllCombi(Model* mdl, Examples* exp);

/**
*	@brief Find all the common relation between the objects
*	@param s The solution generated by the genAllCombi function
*	@param e The examples to search the relations into
*	@param m The model to use the relations
*/
void genAllRelations(Solution* s, Examples* e, Model* m);

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