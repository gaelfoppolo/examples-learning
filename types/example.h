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
#include "basic_object.h"

/**
*   @brief All the objects composing an example (or a counter-example)
*   @field objects An array of the objects composing the example
*/
typedef struct __basic_example {
    Vector(Object) objects;
} Example;

void initExample(Example * e);
void freeExample(Example * e);

#endif // _EXAMPLE_H_
