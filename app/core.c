/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "core.h"

int nbCombi(Examples* exp) {
    // init with 1, neutral of multiplication
    int nbCombi = 1;
    for (int i = 0; i < vectSize(exp->examples); ++i) {
        nbCombi *= vectSize(vectAt(exp->examples, i).objects);
    }
    return nbCombi;
}

Solution* genEmptySol(Solution* sol, int nbCombi) {
    OutObject oo;
    OutAttribute oa;
    vectPush(OutAttribute, oo.attributes, oa);
    for (int i = 0; i < nbCombi; ++i) {
        vectPush(OutObject, sol->outobjects, oo);
    }
    return sol;
}

OutObject* genOutObject(Object* in) {
    OutObject* oo = (OutObject*)malloc(sizeof(OutObject));
    initOutObject(oo);
    OutAttribute oa;
    Attribute att;

    for(int i = 0; i < vectSize(in->attributes); ++i) {
        att = vectAt(in->attributes, i);
        oa.type = att.type;

        switch(att.type) {
            case TYPE_INT:
                oa.inter.min = att.value;
                oa.inter.max = att.value;
                break;
            case TYPE_ENUM:
                initOutEnum(&oa.oenu);
                vectPush(int, oa.oenu.oenu, att.value);
                break;
            case TYPE_TREE:
                oa.tree = att.value;
                break;
        }
        // finally push OutAttribute to the OutObject
        vectPush(OutAttribute, oo->attributes, oa);
    }
    return oo;
}

void genCombi(OutObject* first, Object* second, Model* mdl) {
    OutAttribute* oa = (OutAttribute*)malloc(sizeof(OutAttribute));
    Attribute att;
    int pt;
    for (int i = 0; i < vectSize(first->attributes); ++i) {
        oa = &vectAt(first->attributes, i);
        att = vectAt(second->attributes, i);

        switch(oa->type) {
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
    free(oa);
}

/*
Solution* genSolution(Model* mdl, Examples* exp) {
 	// an example
 	Example e;
    // an attribute
    Attribute att;
    // an output object
    OutObject* oo;
 	// an object of an example
 	Object o;
    // an integer
    int pt;
 	// a solution object, gathering traits from all examples
 	Solution* sol = (Solution*)malloc(sizeof(Solution));
    initSolution(sol);
    // init with the first object
    o = vectAt(vectAt(exp->examples, 0).objects, 0);
    sol = initSol(sol, o);

 	for(int i = 0; i < vectSize(exp->examples); ++i) {
        // current example
        e = vectAt(exp->examples, i);

        // for all objects of the example
        for(int j = 0; j < vectSize(e.objects); ++j) {
        	// current object of the example
            o = vectAt(e.objects, j);

            // for all attributes of the object
            for(int k = 0; k < vectSize(o.attributes); ++k) {
                // current attribute of the object
                att = vectAt(o.attributes, k);
                // matching output object in the solution (same rank)
                oo = &vectAt(sol->outobjects, k);

                switch(att.type) {
                    case TYPE_INT:
                        addToInterval(&oo->inter, att.value);
                        break;
                    case TYPE_ENUM:
                        vectIndexOf(oo->oenu.oenu, att.value, pt);
                        if (pt == -1) vectPush(int, oo->oenu.oenu, att.value);
                        break;
                    case TYPE_TREE:
                        // looking for tree model (root) in the model (same rank), then LCA
                        oo->tree = LCA(&vectAt(mdl->ma, k).mt.tree, oo->tree, att.value)->id;
                        break;
                }
            }
        }
    }

    return sol;
 }

 Solution* initSol(Solution* sol, Object o) {
    OutObject oo; // default object
    Attribute att;

    for(int i = 0; i < vectSize(o.attributes); ++i) {
        att = vectAt(o.attributes, i);
        oo.type = att.type;

        switch(att.type) {
            case TYPE_INT:
                oo.inter.min = att.value;
                oo.inter.max = att.value;
                break;
            case TYPE_ENUM:
                initOutEnum(&oo.oenu);
                vectPush(int, oo.oenu.oenu, att.value);
                break;
            case TYPE_TREE:
                oo.tree = att.value;
                break;
        }
        // finally push OutputObject to Solution
        vectPush(OutObject, sol->outobjects, oo);
    }

    return sol;
 }
 */
