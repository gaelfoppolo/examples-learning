#ifndef _CONFIG_PARSER_H_
#define _CONFIG_PARSER_H_

#include "../types/model.h"

/**
*	@brief Loads the config file and returns an Model object that contains all the informations of the config file
*	@param filename The path to the file
*
*	@return A new model Object
*/
Model* loadModel(char const* filename);

/**
*	@brief Frees all the data created by the loadModel function call
*	@param m The model to be freed
*/
void freeModel(Model* m);

#endif // _CONFIG_PARSER_H_
