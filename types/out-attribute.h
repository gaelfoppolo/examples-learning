/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our attribute
 */

#ifndef _OUT_ATTRIBUTE_H_
#define _OUT_ATTRIBUTE_H_

#include "attribute-types.h"

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

#endif // _OUT_ATTRIBUTE_H_
