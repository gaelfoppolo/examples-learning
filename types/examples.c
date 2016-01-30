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
	printf("Free\n");
    //first free the examples
    for(int i = 0; i < vectSize(es->examples); ++i) {
		for(int j = 0; j < vectSize((vectAt(es->examples, i)).objects); ++j) {
			vectFree(vectAt((vectAt(es->examples, i)).objects, j).attributes);
		}
        vectFree((vectAt(es->examples, i)).objects);
    }
    //then free the counter-examples
    for(int i = 0; i < vectSize(es->counterExamples); ++i) {
		for(int j = 0; j < vectSize((vectAt(es->counterExamples, i)).objects); ++j) {
			vectFree(vectAt((vectAt(es->counterExamples, i)).objects, j).attributes);
		}
        vectFree((vectAt(es->counterExamples, i)).objects);
    }

    vectFree(es->examples);
    vectFree(es->counterExamples);

    free(es);
}
