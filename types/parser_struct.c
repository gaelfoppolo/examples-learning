#include "parser_struct.h"

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

void initExample(Example * e) {
    vectInit(e->objects);
}

void freeExample(Example * e) {
    vectFree(e->objects);
}
