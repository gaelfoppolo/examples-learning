/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "core.h"

Solution* genSolution(Examples* exp) {
 	// an example
 	Example e;
 	// an object of an example
 	Object o;
    initObject();
 	// a solution object, gathering traits from all examples
 	Solution* sol = (Solution*)malloc(sizeof(Solution));
    initSolution(sol);
    // init with the first object
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
                Attribute att = vectAt(o.attributes, k);
                switch(att.type) {
                    case TYPE_INT:
                        // add into interval
                        break;
                    case TYPE_ENUM:
                        // push into enum
                        break;
                    case TYPE_TREE:
                        // LCA
                        break;
                    default:
                        // handle error ?
                        break;
                }
            }

        }
    }
    return sol;
 }

 Solution* initSol(Solution* sol, Object o) {
    OutObject oo;
    Attribute att;
    Interval inter;
    OutEnum oenu;
    for(int i = 0; i < vectSize(o.attributes); ++i) {
        oo = (OutObject*)malloc(sizeof(OutObject));
        att = vectAt(o.attributes, i);

        oo = att.type;
        
        switch(att.type) {
            case TYPE_INT:
                inter = (Interval*)malloc(sizeof(Interval));
                inter.min = att.value;
                inter.max = att.value;
                oo.inter = inter;
                break;
            case TYPE_ENUM:
                oenu = (OutEnum*)malloc(sizeof(OutEnum));
                initOutEnum(oenu);
                vectPush(int, oenu, att.value);
                vectPush(OutEnum, oo.oenu, oenu);
                break;
            case TYPE_TREE:
                oo.tree = att.value;
                break;
            default:
                // handle error ?
                break;
        }
        // finally push OutputObject to Solution
        vectPush(OutObject, sol.outobjects, oo);
    }
    free(oo);
    free(inter);
    free(oenu);
 }

 void addToInterval(int *min, int*max, int x) {
 	if(x < *min) *min = x;
 	else if(*max < x) *max = x;
 }

 int colorIsInVector(OutObject* v, Color c) {
 	int found = 0;
 	for(int i = 0; i < vectSize(v->colors) && !found; ++i) {
 		found = (vectAt(v->colors, i) == c);
 	}
 	return found;
 }