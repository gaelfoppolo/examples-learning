/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions and structures used by the binary tree
 */

#ifndef _TREE_H_
#define _TREE_H_

/**
 * @brief Binary tree structure
 * 
 * @field value Integer value
 * @field *lf_child Pointer to left child
 * @field *rg_child Pointer to right child
 *
 */
typedef struct __tree {
 	int value;
 	struct __tree *lf_child;
 	struct __tree *rg_child;
} Tree;

/**
 * @brief Create a new leaf (tree)
 * 
 * @param val Value matching the geometric shape
 * 
 * @return A new Tree
 */
Tree* createLeaf(int val);

/**
 * @brief Create a new node (tree)
 *
 * @param val Value matching the geometric shape
 * @param[in] lfc The left child
 * @param[in] rgc The right child
 *
 * @return A new Tree
 */
Tree* createNode(int val, Tree* lfc, Tree* rgc);

/**
 * @brief Check if a tree is a leaf
 *
 * @param t The tree to check
 *
 * @return 0 (false) ou 1 (true)
 */
int isLeaf(Tree* t);

/**
 * @brief Find the lowest common ancestor - Complexity θ(n)
 * @description We traverse from root to leaf(s).
 * When we find a node matching at least one, we pass it to its parent.
 * The parent tests if left or right child contains the value.
 * If yes, the parent is the LCA, else, we pass its parent, up to root.
 * What is pass is the lower node or NULL
 *
 * @param root The root of the tree
 * @param t1 The first tree
 * @param t2 The second tree
 *
 * @return The lowest common ancestor (node or leaf)
 */
Tree* LCA(Tree* root, Tree* t1, Tree* t2);

/**
 * @brief Remove from the memory, the space used by the tree
 *
 * @param t Pointer of the tree
 */
void freeTree(Tree* t);

#endif // _TREE_H_
