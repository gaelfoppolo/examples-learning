/**
 *	@file out-enum.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the enumeration extracts
 */

#ifndef _OUTPUTENUM_H_
#define _OUTPUTENUM_H_

#include "vector.h"

/**
*	@struct OutEnum
*   @brief Contains multiple enumeration items
*	When combining multiple Object, each enumeration item is to be stored, this structure does that
*/
typedef struct OutEnum {
	/** @brief An array that contains the identifier of each enumeration item contained */
    Vector(int) oenu;
} OutEnum;

/**
*	@brief Init the output enum
*	@param oenu A pointer to the enum to init
*/
void initOutEnum(OutEnum* oenu);

/**
*	@brief Free the OutEnum previously initialized by initEnum
*	@param oenu A pointer to the enum to free
*	@param freeItself Boolean to know wether the OutEnum is to be freed or not
*/
void freeOutEnum(OutEnum* oenu, int freeItself);

/**
 * 	@brief Compare two OutEnum
 *
 * 	@param oenu1 First OutEnum
 * 	@param oenu2 Second OutEnum
 
 *	@return  0 = same or bigger, 1 = smaller or different
 */
int compareOutEnum(OutEnum oenu1, OutEnum oenu2);

#endif // _OUTPUTENUM_H_