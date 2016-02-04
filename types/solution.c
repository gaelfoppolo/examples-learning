/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structure of our solution - Implementation
 */

#include "solution.h"

void initSolution(Solution* sol) {
	vectInit(sol->outobjects);
}

void freeSolution(Solution* sol) {
	for(unsigned int i = 0; i < vectSize(sol->outobjects); ++i) {
		freeOutObject(&vectAt(sol->outobjects, i));
	}
	vectFree(sol->outobjects);
	free(sol);
}

