/**
 *	@file example.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Containins the definition of the Example
 */

#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include "vector.h"
#include "object.h"

/**
*   @brief All the objects composing an example (or a counter-example)
*
*	An example contains all the objects linked as part of this example.
*	It can store either	example or counter-example
*	(only the use we make of it differs between counter-example and examples)
*/
typedef struct Example {
	/** @brief The array that contains the objects of which is composed the example (or counter-example) */
    Vector(Object) objects;
} Example;

/**
*	@brief Initialize the example object
*	@param exp A pointer to the Example to be initialized
*/
void initExample(Example* exp);

/**
*	@brief Free the example object
*	@param exp A pointer to the Example to be freed
*	@param freeItself Boolean to know whether the Example is to be freed or not
*/
void freeExample(Example* exp, int freeItself);

#endif // _EXAMPLE_H_
