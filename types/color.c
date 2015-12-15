/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The color used by the app
 */

#include "color.h"

int getColorId(char* color) {
    if(strcmp(color, "white") == 0) return 0;
    else if(strcmp(color, "black") == 0) return 1;
    else if(strcmp(color, "blue") == 0) return 2;
    else if(strcmp(color, "red") == 0) return 3;
    return -1;
}