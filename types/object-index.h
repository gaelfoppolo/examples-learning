/**
 *	@file object-index.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the ObjectIndex
 */

#ifndef _OBJECT_INDEX_H_
#define _OBJECT_INDEX_H_

#include "vector.h"

/**
*   @brief Stores a list of indexes
*	When combining multiple Object, the identifier of each of them (rank in the Example) can be stored in this structure
*/
typedef struct ObjectIndex {
	/** @brief The indexes of the combined objects */
	Vector(int) indexes;
} ObjectIndex;

#endif // _OBJECT_INDEX_H_
