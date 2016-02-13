/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "model.h"

/**
*	@brief NOT FOR USE - Used by getTreeStr - Recursively search in the tree to find the str that match the id.
*	@param id The enum id to which the str is wanted
*	@param t The root of the tree in which to search
*
*	@return Returns the str if found, NULL otherwise
*/
static char* __getTreeStr_rec(int id, Tree* t);

/**
*	@brief NOT FOR USE - Used by getTreeId - Recursively search in the tree to find the id that match the value's name.
*	@param str The enum value to which the id is wanted
*	@param t The root of the tree in which to search
*
*	@return Returns the id if found, -1 otherwise
*/
static int __getTreeId_rec(const char* str, Tree* t);

void initModel(Model* mdl) {
	vectInit(mdl->ma);
}

void freeModel(Model* mdl) {
	if(!mdl) return;

	// free attributes
	for(unsigned int i = 0; i < vectSize(mdl->ma); ++i) {
		freeModelAttribute(&vectAt(mdl->ma, i), 0);
	}

	// free relations
	for(unsigned int i = 0; i < vectSize(mdl->rel); ++i) {
		free(vectAt(mdl->rel, i));
	}

	vectFree(mdl->ma);
	vectFree(mdl->rel);
	free(mdl);
}

int getEnumId(const char* str, Model* mdl, unsigned int index) {
	Enum* current = &vectAt(mdl->ma, index).mt.enu;
	for(unsigned int i = 0; i < vectSize(current->enu); ++i) {
		if(strcmp(str, vectAt(current->enu, i).str) == 0) {
			return vectAt(current->enu, i).id;
		}
	}

	return -1;
}

static int __getTreeId_rec(const char* str, Tree* t) {
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

int getTreeId(const char* str, Model* mdl, unsigned int index) {
	return __getTreeId_rec(str, &vectAt(mdl->ma, index).mt.tree);
}

char* getEnumStr(int id, Model* mdl, unsigned int index) {
	Enum* current = &vectAt(mdl->ma, index).mt.enu;
	for(unsigned int i = 0; i < vectSize(current->enu); ++i) {
		if(vectAt(current->enu, i).id == id) {
			return vectAt(current->enu, i).str;
		}
	}

	return NULL;
}

char* getTreeStr(int id, Model* mdl, unsigned int index) {
	return __getTreeStr_rec(id, &vectAt(mdl->ma, index).mt.tree);
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
