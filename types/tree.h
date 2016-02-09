/**
 *	@file tree.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the definition of the trees
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include "vector.h"

/**
*	@def max(a, b)
*	@brief Computes the maximum of @a a and @a b
*/
#define max(a,b) ((a) > (b) ? (a) : (b))

/**
*	@struct Tree
*	@brief Defines the trees
*/
typedef struct Tree {
	/** @brief The unique identifier of this node or leaf */
 	int id;
 	/** @brief The name of this node or leaf */
	char* str;
	/** @brief all the children of this node (or nothing if a leaf) */
	Vector(struct Tree) children;
} Tree;

/**
*	@brief Create a new leaf
*	@param id The value to store in the leaf
*	@param str String that represents the real name of what is stored
*
*	@return A new leaf
*/
Tree* createLeaf(int id, char* str);

/**
*	@brief Create a new node
*	@param id The value to store in the node
*	@param str String that represents the real name of what is stored
*	@param child The child to add to our new node
*
*	@return A new node
*/
Tree* createNode(int id, char* str, Tree* child);

/**
*	@brief Add a child to a node
*	@param node The node to which to add the child
*	@param child The child to add to our node
*
*	@return The modified node (same as given as parameter)
*/
Tree* addChild(Tree* node, Tree* child);

/**
*	@brief Check wether the tree is a leaf or not
*	@param t The tree to check
*
*	@return Returns 1 if the parameter is a leaf, 0 otherwise
*/
int isLeaf(Tree* t);

/**
*	@brief Get the height of a tree
*	@param t The tree of which the height is needed
*
*	@return The height of the tree
*/
int height(Tree* t);

/**
*	@brief Get the depth of a node in the tree
*	@param root The root of the tree
*	@param id The id of the node of which the depth is needed
*
*	@return The depth of the node in the tree
*/
int depth(Tree* root, int id);

/**
*	@brief Find the lowest common ancestor
*	We traverse from root to leaf.
*	When we find a node matching at least one value, we pass it to its parent.
*	The parent tests wether a child contains the value or not.
*	If yes, the parent is the LCA, otherwise, we pass its parent, up to root.
*	What is passed is the lower node or NULL
*
*	@param root The root of the tree
*	@param id1 The first value
*	@param id2 The second value
*
*	@return The lowest common ancestor (node or leaf)
*/
Tree* LCA(Tree* root, int id1, int id2);

/**
*	@brief Free the tree
*	@param t Pointer to the tree
*/
void freeTree(Tree* t);

#endif // _TREE_H_
