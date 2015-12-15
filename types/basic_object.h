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

/**
*	@brief The object that represents the common traits of the other objects
*	@field min The min size of the objects
*	@field max The max size of the objects
*	@field colors The list of the object's colors
*	@field shape The lowest common shape of the objects
*/
typedef struct __basic_out_object {
	int min;
	int max;
	Vect(Color) colors;
	Shape shape;
} OutObject;

#endif // _BASICOBJECT_H_
