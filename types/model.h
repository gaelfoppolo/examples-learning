/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <string.h>

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

/**
*	@brief Init the model
*	@param mo A pointer to the model to init
*/
void initModel(Model* mo);

/**
*	@brief Frees the Model struct created while parsing the config file
*	@param mo The Model struct to free
*/
void freeModel(Model* mo);

/**
*	@brief Returns the id of the enum given as parameter
*	@param str The enum value to which the id is wanted
*	@param m, The model
*	@param index The index of the attribute
*
*	@return Returns the id if found, -1 otherwise
*/
int getEnumId(const char* str, Model* m, unsigned int index);
int getTreeId(const char* str, Model* m, unsigned int index);

/**
*	@brief NOT FOR USE - Used by getTreeId - Recursively search in the tree to find the id that match the value's name.
*	@param str The enum value to which the id is wanted
*	@param t The root of the tree in which to search
*
*	@return Returns the id if found, -1 otherwise
*/
int __getTreeId_rec(const char* str, Tree* t);

/**
*	@brief Returns the string of the enum's id given as parameter
*	@param id The enum id to which the str is wanted
*	@param m, The model
*	@param index The index of the attribute
*
*	@return Returns the str if found, NULL otherwise
*/
char* getEnumStr(int id, Model* m, unsigned int index);
char* getTreeStr(int id, Model* m, unsigned int index);

/**
*	@brief NOT FOR USE - Used by getTreeStr - Recursively search in the tree to find the str that match the id.
*	@param id The enum id to which the str is wanted
*	@param t The root of the tree in which to search
*
*	@return Returns the str if found, NULL otherwise
*/
char* __getTreeStr_rec(int id, Tree* t);

#endif // _MODEL_H_
