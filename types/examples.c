/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions used by the examples
 */

#include "examples.h"

void initExamples(Examples* exps) {
    vectInit(exps->examples);
    vectInit(exps->counterExamples);
}

void freeExamples(Examples* exps) {
    if(!exps) return;

    //first free the examples
    for(int i = 0; i < vectSize(exps->examples); ++i) {
		freeExample(&vectAt(exps->examples, i), 0);
    }
    //then free the counter-examples
    for(int i = 0; i < vectSize(exps->counterExamples); ++i) {
		freeExample(&vectAt(exps->counterExamples, i), 0);
    }

    vectFree(exps->examples);
    vectFree(exps->counterExamples);

    free(exps);
}
