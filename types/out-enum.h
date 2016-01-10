/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our output enum
 */

#ifndef _OUTPUTENUM_H_
#define _OUTPUTENUM_H_

#include "vector.h"

/**
*   @brief All the integer composing the enum
*   @field oenu The list of the solution's integers
*/
typedef struct __basic_outenum {
    Vector(int) oenu
} OutEnum;

/**
*	@brief Init the output enum
*	@param enu A pointer to the enum to init
*/
void initOutEnum(OutEnum* oenu);

/**
*	@brief Free the ouput enum previously initialized by initEnum
*	@param oenu A pointer to the enum to free
*/
void freeOutEnum(OutEnum* oenu);

#endif // _OUTPUTENUM_H_