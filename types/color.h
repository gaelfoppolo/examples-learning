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

const char *colorString[] = { 
    "white", "black", "blue", "red"
};

/**
*	@brief Returns the numeric id of a color
*	@param color The string that represent the color
*	@return The numeric id of the color
*/
int getColorId(char* color);

#endif // _COLOR_H_
