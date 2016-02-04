/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our output attribute
 */

#ifndef _OUT_ATTRIBUTE_H_
#define _OUT_ATTRIBUTE_H_

#include "attribute-types.h"
#include "interval.h"
#include "out-enum.h"

/**
*   @brief Represents an attribute and the value it holds
*   @field type The attribute's type
*   @field inter The inter value if the attribute is an interval
*	@field oenu The enum value if the attribute is an enum
*	@field tree The tree value if the attribute is an enum
*/
typedef struct __basic_out_attribute {
    attrType type;
	union {
    	Interval inter;
    	OutEnum oenu;
    	int tree;
    };
} OutAttribute;

/**
*	@brief Free the OutAttribute
*	@param oa A pointer to the OutAttribute to free
*	@param freeItself Boolean to know if the OutAttribute needs to free itself
*/
void freeOutAttribute(OutAttribute* oa, int freeItself);

#endif // _OUT_ATTRIBUTE_H_
