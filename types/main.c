
#include "tree.c"

int main(int argc, char const *argv[])
{
	Tree* a = createLeaf("Triangle rectangle", 7);
	Tree* b = createLeaf("Triangle équilatéral", 11);
	Tree* c = createLeaf("Trapèze", 9);
	Tree* d = createLeaf("Carré", 12);
	Tree* e = createLeaf("Cercle", 5);
	Tree* f = createLeaf("Ellipse", 6);
	Tree* g = createNode("Triangle isocèle", 8, b, NULL);
	Tree* h = createNode("Rectangle", 10, d, NULL);
	Tree* i = createNode("Ellipsoïde", 2, e, f);
	Tree* j = createNode("Triangle", 3, a, g);
	Tree* k = createNode("Quadrilatère", 4, c, h);
	Tree* l = createNode("Polygone", 1, j, k);
	Tree* m = createNode("Quelconque", 0, l, i);

	Tree* n = LCA(m, b, h);
	printf("%s\n", n->name);

	freeTree(m);

	return 0;
}