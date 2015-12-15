#include <stdio.h>
#include "parser/parser.h"

int main(int argc, char const *argv[])
{
    ModelSample * current = parse("ressources/examples.cfg");


    Example test;
    Object o;

    printf("Contre-exemples : %d\n", vectSize(current->counterExamples));
    printf("exemples : %d\n", vectSize(current->examples));

    printf("Parcourt des contre-exemples : \n");
    for(int i = 0; i < vectSize(current->examples); ++i) {
        test = vectAt(current->examples, i);
        printf("Exemple %d:\n", i+1);
        for(int j = 0; j < vectSize(test.objects); ++j) {
            o = vectAt(test.objects, j);
            printf("\tObjet %d:\n", j+1);
            printf("\t\tTaille : %d\n", o.size);
            printf("\t\tCouleur : %d\n", o.color);
            printf("\t\tForme : %d\n", o.shape);
        }
    }


    printf("Taille de l'exemple : %d\n", vectSize(test.objects));

    return 0;
}
