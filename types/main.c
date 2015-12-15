
#include "tree.c"

int main(int argc, char const *argv[])
{
	Tree* a = createLeaf("Rectangle triangle", 7);
	Tree* b = createLeaf("Equilateral triangle", 11);
	Tree* c = createLeaf("Trapeze", 9);
	Tree* d = createLeaf("Square", 12);
	Tree* e = createLeaf("Circle", 5);
	Tree* f = createLeaf("Ellipse", 6);
	Tree* g = createNode("Isosceles triangle", 8, b, NULL);
	Tree* h = createNode("Rectangle", 10, d, NULL);
	Tree* i = createNode("Ellipsoid", 2, e, f);
	Tree* j = createNode("Triangle", 3, a, g);
	Tree* k = createNode("Quadrilateral", 4, c, h);
	Tree* l = createNode("Polygone", 1, j, k);
	Tree* m = createNode("Whatever", 0, l, i);

	Tree* n = LCA(m, b, h);
	printf("%s\n", n->name);

	freeTree(m);

	return 0;
}