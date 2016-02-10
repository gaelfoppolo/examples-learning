/**
 *	@file object.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the objects
 */

#ifndef _OBJECT_INDEX_H_
#define _OBJECT_INDEX_H_

#include "vector.h"

/**
*	@struct ObjectIndex
*   @brief Stores a list of indexes
*	When combining multiple objects, the identifier of each of them can be stored in this structure
*/
typedef struct ObjectIndex {
	/** @brief The indexes of the combined objects */
	Vector(int) indexes;
} ObjectIndex;

#endif // _OBJECT_INDEX_H_
