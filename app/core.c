#include "core.h"

OutObject* learning(ModelSample* ms, Tree* root) {
 	// an example
 	Example e;
 	// an object of an example
 	Object o;
 	// an output object, gathering traits from all examples
 	OutObject* oo = (OutObject*)malloc(sizeof(OutObject));
    initOutObject(oo);

    // first object of the first example is our basic output model
    o = vectAt(vectAt(ms->examples, 0).objects, 0);
    oo->min = o.size;
    oo->max = o.size;
    vectPush(Color, oo->colors, o.color);
    oo->shape = o.shape;

 	for(int i = 0; i < vectSize(ms->examples); ++i) {
        // current example
        e = vectAt(ms->examples, i);
        // for all objects of the example

        for(int j = 0; j < vectSize(e.objects); ++j) {
        	// current object of the example
            o = vectAt(e.objects, j);

            // basic processing
            addToInterval(&(oo->min), &(oo->max), o.size);
            if (!colorIsInVector(oo, o.color)) {
				vectPush(Color, oo->colors, o.color);
			}
			oo->shape = (LCA(root, oo->shape, o.shape))->value;

        }
    }
    return oo;
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