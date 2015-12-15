/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The colors used by the app
 */

#ifndef _COLORS_H_
#define _COLORS_H_

#include <string.h>

#define NOCOLOR 0
#define WHITE 1
#define BLACK 2
#define RED 3
#define BLUE 4

typedef int Color;

int getColorId(char* color);
int getShapeId(char* shape); // à déplacer

#endif // _COLORS_H_
