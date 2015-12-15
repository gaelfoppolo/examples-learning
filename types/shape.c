/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The shape used by the app
 */

#include "shape.h"

int getShapeId(char* shape) {
    if(strcmp(shape, "whatever") == 0) return 0;
    if(strcmp(shape, "polygone") == 0) return 1;
    if(strcmp(shape, "ellipsoid") == 0) return 2;
    if(strcmp(shape, "triangle") == 0) return 3;
    if(strcmp(shape, "quadrilateral") == 0) return 4;
    if(strcmp(shape, "circle") == 0) return 5;
    if(strcmp(shape, "ellipse") == 0) return 6;
    if(strcmp(shape, "rectangle triangle") == 0) return 7;
    if(strcmp(shape, "isosceles triangle") == 0) return 8;
    if(strcmp(shape, "trapeze") == 0) return 9;
    if(strcmp(shape, "rectangle") == 0) return 10;
    if(strcmp(shape, "equilateral triangle") == 0) return 11;
    if(strcmp(shape, "square") == 0) return 12;
    return -1;
}