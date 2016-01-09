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
*	@param e A pointer to the example to be initialized
*/
void initExample(Example * e);

/**
*	@brief free the example object
*	@param e A pointer to the example to be freed
*/
void freeExample(Example * e);

#endif // _EXAMPLE_H_
