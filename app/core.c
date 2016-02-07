/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin 	PHILIP Bastien
 *
 * @brief The core
 */

#include "core.h"

int nbCombi(Examples* exp, int step) {
	// init with 1, neutral of multiplication
	int nbCombi = 1;
	for (int i = step; i < vectSize(exp->examples); ++i) {
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

static void __genAllRelations_rec(Solution* s, Examples* e, Model* m, ObjectIndice* indices, unsigned int currentIndex) {
	int allRel;
	ObjectIndice relIndices;
	// end of the examples
	if(currentIndex == vectSize(e->examples)) {
		// loop through all the relations
		for(unsigned int i = 0; i < vectSize(m->rel); ++i) {
			vectInit(relIndices.indices);
			allRel = 1;
			for(unsigned int j = 0; j < vectSize(indices->indices); ++j) {
				// check whether the current object has a relation defined for the ith relation
				if(vectAt(vectAt(vectAt(e->examples, j).objects, vectAt(indices->indices, j)).relations, i).type != TYPE_RELATION) {
					allRel = 0;
					break;
				}
				else {
					vectPush(int, relIndices.indices, vectAt(vectAt(vectAt(e->examples, j).objects, vectAt(indices->indices, j)).relations, i).value);
				}
			}

			if(allRel) { // every objects have the relation
				// get the combination of the objects linked and assign it to the relation of the current combination
				vectAt(vectAt(s->outobjects, getIndex(e, indices)).relations, i) = &vectAt(s->outobjects, getIndex(e, &relIndices));
			}
			vectFree(relIndices.indices);
		}

		return;
	}

	for(unsigned int i = 0; i < vectSize(vectAt(e->examples, currentIndex).objects); ++i) {
		vectPush(int, indices->indices, i);
		__genAllRelations_rec(s, e, m, indices, currentIndex + 1);
		vectRemoveLast(indices->indices);
	}
}

void genAllRelations(Solution* s, Examples* e, Model* m) {
	ObjectIndice stack;
	vectInit(stack.indices);

	__genAllRelations_rec(s, e, m, &stack, 0);

	vectFree(stack.indices);
}

int getIndex(Examples* exp, ObjectIndice* oi) {
	int index = 0, inside, i;
	for (i = 0; i <= vectSize(exp->examples)-2; ++i) {
		inside = 1;
		for (int j = i+1; j <= vectSize(exp->examples)-1; ++j) {
			inside *= vectSize(vectAt(exp->examples, j).objects);
		}
		index += vectAt(oi->indices, i)*inside;
	}
	return index+vectAt(oi->indices, i);
}

int genSpecificity(Model* mdl, OutObject* oo) {
	float specificity = 0, tmp;
	int relCount = 0;
	OutAttribute oa;
	ModelType mt;
	// for all attributes
	for (int i = 0; i < vectSize(oo->attributes); ++i) {
		oa = vectAt(oo->attributes, i);
		mt = vectAt(mdl->ma, i).mt;

		// for each we use weighted values
		switch(oa.type) {
			case TYPE_INT:
				// (oo max - oo min) / (model max - model min)
				tmp = (float)(oa.inter.max-oa.inter.min)/(float)(mt.inter.max-mt.inter.min);
				break;
			case TYPE_ENUM:
				// (oo size of enum) / (model size of enum)
				tmp = (float)(vectSize(oa.oenu.oenu))/(float)vectSize(mt.enu.enu);
				break;
			case TYPE_TREE:
				// (oo node depth in tree) / (model tree depth)
				// if depth = height, we get 1.0, but because it is the best, 0.0 to fit our spec
				// if depth = 0, we get 0.0, but because it is the worst, 1.0 to fit our spec
				tmp = 1.0-(float)(depth(&mt.tree, oa.tree))/(float)height(&mt.tree);
				break;
		}
		// if tmp = 0, it means it is the best, so set to 1
		// if tmp = 1, it means it is the worst, so set to 0
		specificity += (tmp == 0.0 || tmp == 1.0) ? fabs(tmp-1.0) : 1.0-tmp;	
	}

	// add relations
	for (int i = 0; i < vectSize(oo->relations); ++i) {
		if (vectAt(oo->relations , i) != NULL) relCount++;
	}

	// ((relCount) / (model size of rel))
	specificity += (float)relCount/(float)vectSize(mdl->rel);


	// if specificity = 0.0, that means it's the worst so we set specificity to 1
	// because 0.0 means duplicate in our model specification
	return (specificity == 0.0) ? 1 : (int)(specificity/(float)(vectSize(oo->attributes)+1)*100);
}