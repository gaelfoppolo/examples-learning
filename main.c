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

	Tree* a = createNode("Whatever", whatever, 
		createNode("Polygone", polygone, 
			createNode("Triangle", triangle, 
				createLeaf("Rectangle triangle", rectangle_triangle), 
				createNode("Isosceles triangle", isosceles_triangle, 
					createLeaf("Equilateral triangle", equilateral_triangle), 
					NULL)
			), 
			createNode("Quadrilateral", quadrilateral, 
				createLeaf("Trapeze", trapeze), 
				createNode("Rectangle", rectangle, 
					createLeaf("Square", square), 
					NULL
				)
			)
		), 
		createNode("Ellipsoid", ellipsoid, 
			createLeaf("Circle", circle), 
			createLeaf("Ellipse", ellipse)
		));

	Tree* n = LCA(a, createLeaf("Rectangle triangle", rectangle_triangle), createLeaf("Square", circle));
	printf("%s\n", n->name);

	freeTree(a);

	return 0;
}