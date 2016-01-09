/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include "attribute_types.h"
#include "interval.h"
#include "enum.h"
#include "tree.h"

/**
*   @brief Structure that contains the model attributes
*   @field type Type of the attribute
*   @field union The attribute depending on the type
*/
typedef struct __basic_model {
    attrType type;
    union {
    	Interval inter;
    	Enum enu;
    	Tree tree;
    };
} Model;

#endif // _MODEL_H_