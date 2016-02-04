/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Attribute types definition
 */

#ifndef _ATTRIBUTE_TYPES_H_
#define _ATTRIBUTE_TYPES_H_

/**
 * @brief Attribute type
 */
typedef unsigned char attrType;

#define TYPE_INT 1 // attribute that represents an integer
#define TYPE_ENUM 2 // attribute that represents an enumeration
#define TYPE_TREE 3 // attribute that represents a tree

#define TYPE_RELATION 4 // attribute that represents a relation
#define TYPE_NORELATION 5 // attribute that represents the lack of relation

#endif // _ATTRIBUTE_TYPES_H_
