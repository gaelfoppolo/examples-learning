/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our example
 */

#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include "vector.h"
#include "object.h"

/**
*   @brief All the objects composing an example (or a counter-example)
*   @field objects An array of the objects composing the example
*/
typedef struct __basic_example {
    Vector(Object) objects;
} Example;

/**
*	@brief Init the example object
*	@param exp A pointer to the example to be initialized
*/
void initExample(Example * exp);

/**
*	@brief free the example object
*	@param exp A pointer to the example to be free
*	@param freeItself Boolean to know if the object needs to free itself
*/
void freeExample(Example * exp, int freeItself);

#endif // _EXAMPLE_H_
