/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 */

#include "solution.h"

void initSolution(Solution* sol) {
	vectInit(sol->outobjects);
}

void freeSolution(Solution* sol) {
	// free each OutObject
	for(unsigned int i = 0; i < vectSize(sol->outobjects); ++i) {
		freeOutObject(&vectAt(sol->outobjects, i), 0);
	}
	vectFree(sol->outobjects);
	free(sol);
}

