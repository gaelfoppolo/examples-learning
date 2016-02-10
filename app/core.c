/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief The core
 */

#include "core.h"

int nbCombi(Examples* exp, int expIndice) {
	// init with 1, neutral of multiplication
	int nbCombi = 1;
	for (int i = expIndice; i < vectSize(exp->examples); ++i) {
		nbCombi *= vectSize(vectAt(exp->examples, i).objects);
	}
	return nbCombi;
}

OutObject* initOutObjectWithObject(Model* mdl, Object* o) {
	OutObject* oo = (OutObject*)malloc(sizeof(OutObject));
	initOutObject(oo);
	OutAttribute* oa = (OutAttribute*)malloc(sizeof(OutAttribute));
	Attribute att;

	for(int i = 0; i < vectSize(o->attributes); ++i) {
		att = vectAt(o->attributes, i);
		oa->type = att.type;

		switch(att.type) {
			case TYPE_INT:
				oa->inter.min = att.value;
				oa->inter.max = att.value;
				break;
			case TYPE_ENUM:
				initOutEnum(&oa->oenu);
				vectPush(int, oa->oenu.oenu, att.value);
				break;
			case TYPE_TREE:
				oa->tree = att.value;
				break;
		}
		vectPush(OutAttribute, oo->attributes, *oa);
		
	}
	for (int j = 0; j < vectSize(mdl->rel); ++j) {
			vectPush(OutObject*, oo->relations, (OutObject*)NULL);
	}

	free(oa);

	return oo;
}

Solution* initAllCombi(Model* mdl, Examples* exp) {
	int allCombi = nbCombi(exp, 0);
	Solution* T = (Solution*)malloc(sizeof(Solution));
	initSolution(T);
	Example lastExample = vectAt(exp->examples, vectSize(exp->examples)-1);
	int sizeLastExample = vectSize(lastExample.objects);
	
	Object* o;
	OutObject* oo;

	while(vectSize(T->outobjects) < allCombi) {

		for (int i = 0; i < sizeLastExample; ++i) {
			// get the adress of the i object in the last exemple
			o = &vectAt(lastExample.objects, i);
			oo = initOutObjectWithObject(mdl, o);
			oo->specificity = 1;
			oo->name = cPrint("S%d", vectSize(T->outobjects)+1);
			vectPush(OutObject, T->outobjects, *oo);
			free(oo);
		}
	}
	return T;

}

void combiOutObjectObject(Model* mdl, OutObject* oo, Object*o) {
	OutAttribute* oa = (OutAttribute*)malloc(sizeof(OutAttribute));
	Attribute att;
	int pt;

	for(int i = 0; i < vectSize(o->attributes); ++i) {
		att = vectAt(o->attributes, i);
		oa = &vectAt(oo->attributes, i);

		switch(att.type) {
			case TYPE_INT:
				addToInterval(&oa->inter, att.value);
				break;
			case TYPE_ENUM:
				vectIndexOf(oa->oenu.oenu, att.value, pt);
				if (pt == -1) vectPush(int, oa->oenu.oenu, att.value);
				break;
			case TYPE_TREE:
				// looking for tree model (root) in the model (same rank), then LCA
				oa->tree = LCA(&vectAt(mdl->ma, i).mt.tree, oa->tree, att.value)->id;
				break;
		}		
	}

}

Solution* genAllCombi(Model* mdl, Examples* exp) {
	Solution* T = initAllCombi(mdl, exp);
	int fact, factNext, nbExamples = vectSize(exp->examples), nbAllCombi = nbCombi(exp, 0);
	Example e;
	// begin from last last examples to first one
	for (int step = nbExamples-2; step >= 0; --step) {
		e = vectAt(exp->examples, step);
		fact = nbCombi(exp, step+1);
		factNext = nbCombi(exp, step);

		for (int i = 0; i < nbAllCombi/factNext; ++i) {
			
			// for all the object of that example
			for (int j = 0; j < vectSize(e.objects); ++j) {

				for (int k = 0; k < fact; ++k) {
					
					// combi the OutObject with the current Object
					combiOutObjectObject(mdl, &vectAt(T->outobjects, i*factNext+j*fact+k), &vectAt(e.objects, j));
				}
			}			
		}
	}
	return T;
}

static void __genAllRelations_rec(Solution* s, Examples* e, Model* m, ObjectIndex* indexes, unsigned int currentIndex) {
	int allRel;
	ObjectIndex relindexes;
	// end of the examples
	if(currentIndex == vectSize(e->examples)) {
		// loop through all the relations
		for(unsigned int i = 0; i < vectSize(m->rel); ++i) {
			vectInit(relindexes.indexes);
			allRel = 1;
			for(unsigned int j = 0; j < vectSize(indexes->indexes); ++j) {
				// check whether the current object has a relation defined for the ith relation
				if(vectAt(vectAt(vectAt(e->examples, j).objects, vectAt(indexes->indexes, j)).relations, i).type != TYPE_RELATION) {
					allRel = 0;
					break;
				}
				else {
					vectPush(int, relindexes.indexes, vectAt(vectAt(vectAt(e->examples, j).objects, vectAt(indexes->indexes, j)).relations, i).value);
				}
			}

			if(allRel) { // every objects have the relation
				// get the combination of the objects linked and assign it to the relation of the current combination
				vectAt(vectAt(s->outobjects, getIndex(e, indexes)).relations, i) = &vectAt(s->outobjects, getIndex(e, &relindexes));
			}
			vectFree(relindexes.indexes);
		}
		return;
	}

	for(unsigned int i = 0; i < vectSize(vectAt(e->examples, currentIndex).objects); ++i) {
		vectPush(int, indexes->indexes, i);
		__genAllRelations_rec(s, e, m, indexes, currentIndex + 1);
		vectRemoveLast(indexes->indexes);
	}
}

void genAllRelations(Solution* s, Examples* e, Model* m) {
	ObjectIndex stack;
	vectInit(stack.indexes);

	__genAllRelations_rec(s, e, m, &stack, 0);

	vectFree(stack.indexes);
}

int getIndex(Examples* exp, ObjectIndex* oi) {
	int index = 0, inside, i;
	for (i = 0; i <= vectSize(exp->examples)-2; ++i) {
		inside = 1;
		for (int j = i+1; j <= vectSize(exp->examples)-1; ++j) {
			inside *= vectSize(vectAt(exp->examples, j).objects);
		}
		index += vectAt(oi->indexes, i)*inside;
	}
	return index+vectAt(oi->indexes, i);
}

int compareOutObjects(Model* mdl, OutObject* oo1, OutObject* oo2) {
	OutAttribute oa1, oa2;

	int tmp = 0;

	// for all attributes
	for(int i = 0; i < vectSize(oo1->attributes); ++i) {
		
		oa1 = vectAt(oo1->attributes, i);
		oa2 = vectAt(oo2->attributes, i);

		switch(oa1.type) {
			
			case TYPE_INT:
				tmp += compareInterval(oa1.inter, oa2.inter);
				break;
			case TYPE_ENUM:
				tmp += compareOutEnum(oa1.oenu, oa2.oenu);
				break;
			case TYPE_TREE:
				tmp += compareNode(&vectAt(mdl->ma, i).mt.tree, oa1.tree, oa2.tree);
				break;
		}		
	}

	// here we can have:
		// x = 0: so return 0
		// x => 1: so return 1
	
	return (tmp == 0) ? 0 : 1;
}

void genGeneralisation(Model* mdl, Solution* s) {
	// for each OutObjects
	for (int i = 0; i < vectSize(s->outobjects)-1; ++i) {
		// if the OutObject is still usefull
		if ((&vectAt(s->outobjects, i))->specificity != 0) {
			// compare it to all next OutObjects
			for (int j = i+1; j < vectSize(s->outobjects); ++j) {
				// but only if the OutObject to compare to is usefull
				// and the two OutObjects have exactly the same relations
				if ((&vectAt(s->outobjects, j))->specificity != 0 && haveSameRelations(&vectAt(s->outobjects, i), &vectAt(s->outobjects, j))) {
					// will change specificity of the second OutObject
					(&vectAt(s->outobjects, j))->specificity = compareOutObjects(mdl, &vectAt(s->outobjects, i), &vectAt(s->outobjects, j));
				}	
			}
		}	
	}
}