/**
 *	@file out-enum.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Containins the definition of the OutEnum
 */

#ifndef _OUTPUTENUM_H_
#define _OUTPUTENUM_H_

#include "vector.h"

/**
*   @brief Contains multiple enumeration items
*	When combining multiple Object, each enumeration item is to be stored, this structure does that
*/
typedef struct OutEnum {
	/** @brief An array that contains the identifier of each enumeration item contained */
    Vector(int) oenu;
} OutEnum;

/**
*	@brief Initilialize the OutputEnum
*	@param oenu A pointer to the OutputEnum to init
*/
void initOutEnum(OutEnum* oenu);

/**
*	@brief Free the OutEnum previously initialized by initEnum
*	@param oenu A pointer to the enum to free
*	@param freeItself Boolean to know whether the OutEnum is to be freed or not
*/
void freeOutEnum(OutEnum* oenu, int freeItself);

/**
 * 	@brief Is oenu1 include in oenu2?
 *
 * 	@param oenu1 First OutEnum
 * 	@param oenu2 Second OutEnum
 
 *	@return 1, if oenu1 is include in oenu2, 0 otherwise
 */
int isOutEnumIncludeInAnother(OutEnum oenu1, OutEnum oenu2);

#endif // _OUTPUTENUM_H_