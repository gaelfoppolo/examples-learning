/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "core.h"

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
    int* pt = (int*)malloc(sizeof(int));
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
                        vectIndexOf(oo->oenu.oenu, att.value, *pt);
                        if (*pt) vectPush(int, oo->oenu.oenu, att.value);
                        break;
                    case TYPE_TREE:
                        // looking for tree model (root) in the model (same rank), then LCA
                        oo->tree = LCA(&vectAt(mdl->ma, k).mt.tree, oo->tree, att.value)->id;
                        break;
                }
            }

        }
    }

    free(pt);
    free(oo);
    return sol;
 }

 Solution* initSol(Solution* sol, Object o) {
    OutObject* oo;
    Attribute att;
    Interval* inter;
    OutEnum* oenu;
    for(int i = 0; i < vectSize(o.attributes); ++i) {
        oo = (OutObject*)malloc(sizeof(OutObject));
        att = vectAt(o.attributes, i);
        
        switch(att.type) {
            case TYPE_INT:
                inter = (Interval*)malloc(sizeof(Interval));
                inter->min = att.value;
                inter->max = att.value;
                oo->inter = *inter;
                break;
            case TYPE_ENUM:
                oenu = (OutEnum*)malloc(sizeof(OutEnum));
                initOutEnum(oenu);
                vectPush(int, oenu->oenu, att.value);
                oo->oenu = *oenu;
                break;
            case TYPE_TREE:
                oo->tree = att.value;
                break;
        }
        // finally push OutputObject to Solution
        vectPush(OutObject, sol->outobjects, *oo);
    }

    free(oo);
    free(inter);
    free(oenu);
    return sol;
 }