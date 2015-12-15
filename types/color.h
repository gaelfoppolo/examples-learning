/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The colors used by the app
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include <string.h>

typedef enum {
	white, black, blue, red
} Color;

static const char *ColorString[] = {
    "white", "black", "blue", "red"
};

int getColorId(char* color);

#endif // _COLOR_H_
