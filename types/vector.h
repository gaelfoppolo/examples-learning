#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

/**
*	@brief define a dynamic array of type t
*/
#define Vector(t) struct {int size, capacity; t *data; }

/**
*	@brief Init the vector
*	@param vect The vector to be initialized
*/
#define vectInit(vect) ((vect).size = (vect).capacity = 0, (vect).data = 0)

/**
*	@brief Free the vector
*	@param vect The vector to be initialized
*/
#define vectFree(vect) free((vect).data)

/**
*	@brief Returns the element at a certain index of the array
*	@param vect The vector of which to access the element
*	@param index The index of the element (between 0 and vector size - 1)
*	@return The element (directly. You can use this as a left value)
*/
#define vectAt(vect, index) ((vect).data[(index)])

/**
*	@brief Return the size of the array
*	@param vect The array of which to get the size
*	@return The size of the array
*/
#define vectSize(vect) ((vect).size)

/**
*	@brief Append an element at the end of the vector
*	@param type The type of the element (must be the same type as the other elements of the array)
*	@param vect The vector at the end of which to add the element
*	@param value The element to be appened
*/
#define vectPush(type, vect, value) do {                                                                                \
                                        if((vect).size == (vect).capacity) {                                            \
                                            (vect).capacity = ((vect).capacity ? (vect).capacity * 2 : 10);             \
                                            (vect).data = (type*)realloc((vect).data, sizeof(type) * (vect).capacity);  \
                                        }                                                                               \
                                        (vect).data[(vect).size++] = value;                                             \
                                    } while(0);                                 

#endif // _VECTOR_H_
