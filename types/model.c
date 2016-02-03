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

	// free attributes
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
				freeTree(&vectAt(mo->ma, i).mt.tree);
				break;
		}
	}

	// free relations
	for(unsigned int i = 0; i < vectSize(mo->rel); ++i) {
		free(vectAt(mo->rel, i));
	}

	vectFree(mo->ma);
	vectFree(mo->rel);
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
		int rec;
		for(unsigned int i = 0; i < vectSize(t->children); ++i) {
			rec = __getTreeId_rec(str, &vectAt(t->children, i));
			if(rec > -1) {
				return rec;
			}
		}
	}

	return -1;
}

char* getEnumStr(int id, Model* m, unsigned int index) {
	Enum* current = &vectAt(m->ma, index).mt.enu;
	for(unsigned int i = 0; i < vectSize(current->enu); ++i) {
		if(vectAt(current->enu, i).id == id) {
			return vectAt(current->enu, i).str;
		}
	}

	return NULL;
}

char* getTreeStr(int id, Model* m, unsigned int index) {
	return __getTreeStr_rec(id, &vectAt(m->ma, index).mt.tree);
}

char* __getTreeStr_rec(int id, Tree* t) {
	if(t) {
		if(t->id == id) {
			return t->str;
		}
		char* rec;
		for(unsigned int i = 0; i < vectSize(t->children); ++i) {
			rec = __getTreeStr_rec(id, &vectAt(t->children, i));
			if(rec) {
				return rec;
			}
		}
	}

	return NULL;
}
