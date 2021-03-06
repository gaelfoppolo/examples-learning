/**
 *	@file examples.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the Examples
 */

#ifndef _EXAMPLES_H_
#define _EXAMPLES_H_

#include "example.h"

/**
*   @brief Structure that contains the examples and counter-examples of the parsed example file
*
*	Each example and counter-example found in the example file is stored in this structure.
*	Counter-examples are Example too, only the fields allow to differentiate them
*/
typedef struct Examples {
	/** @brief Contains all the examples of the file */
    Vector(Example) examples;
	/** @brief Contains all the counter-examples of the file */
    Vector(Example) counterExamples;
} Examples;

/**
*	@brief Initialize the Examples structure
*	@param exps A pointer to the Examples structure to be initialized
*/
void initExamples(Examples* exps);

/**
*	@brief Free the Examples structure
*	@param exps A pointer to the Examples to be freed
*/
void freeExamples(Examples* exps);

#endif // _EXAMPLES_H_