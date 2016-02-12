/**
 *	@file out-attribute.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the out-attributes
 */

#ifndef _OUT_ATTRIBUTE_H_
#define _OUT_ATTRIBUTE_H_

#include "attribute-types.h"
#include "interval.h"
#include "out-enum.h"

/**
  *	@brief Represents an attribute used by the solution and the value it holds
 *	
 *	This structure holds the attribute of the object generated by the solution. They contains the 
 *	generalisation of the objects of which they are the composition
 *	OutAttributes can hold values of different types
 *	(signed integer interval, items of an enumeration, node or leaf of a tree).
 */
typedef struct OutAttribute {
	/** @brief The type contained by this attribute */
    attrType type;
    /**
    *	@brief As model types can be of 3 different types, each is defined, the good one is selected via the type field
    */
	union {
		/** @brief Contains the definition of the type if it is an interval */
    	Interval inter;
		/** @brief Contains the definition of the type if it is an enumeration extract */
    	OutEnum oenu;    	
		/** @brief Contains the definition of the type if it is the node or the leaf of a tree */
    	int tree;
    };
} OutAttribute;

/**
*	@brief Free the OutAttribute
*	@param oa A pointer to the OutAttribute to free
*	@param freeItself Boolean to know wether the OutAttribute is to be freed or not
*/
void freeOutAttribute(OutAttribute* oa, int freeItself);

#endif // _OUT_ATTRIBUTE_H_
