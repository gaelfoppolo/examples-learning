#ifndef _PARSERS_H_
#define _PARSERS_H_

#include <stdlib.h>
#include <stdio.h>

#include "../types/examples.h"
#include "../types/model.h"
#include "../types/string-type.h"

/**
*	@brief Get the pathname to the config file included at the begening of an example file
*	@param pathname The path to the example file
*
*	@return If the file to include is found, the file name. NULL otherwise
*/
char* getIncludeFile(char const* pathname);

/**
*	@brief Loads the example file given and generate the Example object that represents its content
*	@param pathname The path to the example file to be read
*	@param model The Model object generated from the config file
*
*	@return A newly created Examples object
*/
Examples* loadExampleFile(char const* pathname, Model* model);

/**
*	@brief Frees the Example struct created while parsing the Example file
*	@param ex The Example struct to free
*/
void freeExamples(Examples* ex);

/**
*	@brief Loads the config file given anf the generate the Model object that represents its content
*	@param pathname The path tp the config file to be read
*
*	@return A newly created Model object
*/
Model* loadConfigFile(char const* pathname);

/**
*	@brief Frees the Model struct created while parsing the config file
*	@param mo The Model struct to free
*/
void freeModel(Model* mo);


#endif // _PARSERS_H_
