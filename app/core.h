/**
 *	@file core.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the core that generates the solutions
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>
#include <math.h>

#include "../types/model.h"
#include "../types/examples.h"
#include "../types/solution.h"
#include "../types/object-index.h"
#include "output.h"

/**
*	@brief Computes the number of combinations possible for our examples from an example
*	@param exp Pointer to our array of exemple
*	@param expIndice The example number
*
*	@return The number of combinations starting at expIndice example
*/
int nbCombi(Examples* exp, int expIndice);

/**
*	@brief Generate a filled OutObject based on an object values
*	@param mdl Pointer to the Model
*	@param o Pointer to the Object
* 
*	@return Pointer to OutObject
*/
OutObject* initOutObjectWithObject(Model* mdl, Object* o);

/**
*	@brief Init all combinations with last example objects
*	@param mdl Pointer to the Model
*	@param exp Pointer to the Examples
* 
*	@return Pointer to Solution inizialized
*/
Solution* initAllCombi(Model* mdl, Examples* exp);

/**
*	@brief Combine an OutObject and an Object into an OutObject
*	@param mdl Pointer to the Model
*	@param oo Pointer to the OutObject to combine with Object
*	@param o Pointer to the Object to combine with OutObject
*/
void combiOutObjectObject(Model* mdl, OutObject* oo, Object*o);

/**
*	@brief Generate all the combinations for our examples
*	@param mdl Pointer to the Model
*	@param exp Pointer to our Examples to combine
* 
*	@return Pointer to Solution containing all our combinations
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
*	@brief Get the index of the combinations of object in the array
*	@param exp Pointer to the examples
*	@param oi Pointer to the objects's indexes
* 
*	@return An integer
*/
int getIndex(Examples* exp, ObjectIndex* oi);

/**
*	@brief Is oo1 include in oo2?
*	
*	@param mdl Pointer to Model
*	@param oo1 Pointer to the first OutObject
*	@param oo2 Pointer to the second OutObject
* 
*	@return 1 if oo1 include in oo2, 0 else
*/
int isOutObjectIncludeInAnother(Model *mdl, OutObject* oo1, OutObject* oo2);

/**
*	@brief generalization of our solution(s)
*	@param mdl Pointer to the Model
*	@param s Pointer to the Solution
*/
void genGeneralization(Model *mdl, Solution* s);

/**
*	@brief Add counter-examples to the solutions
*	@param m Pointer to the Model
*	@param e Pointer to the examples
*	@param s Pointer to the solution
*/
void genCounterExamples(Model* m, Examples* e, Solution* s);

/**
*	@brief Check whether an OutObject matches an object or not
*	@param m The model
*	@param oo The OutObject that you want to know if it matches the Object
*	@param o The object
*
*	@return Returns 1 if the OutObject matches. 0 otherwise
*/
int isObjectInOutObject(Model* m, OutObject* oo, Object* o);

#endif // _CORE_H_