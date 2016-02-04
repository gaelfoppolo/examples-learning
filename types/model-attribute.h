/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our model attribute
 */

#ifndef _MODEL_ATTRIB_H_
#define _MODEL_ATTRIB_H_

#include <string.h>

#include "model-type.h"

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
*	@brief Free the ModelAttribute
*	@param ma A pointer to the ModelAttribute to be free
*	@param freeItself Boolean to know if the ModelAttribute needs to free itself
*/
void freeModelAttribute(ModelAttribute* ma, int freeItself);

#endif // _MODEL_ATTRIB_H_