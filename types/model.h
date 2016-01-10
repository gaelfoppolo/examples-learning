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

/**
*   @brief Structure that contains the model
*   @field mt The type of the propertie's model
*   @field name The name of the propertie's model
*/
typedef struct __basic_model {
    ModelType mt;
    char* name;
} Model;

#endif // _MODEL_H_