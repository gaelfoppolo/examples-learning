/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our model type
 */

#ifndef _MODELTYPE_H_
#define _MODELTYPE_H_

#include "attribute-types.h"
#include "interval.h"
#include "enum.h"
#include "tree.h"

/**
*   @brief Structure that contains the model attribute
*   @field type Type of the attribute
*   @field union (inter or enum or tree) The attribute depending on the type
*/
typedef struct __basic_model_type {
    attrType type;
    union {
    	Interval inter;
    	Enum enu;
    	Tree tree;
    };
} ModelType;

/**
*	@brief Free the ModelType
*	@param mt A pointer to the ModelType to be free
*	@param freeItself Boolean to know if the ModelType needs to free itself
*/
void freeModelType(ModelType* mt, int freeItself);

#endif // _MODELTYPE_H_
