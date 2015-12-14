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

Tree* LCA(Tree* root, Tree* t1, Tree* t2) {
  if(!root) {
  	return NULL;
  }
  // we check if we find at least one
  if (root->value == t1->value || root->value == t2->value) {
  	return root;
  }	
  // else we keep going down
  Tree* left = LCA(root->lf_child, t1, t2);
  Tree* right = LCA(root->rg_child, t1, t2);
  // if left and right both contain t1 and t2
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