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
