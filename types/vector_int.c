#include "vector_int.h"

void initVector(Vector * vect) {
    vect->currentSize = 0;
    vect->capacity = VECTOR_DEFAULT_SIZE;

    vect->data = (int*)malloc(vect->capacity * sizeof(int));
}

void pushVector(Vector * vect, int item) {
    // if the vector is full
    if(vect->currentSize >= vect->capacity) {
        vect->capacity *= 2; // double the array capacity
        vect->data = (int*)realloc(vect->data, vect->capacity * sizeof(int));
    }

    vect->data[vect->currentSize] = item;
    ++vect->currentSize;
}

int vectorGet(Vector * vect, unsigned int index) {
    return vect->data[index];
}

void freeVector(Vector * vect) {
    free(vect->data);
}

unsigned int getVectorSize(Vector * vect) {
    return vect->currentSize;
}
