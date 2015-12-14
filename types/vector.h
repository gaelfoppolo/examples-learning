#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_DEFAULT_SIZE 10

/**
*   @brief Structure that represents a dynamic array
*   @field currentSize The number of elements currently in the array
*   @field capacity The maximum number of elements that the array can host
*   @field elemSize The size of an element
*   @field data The elements of the array
*/
typedef struct __basic_vector {
    unsigned int currentSize;
    unsigned int capacity;
    unsigned int elemSize;
    void* data;
} Vector;

/**
*   @brief Inits a vector
*   @param vect A pointer to a vector
*   @param elemSize The size of the elements that are to be stored in the array
*/
void initVector(Vector * vect, unsigned int elemSize);

/**
*   @brief Add an element at the end of the array
*   @param vect The vector at the end of which the element is to be added
*   @param item The element to be added
*/
void pushVector(Vector * vect, void * item);

/**
*   @brief Returns the element at a given index of the array
*   @param vect The vector
*   @param index The index of the element wanted. Starts at 0. No bounds check
*   @return A pointer to the element selected
*/
void * vectorGet(Vector * vect, unsigned int index);

/**
*   @brief Free the vector
*   @param vect The vector to be freed
*/
void freeVector(Vector * vect);

#endif // _VECTOR_H_
