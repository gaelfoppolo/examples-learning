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
 	// an object of an example
 	Object o;
 	// a solution object, gathering traits from all examples
 	Solution* sol = (Solution*)malloc(sizeof(Solution));
    initObject(sol);

    // first object of the first example is our basic solution
    o = vectAt(vectAt(exp->examples, 0).objects, 0);
    // just need to push its attributes into our solution
    vectPush(Attribute, sol->attributes, o->attributes);

 	for(int i = 0; i < vectSize(exp->examples); ++i) {
        // current example
        e = vectAt(exp->examples, i);
        // for all objects of the example

        for(int j = 0; j < vectSize(e.objects); ++j) {
        	// current object of the example
            o = vectAt(e.objects, j);

            // basic processing
            addToInterval(&(sol->min), &(sol->max), o.size);
            if (!colorIsInVector(sol, o.color)) {
				vectPush(Color, sol->colors, o.color);
			}
			sol->shape = (LCA(rsolt, sol->shape, o.shape))->value;

        }
    }
    return sol;
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