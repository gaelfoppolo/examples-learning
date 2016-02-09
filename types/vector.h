/**
 *	@file vector.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the vectors (dynamic & generic arrays)
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

/**
*	@brief define a dynamic array
*	@param t The type of the items to store in the vector
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
                                    } while(0)

/**
*	@brief Search for an element in the vector. Returns its index if found
*	@param vect The vector to search in
*	@param value The value to search for
*	@param out An integer that will hold the return value (either the index if found ou -1 if the element is not int the vector)
*/
#define vectIndexOf(vect, value, out) do {																				\
										out = -1;																		\
										for(int i = 0; i < vectSize(vect); ++i) {										\
											if(vectAt(vect, i) == value) {												\
												out = i;																\
												break;																	\
											}																			\
										}																				\
									} while(0)

/**
*	@brief Remove the last element in the vector
*	@param vect The vector to which remove the last element
*/
#define vectRemoveLast(vect) do {																						\
									if((vect).size > 0) {																\
										--(vect).size;																	\
									}																					\
								} while(0)

#endif // _VECTOR_H_
