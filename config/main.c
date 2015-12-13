
#include "arbre.c"

int main(int argc, char const *argv[])
{
	Arbre* a = creeFeuille("Triangle rectangle", 7);
	Arbre* b = creeFeuille("Triangle équilatéral", 11);
	Arbre* c = creeFeuille("Trapèze", 9);
	Arbre* d = creeFeuille("Carré", 12);
	Arbre* e = creeFeuille("Cercle", 5);
	Arbre* f = creeFeuille("Ellipse", 6);
	Arbre* g = creeNoeud("Triangle isocèle", 8, b, NULL);
	Arbre* h = creeNoeud("Rectangle", 10, d, NULL);
	Arbre* i = creeNoeud("Ellipsoïde", 2, e, f);
	Arbre* j = creeNoeud("Triangle", 3, a, g);
	Arbre* k = creeNoeud("Quadrilatère", 4, c, h);
	Arbre* l = creeNoeud("Polygone", 1, j, k);
	Arbre* m = creeNoeud("Quelconque", 0, l, i);

	Arbre* n = PPAC(m, b, h);
	printf("%s\n", n->nom);

	freeArbre(m);

	return 0;
}