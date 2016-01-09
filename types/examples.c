/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions used by the examples
 */

#include "examples.h"

void initExamples(Examples * es) {
    vectInit(es->examples);
    vectInit(es->counterExamples);
}

void freeExamples(Examples * es) {
    //first free the examples
    for(int i = 0; i < vectSize(es->examples); ++i) {
        vectFree((vectAt(es->examples, i)).objects);
    }
    //then free the counter-examples
    for(int i = 0; i < vectSize(es->counterExamples); ++i) {
        vectFree((vectAt(es->counterExamples, i)).objects);
    }

    vectFree(es->examples);
    vectFree(es->counterExamples);

    free(es);
}