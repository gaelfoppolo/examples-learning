/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "../types/model.h"
#include "../types/tree.h"

OutObject* learning(ModelSample* current, Tree* root);

void addToInterval(int *min, int*max, int x);

int isInVector(OutObject* v, Color c);