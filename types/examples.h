/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our examples and counter-examples
 */

#ifndef _EXAMPLES_H_
#define _EXAMPLES_H_

#include "example.h"

/**
*   @brief Structure that contains the examples and counter-examples of the current model
*   @field examples Array of examples
*   @field counterExamples Array of counter-examples
*/
typedef struct __basic_examples {
    Vector(Example) examples;
    Vector(Example) counterExamples;
} Examples;

/**
*	@brief Init examples object
*	@param exps A pointer to the Examples to be initialized
*/
void initExamples(Examples * exps);

/**
*	@brief Free examples object
*	@param exps A pointer to the Examples to be free
*/
void freeExamples(Examples * exps);

#endif // _EXAMPLES_H_