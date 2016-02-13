/**
 *	@file model-type.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of an attribute's type
 */

#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "attribute-types.h"
#include "interval.h"
#include "enum.h"
#include "tree.h"

/**
*   @brief Structure that contains the definition of the type
*/
typedef struct ModelType {
	/** @brief The type contained */
    attrType type;
    /**
	*	@brief As model types can be of 3 different types, each is defined, the good one is selected via the type field
    */
    union {
    	/** @brief Contains the definition of the type if it is an interval */
    	Interval inter;
    	/** @brief Contains the definition of the type if it is an enumeration */
    	Enum enu;
    	/** @brief Contains the definition of the type if it is a tree */
    	Tree tree;
    };
} ModelType;

/**
*	@brief Free the ModelType
*	@param mt A pointer to the ModelType to be freed
*	@param freeItself Boolean to know whether the ModelType is to be freed or not
*/
void freeModelType(ModelType* mt, int freeItself);

#endif // _MODELTYPE_H_
