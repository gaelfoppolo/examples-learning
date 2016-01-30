/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our model - Implementation
 */

#include "model.h"

void initModel(Model* mo) {
	vectInit(mo->ma);
}

void freeModel(Model* mo) {
	if(!mo) return;
	for(unsigned int i = 0; i < vectSize(mo->ma); ++i) {
		if(vectAt(mo->ma, i).name) {
			free(vectAt(mo->ma, i).name);
		}
		switch(vectAt(mo->ma, i).mt.type) {
			case TYPE_INT: break;
			case TYPE_ENUM:
				for(unsigned int j = 0; j < vectSize(vectAt(mo->ma, i).mt.enu.enu); ++j) {
					if(vectAt(vectAt(mo->ma, i).mt.enu.enu, j).str) {
						free(vectAt(vectAt(mo->ma, i).mt.enu.enu, j).str);
					}
				}
				vectFree(vectAt(mo->ma, i).mt.enu.enu);
				break;
			case TYPE_TREE:
				if(vectAt(mo->ma, i).mt.tree.left) {
					freeTree(vectAt(mo->ma, i).mt.tree.left);
				}
				if(vectAt(mo->ma, i).mt.tree.right) {
					freeTree(vectAt(mo->ma, i).mt.tree.right);
				}
				if(vectAt(mo->ma, i).mt.tree.str) {
					free(vectAt(mo->ma, i).mt.tree.str);
				}
				break;
		}
	}
	vectFree(mo->ma);
	free(mo);
}

int getEnumId(const char* str, Model* m, unsigned int index) {
	Enum* current = &vectAt(m->ma, index).mt.enu;
	for(unsigned int i = 0; i < vectSize(current->enu); ++i) {
		if(strcmp(str, vectAt(current->enu, i).str) == 0) {
			return vectAt(current->enu, i).id;
		}
	}

	return -1;
}

int getTreeId(const char* str, Model* m, unsigned int index) {
	return __getTreeId_rec(str, &vectAt(m->ma, index).mt.tree);
}

int __getTreeId_rec(const char* str, Tree* t) {
	if(t) {
		if(strcmp(str, t->str) == 0) {
			return t->id;
		}
		int rec = __getTreeId_rec(str, t->left);
		if(rec > -1) {
			return rec;
		}
		rec = __getTreeId_rec(str, t->right);
		return rec;
	}

	return -1;
}
