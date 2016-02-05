/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our model
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <string.h>

#include "model-attribute.h"
#include "vector.h"

/**
*   @brief Structure that contains the model
*   @field ma The vector of attributes possible values and their name
*	@field rel The vector of the object's possible relations by name
*/
typedef struct __basic_model {
    Vector(ModelAttribute) ma;
	Vector(char*) rel;
} Model;

/**
*	@brief Init the model
*	@param mdl A pointer to the model to init
*/
void initModel(Model* mdl);

/**
*	@brief Free the Model struct created while parsing the config file
*	@param mdl The Model struct to free
*/
void freeModel(Model* mdl);

/**
*	@brief Returns the id of the enum (resp. tree) given as parameter
*	@param str The enum (resp. tree) value to which the id is wanted
*	@param mdl, The model
*	@param index The index of the attribute
*
*	@return Returns the id if found, -1 otherwise
*/
int getEnumId(const char* str, Model* mdl, unsigned int index);
int getTreeId(const char* str, Model* mdl, unsigned int index);

/**
*	@brief Returns the string of the enum's (resp. tree's) id given as parameter
*	@param id The enum (resp. tree) id to which the str is wanted
*	@param mdl, The model
*	@param index The index of the attribute
*
*	@return Returns the str if found, NULL otherwise
*/
char* getEnumStr(int id, Model* mdl, unsigned int index);
char* getTreeStr(int id, Model* mdl, unsigned int index);

/**
*	@brief NOT FOR USE - Used by getTreeStr - Recursively search in the tree to find the str that match the id.
*	@param id The enum id to which the str is wanted
*	@param t The root of the tree in which to search
*
*	@return Returns the str if found, NULL otherwise
*/
char* __getTreeStr_rec(int id, Tree* t);

#endif // _MODEL_H_
