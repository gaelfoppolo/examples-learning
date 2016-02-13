/**
 *	@file model.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the definition of the Model parsed in the model file
 */

#ifndef _MODEL_H_
#define _MODEL_H_

#include <string.h>

#include "model-attribute.h"
#include "vector.h"

/**
*   @brief Contains the attributes and relations definitions found in the model file
*/
typedef struct Model {
	/** 
	*	@brief An array of attributes definition. 
	*	Allow to know which attribute is ruled by which rules.
	*	The order in which they are stored matters
	*/
    Vector(ModelAttribute) ma;
    /** 
    *	@brief An array of the relations definitions. The order in which they are stored matters
    *	Only a string is stored (their name), the object they link is defined in the Examples
    */
	Vector(char*) rel;
} Model;

/**
*	@brief Initialize the Model
*	@param mdl A pointer to the Model to init
*/
void initModel(Model* mdl);

/**
*	@brief Free the Model structure (created while parsing the config file)
*	@param mdl A pointer to the Model to be freed
*/
void freeModel(Model* mdl);

/**
*	@brief Returns the identifier of the enumeration item whose name is given as a parameter
*	@param str The enumeration item's name of which the identifier is needed
*	@param mdl The Model
*	@param index The index of the ModelAttribute in the Model
*
*	@return Returns the identifier if found, -1 otherwise
*/
int getEnumId(const char* str, Model* mdl, unsigned int index);

/**
*	@brief Returns the identifier of the tree node or tree leaf whose name is given as a parameter
*	@param str The node or leaf name of which the identifier is needed
*	@param mdl The Model
*	@param index The index of the ModelAttribute in the Model
*
*	@return Returns the identifier if found, -1 otherwise
*/
int getTreeId(const char* str, Model* mdl, unsigned int index);

/**
*	@brief Returns the name of the enumeration item whose identifier is given as a parameter
*	@param id The enumeration item's identifier of which the name is needed
*	@param mdl The Model
*	@param index The index of the ModelAttribute in the model
*
*	@return Returns the name if found, NULL otherwise
*/
char* getEnumStr(int id, Model* mdl, unsigned int index);

/**
*	@brief Returns the name of the tree node or tree leaf whose identifier is given as a parameter
*	@param id The node or leaf identifier of which the name is needed
*	@param mdl The Model
*	@param index The index of the ModelAttribute in the model
*
*	@return Returns the name if found, NULL otherwise
*/
char* getTreeStr(int id, Model* mdl, unsigned int index);

#endif // _MODEL_H_
