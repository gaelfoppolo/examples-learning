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
	if(argc != 2) {
		printf("You must give a file as first argument ex: %s myFile.cfg\n", argv[0]);
		return 1;
	}

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

	ModelSample * current = parse(argv[1]);

	if(current == NULL) {
		printf("The file does not exist or you don't have the correct rights to open it.\n");

    	freeTree(root);
    	
		return 1;
	}

    OutObject* oo = learning(current, root);

    printf("%s\n", stringifyCommonObject(oo));

    freeTree(root);

    freeModelSample(current);

    freeOutObject(oo);

	return 0;
}

 