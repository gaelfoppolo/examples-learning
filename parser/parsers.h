/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief The parser
 */

#ifndef _PARSERS_H_
#define _PARSERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "../types/examples.h"
#include "../types/model.h"
#include "../types/string-type.h"
#include "../app/output.h"

#define PARSED_EXAMPLE 1 // value returned by the getNextExample function if the example is an example
#define PARSED_COUNTEREXAMPLE 2 // value returned by the getNextExample function if the example is a counter-example

struct __basic_string_vector {
	Vector(char*) seen;
};

/**
*	@brief Get the pathname to the config file included at the begening of an example file
*	@param pathname The path to the example file
*	@param pos Will contain the position of the character after the last character of the include (basically, a " ", "\t" or "\n")
*
*	@return If the file to include is found, the file name. NULL otherwise
*/
char* getIncludeFile(char const* pathname, size_t * pos);

/**
*	@brief Loads the example file given and generate the Example object that represents its content
*	@param pathname The path to the example file to be read
*	@param model The Model object generated from the config file
*	@param startPos The position at which to start parsing the file
*
*	@return A newly created Examples object
*/
Examples* loadExampleFile(char const* pathname, Model* model, size_t startPos);

/**
*	@brief Get the type of the next example (example or counter-example). Stop reading at the end of the example name, on the last character
*	@param f The file to be read
*
*	@param Returns 0 in case of error, PARSED_EXAMPLE if the line is an example, PARSED_COUNTEREXAMPLE if the line is a counter-example
*/
unsigned int getNextExample(FILE* f);

/**
*	@brief Parse an example or a counterexample
*	@param fp The file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error happened. Must be an uninitialized variable or data loss may occur.
*	@param ex A pointer to the example object to populate
*	@param m The Model object generated from the config file
*
*	@return A boolean. 1 for success. 0 for failure.
*/
int parseExample(FILE* fp, char** error, Example* ex, Model* m);

/**
*	@brief Parse an object (only its properties. The name must already be known)
*	@param fp The file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error happened. Must be an uninitialized variable or data loss may occur.
*	@param o A pointer to the object Object to populate
*	@param m The Model object generated from the config file
*	@param seenObjects The names of the objects that have already been seen
*
*	@return A boolean. 1 for success. 0 for failure
*/
int parseExampleObject(FILE* fp, char** error, Object* o, Model* m, struct __basic_string_vector* seenObjects);

/**
*	@brief Returns the position at which can be found an attribute (by name)
*	@param attr the attribute to search for
*	@param m The model in which to find the order
*
*	@return the index of the attribute (or -1 in case the attributes is not in the model)
*/
int getAttributePosition(const char* attr, Model* m);

/**
*	@brief Returns the position at which can be found a relation (by name)
*	@param rel the relation to search for
*	@param m The model in which to find the order
*
*	@return the index of the attribute (or -1 in case the attributes is not in the model)
*/
int getRelationPosition(const char* rel, Model* m);

/**
*	@brief Parse the attribute's value and populate the Attribute object accordingly
*	@param fp The file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error happened. Must be an uninitialized variable or data loss may occur.
*	@param m The model to use for the parsing
*	@param type The expected type of the attribute
*	@param attr A pointer to the attribute to populate
*	@param position The position of the attribute in the model
*	@param seenObjects The names of the objects that have already been seen
*/
void parseAttrValue(FILE* fp, char** error, Model* m, attrType type, Attribute* attr, unsigned int position, struct __basic_string_vector* seenObjects);

/**
*	@brief Loads the config file given anf the generate the Model object that represents its content
*	@param pathname The path tp the config file to be read
*
*	@return A newly created Model object
*/
Model* loadConfigFile(char const* pathname);

/**
*	@brief Tries to parse the line as a config file attribute definition. If the line is empty, continues to read until it finds a line.
*	@param fp The file in which to read
*	@param error In case of error, contains a description of the error. NULL if no error append. Must be an uninitialized variable or data loss may happen
*	@param out A pointer to the Model object to populate
*
*	@return A boolean. 1 for success. 0 for failure.
*/
int parseConfigLine(FILE* fp, char** error, Model* out) ;

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
Tree* parseAttrTypeTree(FILE* fp, char** error, int* index, int indent);

/**
*	@brief Check whether the character is allowed in an attribute name or not
*	@param c The character to Check
*	@param first Wether the character is the first to be read or not
*
*	@return Returns 1 if the character is valid. 0 otherwise
*/
int isValidAttrChar(char c, unsigned int first);

/**
*	@brief Reads a file from the current position and reads while characters are in the set. Stops on the last one
*	@param f The file to be read
*	@param set A nul terminated array of char that contains the set of characters
*/
void readFileSpaces(FILE* fp, char const* set);

/**
*	@brief Reads a file from the current position and reads until it finds a character in the set. Stops on the last character not in the set
*	@param f The file to be read
*	@param set A nul terminated array of char that contains the set of characters to reach
*/
void readTil(FILE* fp, char const* set);

/**
*	@brief Display tabs(s)
*	@param indent The number of tabs to display
*/
void printIndent(int indent);


#endif // _PARSERS_H_
