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
	vectFill(OutObject, T->outobjects, allCombi);
	Example lastExample = vectAt(exp->examples, vectSize(exp->examples)-1);
	int sizeLastExample = vectSize(lastExample.objects);
	
	Object* o;
	OutObject* oo;

	for (int i = 0; i < (vectSize(T->outobjects)/sizeLastExample); ++i) {

		for (int j = 0; j < sizeLastExample; ++j) {
			// get the adress of the j object in the last exemple
			o = &vectAt(lastExample.objects, j);
			oo = initOutObjectWithObject(mdl, o);
			oo->generalizeBy = (OutObject*)NULL;
			oo->disabled = 0;
			oo->name = cPrint("S%0*d", (int)log10(allCombi) + 1, sizeLastExample*i+j +1);
			
			vectAt(T->outobjects, sizeLastExample*i+j) = *oo;
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

int isOutObjectIncludeInAnother(Model* mdl, OutObject* oo1, OutObject* oo2) {
	OutAttribute oa1, oa2;

	int countAttributesInclude = 0;

	// for all attributes
	for(int i = 0; i < vectSize(oo1->attributes); ++i) {
		
		oa1 = vectAt(oo1->attributes, i);
		oa2 = vectAt(oo2->attributes, i);

		// test if each attributes is include
		switch(oa1.type) {
			
			case TYPE_INT:
				countAttributesInclude += isIntervalIncludeInAnother(oa1.inter, oa2.inter);
				break;
			case TYPE_ENUM:
				countAttributesInclude += isOutEnumIncludeInAnother(oa1.oenu, oa2.oenu);
				break;
			case TYPE_TREE:
				countAttributesInclude += isNodeDepthSameOrSmaller(&vectAt(mdl->ma, i).mt.tree, oa1.tree, oa2.tree);
				break;
		}		
	}
	
	// if all are include sum is equal to number of attributes
	return (countAttributesInclude == vectSize(oo1->attributes));
}

void genGeneralization(Model* mdl, Solution* s) {
	int isInclude;

	// for each OutObjects
	for (int i = 0; i < vectSize(s->outobjects)-1; ++i) {
		
		// for each OO(j)
		// and only if OO(i) is not already include in another OO
		for (int j = 0; j < vectSize(s->outobjects) && (&vectAt(s->outobjects, i))->generalizeBy == NULL; ++j) {
			
			// OO(i) and OO(j) not the same
			// and the two OutObjects have exactly the same relations
			if (i != j && haveSameRelations(&vectAt(s->outobjects, i), &vectAt(s->outobjects, j))) {
				
				// test inclusion of OO(i) in OO(j)
				isInclude = isOutObjectIncludeInAnother(mdl, &vectAt(s->outobjects, j), &vectAt(s->outobjects, i));
				
				// if OO(i) include in OO(j) 
				if (isInclude) {

					// then OO(i) point to OO(j)
					(&vectAt(s->outobjects, i))->generalizeBy = &vectAt(s->outobjects, j);
				}		
			}	
		}	
	}
}


void genCounterExamples(Model* m, Examples* e, Solution* s) {
	for(unsigned int oo = 0; oo < vectSize(s->outobjects); ++oo) {
		// check whether the object is important or have been generalized
		if(vectAt(s->outobjects, oo).generalizeBy != NULL) {
			continue;
		}
		// go through all the counter-examples defined
		for(unsigned int i = 0; i < vectSize(e->counterExamples); ++i) {
			// go through all the objects of the current counter-example
			for(unsigned int j = 0; j < vectSize(vectAt(e->counterExamples, i).objects); ++j) {
				if(isObjectInOutObject(m, &vectAt(s->outobjects, oo), &vectAt(vectAt(e->counterExamples, i).objects, j))) {
					vectAt(s->outobjects, oo).disabled = 1;
				}
			}
		}
	}
}

int isObjectInOutObject(Model* m, OutObject* oo, Object* o) {
	int inside;
	Tree* t;

	// check if the same relations are declared
	for(unsigned int i = 0; i < vectSize(o->relations); ++i) {
		if((vectAt(o->relations, i).type == TYPE_RELATION && vectAt(oo->relations, i) == NULL) ||
			(vectAt(o->relations, i).type == TYPE_NORELATION && vectAt(oo->relations, i))) {
			return 0;
		}
	}

	// check if the attributes are the same
	for(unsigned int i = 0; i < vectSize(o->attributes); ++i) {
		switch(vectAt(o->attributes, i).type) {
			case TYPE_INT:
				// if the value of the object is out of the bounds of the interval in the OutObject, the object is not in
				if(vectAt(o->attributes, i).value < vectAt(oo->attributes, i).inter.min || vectAt(o->attributes, i).value > vectAt(oo->attributes, i).inter.max) {
					return 0;
				}
				break;
			case TYPE_ENUM:
				// if the current enumeration item is not in the list of enumeration items of the OutObject
				vectIndexOf(vectAt(oo->attributes, i).oenu.oenu, vectAt(o->attributes, i).value, inside);
				if(inside < 0) {
					return 0;
				}
				break;
			case TYPE_TREE:
				// if the current node is not a child of the node of the OutObject
				t = LCA(&vectAt(m->ma, i).mt.tree, vectAt(oo->attributes, i).tree, vectAt(o->attributes, i).value);
				if(!t || t->id != vectAt(oo->attributes, i).tree) {
					return 0;
				}
				break;
		}
	}

	return 1;
}