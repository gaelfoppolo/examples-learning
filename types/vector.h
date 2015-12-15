#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

#define Vector(t) struct {int size, capacity; t *data; }
#define vectInit(vect) ((vect).size = (vect).capacity = 0, (vect).data = 0)
#define vectFree(vect) free((vect).data)
#define vectAt(vect, index) ((vect).data[(index)])
#define vectSize(vect) ((vect).size)
#define vectPush(type, vect, value) do {                                                                                \
                                        if((vect).size == (vect).capacity) {                                            \
                                            (vect).capacity = ((vect).capacity ? (vect).capacity * 2 : 10);             \
                                            (vect).data = (type*)realloc((vect).data, sizeof(type) * (vect).capacity);  \
                                        }                                                                               \
                                        (vect).data[(vect).size++] = value;                                             \
                                    } while(0);

#endif // _VECTOR_H_
