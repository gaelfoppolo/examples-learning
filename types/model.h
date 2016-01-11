/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include "model-type.h"
#include "vector.h"

/**
*	@brief The attribute possible value and its name
*	@field mt The possible value of the attribute
*	@field name The name of the attribute
*/
typedef struct __basic_model_attribute {
	ModelType mt;
	char* name;
} ModelAttribute;

/**
*   @brief Structure that contains the model
*   @field ma The vector of attributes possible values and their name
*/
typedef struct __basic_model {
    Vector(ModelAttribute) ma;
} Model;

#endif // _MODEL_H_
