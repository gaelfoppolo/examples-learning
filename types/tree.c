/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief Structure of our N-ary tree - Implementation
 */

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

Tree* getTreeFromID(Tree* root, int id) {
	if(root->id == id) {
		return root;
	}
	else {
		Tree* tree;
		for (unsigned int i = 0; i < vectSize(root->children); ++i) {
			tree = getTreeFromID(&vectAt(root->children, i), id);
		}
		return tree;
	}
}

int height(Tree* t) {
    
    if(isLeaf(t)){
		return 0;
	}
	else {
		int heightTree = 0;
		for (unsigned int i = 0; i < vectSize(t->children); ++i) {
			heightTree = max(heightTree, height(&vectAt(t->children, i)));
		}
		return heightTree+1;
	}
}

/**
*	@brief NOT FOR USE - Used by depth - Recursively go down into the tree with the current depth
*	@param t The tree (node) to search into
*	@param id The id of the node
*	@param dpth The current depth of t
*
*	@return Returns the depth of the node matching the id
*/
static int depth_rec(Tree* t, int id, int dpth);

int depth(Tree* root, int id) {
	// launch the search with a depth of 0
	return depth_rec(root, id, 0);
}

int depth_rec(Tree* t, int id, int dpth) {
	// node found, dpth is our depth
	if (t->id == id) {
		return dpth;
	}
	// no children so our node can't be here
	// return neutral of depth
	else if (vectSize(t->children) == 0) {
		return 0;
	}
	// search in each child, increasing depth by one, since we go down
	else {
		int depthTree = 0;
		for (unsigned int i = 0; i < vectSize(t->children); ++i) {
			depthTree = max(depthTree, depth_rec(&vectAt(t->children, i), id ,dpth+1));
		}
		return depthTree;
	}
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

int compareNode(Tree* t, int node1, int node2) {

	// same id? -> 0
	// so different id? then:
		// is the depth the same or smaller? -> 0
		// is the depth bigger? -> 1

	int depth1, depth2, tmp;
	

	if(node1 == node2) {
		tmp = 0;
	} else {
		depth1 = depth(t, node1);
		depth2 = depth(t, node2);
		tmp = (depth1 >= depth2) ? 0 : 1;
	}

	return tmp;			

}