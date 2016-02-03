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
	vectInit(t->children);
	return t;
}

Tree* createNode(int id, char* str, Tree* child) {
	Tree* t;
	t = (Tree*)malloc(sizeof(Tree));
	t->id = id;
	t->str = str;
	vectInit(t->children);
	vectPush(Tree, t->children, *child);
	return t;
}

Tree* addChild(Tree* node, Tree* child) {
	vectPush(Tree, node->children, *child);
	return node;
}

int isLeaf(Tree* t) {
	return vectSize(t->children) == 0;
}

Tree* LCA(Tree* root, int id1, int id2) {

	// we check if we find at least one
	if(root->id == id1 || root->id == id2) {
		return root;
	}

	// else we keep going down
	Tree* firstValue = NULL;
	Tree* secondValue = NULL;
	Tree* tmp;
	for(unsigned int i = 0; i < vectSize(root->children); ++i) {
		tmp = LCA(&vectAt(root->children, i), id1, id2);
		if(tmp) {
			if(!firstValue) {
				firstValue = tmp;
			}
			else if(!secondValue) {
				secondValue = tmp;
				break;
			}
		}
	}
	// if the two ids are in two different children of the root
	// current root is LCA
	if(firstValue && secondValue) {
		return root;
	}

	// else we return the node that contain the value
	// or NULL if none of them contain
	return firstValue;
}

void freeTree(Tree* t) {
	if(t->str) free(t->str);
	for(unsigned int i = 0; i < vectSize(t->children); ++i) {
		freeTree(&vectAt(t->children, i));
	}
	vectFree(t->children);
}
