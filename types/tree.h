/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our N-ary tree
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "vector.h"

#define max(a,b) ((a) > (b) ? (a) : (b))

/**
 * @brief N-ary tree structure
 *
 * @field id Integer that represents the value of the node/leaf
 * @field str The name of the node/leaf
 * @field children Array of pointer to Tree: list of children
 *
 */
typedef struct __tree {
 	int id;
	char* str;
	Vector(struct __tree) children;
} Tree;

/**
 * @brief Create a new leaf (tree)
 *
 * @param id Id of the value to store in the leaf
 * @param str String that represents the real name of what is stored
 *
 * @return A new Tree
 */
Tree* createLeaf(int id, char* str);

/**
 * @brief Create a new node (tree)
 *
 * @param id Id of the value to store in the node
 * @param str String that represents the real name of what is stored
 * @param child The child to add to our new node
 *
 * @return A new node (tree)
 */
Tree* createNode(int id, char* str, Tree* child);

/**
 * @brief Add a child to a node (tree)
 *
 * @param node The node to which adds the child
 * @param child The child to add to our new node
 *
 * @return A node (tree)
 */
Tree* addChild(Tree* node, Tree* child);

/**
 * @brief Check if a tree is a leaf
 *
 * @param t The tree to check
 *
 * @return 0 (false) ou 1 (true)
 */
int isLeaf(Tree* t);

/**
 * @brief Get the height of a tree
 *
 * @param t The tree
 *
 * @return The height of the tree (integer)
 */
int height(Tree* t);

/**
 * @brief Get the depth of a node in the tree
 *
 * @param root The root of tree
 * @param id The id of the node
 *
 * @return The depth of the node in the tree (integer)
 */
int depth(Tree* root, int id);

/**
*	@brief NOT FOR USE - Used by depth - Recursively go down into the tree with the current depth
*	@param t The tree (node) to search into
*	@param id The id of the node
*	@param dpth The current depth of t
*
*	@return Returns the depth of the node matching the id
*/
int depth_rec(Tree* t, int id, int dpth);

/**
 * @brief Find the lowest common ancestor - Complexity θ(n)
 * @description We traverse from root to leaf(s).
 * When we find a node matching at least one, we pass it to its parent.
 * The parent tests if a child contains the value.
 * If yes, the parent is the LCA, else, we pass its parent, up to root.
 * What is pass is the lower node or NULL
 *
 * @param root The root of the tree
 * @param id1 The first value
 * @param id2 The second value
 *
 * @return The lowest common ancestor (node or leaf)
 */
Tree* LCA(Tree* root, int id1, int id2);

/**
 * @brief Remove from the memory, the space used by the tree
 *
 * @param t Pointer of the tree
 */
void freeTree(Tree* t);

#endif // _TREE_H_
