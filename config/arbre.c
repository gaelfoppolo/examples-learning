/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Fonctions des arbres binaires
 */

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

Arbre* creeFeuille(char* n) {
	Arbre* a;
 	a = (Arbre*)malloc(sizeof(Arbre));
 	a->nom = n;
 	a->valeur = compteur++;
 	a->filsg = NULL;
 	a->filsd = NULL;
 	return a;
}

Arbre* creeNoeud(char* n, Arbre* fg, Arbre* fd) {
 	Arbre* a;
 	a = (Arbre*)malloc(sizeof(Arbre));
	a->nom = n;
 	a->valeur = compteur++;
 	a->filsg = fg;
 	a->filsd = fd;
 	return a;
}

int estFeuille(Arbre* a) {
 	return (a->filsg == NULL) && (a->filsd = NULL);
}