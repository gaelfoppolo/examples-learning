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
#include "color.h"
#include "shape.h"

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
	Vector(Color) colors;
	Shape shape;
} OutObject;

/**
*	@brief Init the output object
*	@param out A pointer to the object to init
*/
void initOutObject(OutObject* out);

/**
*	@brief Free the output previewsly initialized by initOutObject
*	@paramout A pointer to the object to free
*/
void freeOutObject(OutObject* out);

#endif // _BASICOBJECT_H_
