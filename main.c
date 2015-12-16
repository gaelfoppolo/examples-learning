/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Main
 */
 
#include <stdio.h>
#include "types/tree.h"
#include "parser/parser.h"
#include "app/output.h"
#include "app/core.h"

int main(int argc, char const *argv[])
{

	Tree* root = createNode(whatever, 
		createNode(polygone, 
			createNode(triangle, 
				createLeaf(rectangle_triangle), 
				createNode(isosceles_triangle, 
					createLeaf(equilateral_triangle), 
					NULL)
			), 
			createNode(quadrilateral, 
				createLeaf(trapeze), 
				createNode(rectangle, 
					createLeaf(square), 
					NULL
				)
			)
		), 
		createNode(ellipsoid, 
			createLeaf(circle), 
			createLeaf(ellipse)
		));

	Tree* n = LCA(root, rectangle_triangle, square);
	printf("LCA of %s and %s is %s\n", ShapeString[rectangle_triangle], ShapeString[square], ShapeString[n->value]);

	ModelSample * current = parse("ressources/examples.cfg");


    // Example test;
    // Object o;

    // printf("Contre-exemples : %d\n", vectSize(current->counterExamples));
    // printf("exemples : %d\n", vectSize(current->examples));

    // printf("Parcourt des contre-exemples : \n");
    // for(int i = 0; i < vectSize(current->examples); ++i) {
    //     test = vectAt(current->examples, i);
    //     printf("Exemple %d:\n", i+1);
    //     for(int j = 0; j < vectSize(test.objects); ++j) {
    //         o = vectAt(test.objects, j);
    //         printf("\tObjet %d:\n", j+1);
    //         printf("\t\tTaille : %d\n", o.size);
    //         printf("\t\tCouleur : %d\n", o.color);
    //         printf("\t\tForme : %d\n", o.shape);
    //     }
    // }


    // printf("Taille de l'exemple : %d\n", vectSize(test.objects));

    OutObject* oo = learning(current, root);

    printf("%s\n", stringifyCommonObject(oo));

    freeTree(root);

    freeModelSample(current);

    freeOutObject(oo);

	return 0;
}

 