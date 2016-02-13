/**
 *	@file attribute-types.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief Contains the attribute's types definition
 *	In our model we have five attribute types: interval of integer, enumeration, n-ary tree, relation and no relation
 */

#ifndef _ATTRIBUTE_TYPES_H_
#define _ATTRIBUTE_TYPES_H_

/**
 *	@typedef unsigned char attrType
 *	@brief Stores the type of the attribute
 */
typedef unsigned char attrType;

/** @brief Indicate a type that stores signed integers */
#define TYPE_INT 1

/** @brief Indicate a type that stores enumerations */
#define TYPE_ENUM 2

/** @brief Indicate a type that stores a tree */
#define TYPE_TREE 3

/** @brief Indicate a type that stores a relation */
#define TYPE_RELATION 4

/** @brief Denote the absence of a relation in this attribute */
#define TYPE_NORELATION 5

#endif // _ATTRIBUTE_TYPES_H_
