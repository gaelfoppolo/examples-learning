#include "vector.h"

static void doubleCapacity(Vector * vect) {
    vect->capacity *= 2;
    vect->data = (void**)realloc(vect->data, vect->capacity * sizeof(void*));
}

void initVector(Vector * vect) {
    vect->currentSize = 0;
    vect->capacity = VECTOR_DEFAULT_SIZE;

    vect->data = (void**)malloc(vect->capacity * sizeof(void*));
}

void pushVector(Vector * vect, void * item) {
    // if the vector is full
    if(vect->currentSize >= vect->capacity) {
        doubleCapacity(vect);
    }

    vect->data[vect->currentSize] = item;
    ++vect->currentSize;
}

void * vectorGet(Vector * vect, unsigned int index) {
    return vect->data[index];
}

void freeVector(Vector * vect) {
    free(vect->data);
}

unsigned int getVectorSize(Vector * vect) {
    return vect->currentSize;
}
