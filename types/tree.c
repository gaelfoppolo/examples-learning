/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions used by the binary tree
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Tree* createLeaf(int id, char* str) {
	Tree* t;
 	t = (Tree*)malloc(sizeof(Tree));
 	t->id = id;
	t->str = str;
 	t->left = NULL;
 	t->right = NULL;
	return t;
}

Tree* createNode(int id, char* str, Tree* left, Tree* right) {
	Tree* t;
	t = (Tree*)malloc(sizeof(Tree));
	t->id = id;
	t->str = str;
	t->left = left;
	t->right = right;
	return t;
}

int isLeaf(Tree* t) {
	return (t->left == NULL) && (t->right = NULL);
}

Tree* LCA(Tree* root, int id1, int id2) {
	if(!root) {
		return NULL;
	}

	// we check if we find at least one
	if(root->id == id1 || root->id == id2) {
		return root;
	}

	// else we keep going down
	Tree* left = LCA(root->left, id1, id2);
	Tree* right = LCA(root->right, id1, id2);
	// if left and right both contain v1 and v2
	// current root is LCA
	if(left && right) {
		return root;
	}

	// else we return the node that contain the value
	// or NULL if none of them contain
	return left ? left : right;
}

void freeTree(Tree* t) {
	if(t->left) freeTree(t->left);
	if(t->right) freeTree(t->right);
	free(t);
}
