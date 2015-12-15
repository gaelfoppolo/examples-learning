/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The shape used by the app
 */

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <string.h>

typedef enum {
	whatever, polygone, ellipsoid, triangle, quadrilateral, circle, ellipse, rectangle_triangle, 
	isosceles_triangle, trapeze, rectangle, equilateral_triangle, square 
} Shape;

static const char *ShapeString[] = {
    "whatever", "polygone", "ellipsoid", "triangle", "quadrilateral", "circle", "ellipse", "rectangle triangle", 
    "isosceles triangle", "trapeze", "rectangle", "equilateral triangle", "square"
};

int getShapeId(char* shape);

#endif // _SHAPE_H_
