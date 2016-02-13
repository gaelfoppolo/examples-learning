/**
 *
 *	@author Bastien Philip (ebatsin)
 *  @author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "examples.h"

void initExamples(Examples* exps) {
    vectInit(exps->examples);
    vectInit(exps->counterExamples);
}

void freeExamples(Examples* exps) {
    if(!exps) return;

    //first free the all examples
    for(int i = 0; i < vectSize(exps->examples); ++i) {
		freeExample(&vectAt(exps->examples, i), 0);
    }
    //then free all counter-examples
    for(int i = 0; i < vectSize(exps->counterExamples); ++i) {
		freeExample(&vectAt(exps->counterExamples, i), 0);
    }

    vectFree(exps->examples);
    vectFree(exps->counterExamples);

    free(exps);
}
