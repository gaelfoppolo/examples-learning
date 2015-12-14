/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Dynamic int array implementation
 */

#ifndef _VECTOR_INT_H_
#define _VECTOR_INT_H_

#include <stdlib.h>

#ifndef VECTOR_DEFAULT_SIZE
#define VECTOR_DEFAULT_SIZE 10
#endif // VECTOR_DEFAULT_SIZE

/**
*   @brief Structure that represents a dynamic array
*   @field currentSize The number of elements currently in the array
*   @field capacity The maximum number of elements that the array can host
*   @field data The elements of the array
*/
typedef struct __basic_int_vector {
    unsigned int currentSize;
    unsigned int capacity;
    int* data;
} Vector;

/**
*   @brief Inits a vector
*   @param vect A pointer to a vector
*/
void initVector(Vector * vect);

/**
*   @brief Add an element at the end of the array
*   @param vect The vector at the end of which the element is to be added
*   @param item The element to be added
*/
void pushVector(Vector * vect, int item);

/**
*   @brief Returns the element at a given index of the array
*   @param vect The vector
*   @param index The index of the element wanted. Starts at 0. No bounds check
*   @return The element selected
*/
int vectorGet(Vector * vect, unsigned int index);

/**
*   @brief Free the vector
*   @param vect The vector to be freed
*/
void freeVector(Vector * vect);

/**
*   @brief Returns the size of the vector
*   @param vect The vector
*   @return The size of the vector
*/
unsigned int getVectorSize(Vector * vect);

#endif // _VECTOR_H_
