/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions used by the model
 */

#include "model.h"

void initModelSample(ModelSample * ms) {
    vectInit(ms->examples);
    vectInit(ms->counterExamples);
}

void freeModelSample(ModelSample * ms) {
    //first free the examples
    for(int i = 0; i < vectSize(ms->examples); ++i) {
        vectFree((vectAt(ms->examples, i)).objects);
    }
    for(int i = 0; i < vectSize(ms->counterExamples); ++i) {
        vectFree((vectAt(ms->counterExamples, i)).objects);
    }

    vectFree(ms->examples);
    vectFree(ms->counterExamples);
}