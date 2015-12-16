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

Tree* createLeaf(int val) {
	Tree* t;
 	t = (Tree*)malloc(sizeof(Tree));
 	t->value = val;
 	t->lf_child = NULL;
 	t->rg_child = NULL;
 	return t;
}

Tree* createNode(int val, Tree* lfc, Tree* rgc) {
 	Tree* t;
 	t = (Tree*)malloc(sizeof(Tree));
 	t->value = val;
 	t->lf_child = lfc;
 	t->rg_child = rgc;
 	return t;
}

int isLeaf(Tree* t) {
 	return (t->lf_child == NULL) && (t->rg_child = NULL);
}

Tree* LCA(Tree* root, int v1, int v2) {
  if(!root) {
  	return NULL;
  }
  // we check if we find at least one
  if (root->value == v1 || root->value == v2) {
  	return root;
  }	
  // else we keep going down
  Tree* left = LCA(root->lf_child, v1, v2);
  Tree* right = LCA(root->rg_child, v1, v2);
  // if left and right both contain v1 and v2
  // current root is LCA
  if (left && right) { 
  	return root;
  }
  // else we return the node that contain the value
  // or NULL if none of them contain
  return left ? left : right;
}

void freeTree(Tree* t) {
	if(t->lf_child != NULL) freeTree(t->lf_child);
	if(t->rg_child != NULL) freeTree(t->rg_child);
	free(t);
}