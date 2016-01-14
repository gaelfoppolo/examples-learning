#ifndef _PARSERS_H_
#define _PARSERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

// sub-parsers

/**
*	@brief Tries to parse the line as a config file attribute definition. If the line is empty, continues to read until it finds a line.
*	@param fp The file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error append. Must be an uninitialized variable or data loss may happen
*
*	@return Returns the ModelAttribute generated from the line. If the line contains an error or EOF is reached, returns NULL
*/
int parseConfigLine(FILE* fp, char** error, ModelAttribute* out);

/**
*	@brief Tries to parse the attribute name at the current position in the file (spaces & tabs are ommited)
*	@param fp Ther file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error append. Must be an uninitialized variable or data loss may happen
*
*	@return Returns a new string that contains the attribute name or NULL in case of error
*/
char* parseAttrName(FILE* fp, char** error);

/**
*	@brief Tries to parse the attribute's value definition at the current position in the file (may read more than one line in case of trees)
*	@param fp Ther file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error append. Must be an uninitialized variable or data loss may happen
*
*	@return Returns the ModelType built from the file definition or NULL in case of error
*/
ModelType* parseAttrType(FILE* fp, char** error);

/**
*	@brief Tries to parse a specific type of attribute's type defininition
*	@param fp Ther file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error append. Must be an uninitialized variable or data loss may happen
*
*	@return The parsed value or NULL in case of error
*/
Interval* parseAttrTypeInterval(FILE* fp, char** error);
Enum* parseAttrTypeEnum(FILE* fp, char** error);
Tree* parseAttrTypeTree(FILE* fp, char** error, int* index);

/**
*	@brief Check wether the character is allowed in an attribute name or not
*	@param c The character to Check
*	@param first Wether the character is the first to be read or not
*
*	@return Returns 1 if the character is valid. 0 otherwise
*/
int isValidAttrChar(char c, unsigned int first);

/**
*	@brief Reads a file from the current position and reads while characters are in the set. Stops on the last one
*	@param f The file to be read
*	@param chars A nul terminated array of char that contains the set of characters
*/
void readFileSpaces(FILE* fp, char const* set);


#endif // _PARSERS_H_
