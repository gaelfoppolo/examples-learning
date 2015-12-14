/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Main
 */

#include "types/tree.c"
#include "types/shape.h"

int main(int argc, char const *argv[])
{

	Tree* a = createNode(whatever, 
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

	Tree* n = LCA(a, createLeaf(rectangle_triangle), createLeaf(square));
	printf("LCA of %s and %s is %s\n", ShapeString[rectangle_triangle], ShapeString[square], ShapeString[n->value]);

	freeTree(a);

	return 0;
}