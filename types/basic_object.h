/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our object
 */

#ifndef _BASICOBJECT_H_
#define _BASICOBJECT_H_

#include "vector.h"
#include "colors.h"

typedef int Shape;

/**
*   @brief All the attributes of the object
*   @field size The object's size
*   @field color The object's color
*   @field shape The object's shape
*/
typedef struct __basic_object {
    int size;
    Color color;
    Shape shape;
} Object;


#endif // _BASICOBJECT_H_
