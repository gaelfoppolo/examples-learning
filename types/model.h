/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include "example.h"

/**
*   @brief Structure that contains the examples and counter-examples of the current model
*   @field examples Array of examples
*   @field counterExamples Array of counter-examples
*/
typedef struct __basic_model_sample {
    Vector(Example) examples;
    Vector(Example) counterExamples;
} ModelSample;

/**
*	@brief Init the model sample object
*	@param ms A pointer to the modelSample to be initialized
*/
void initModelSample(ModelSample * ms);

/**
*	@brief Free the model sample object
*	@param ms A pointer to the modelSample to be freed
*/
void freeModelSample(ModelSample * ms);

#endif // _MODEL_H_