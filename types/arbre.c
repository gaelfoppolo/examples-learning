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

Arbre* creeFeuille(char* n, int val) {
	Arbre* a;
 	a = (Arbre*)malloc(sizeof(Arbre));
 	a->nom = n;
 	a->valeur = val;
 	a->filsg = NULL;
 	a->filsd = NULL;
 	return a;
}

Arbre* creeNoeud(char* n, int val, Arbre* fg, Arbre* fd) {
 	Arbre* a;
 	a = (Arbre*)malloc(sizeof(Arbre));
	a->nom = n;
 	a->valeur = val;
 	a->filsg = fg;
 	a->filsd = fd;
 	return a;
}

int estFeuille(Arbre* a) {
 	return (a->filsg == NULL) && (a->filsd = NULL);
}

Arbre* PPAC(Arbre* racine, Arbre* a, Arbre* b) {
  if(!racine) {
  	return NULL;
  }
  // on vérifie si on a trouvé au moins une valeur
  if (racine == a || racine == b) {
  	return racine;
  }	
  // sinon on continue à descendre
  Arbre* gauche = PPAC(racine->filsg, a, b);
  Arbre* droite = PPAC(racine->filsd, a, b);
  // si gauche et droite contiennent tout deux a et b
  // racine actuelle est racine
  if (gauche && droite) { 
  	return racine;
  }
  // sinon on retourne le noeud qui contiennet une des deux valeurs
  // ou NULL si aucun ne le contient
  return gauche ? gauche : droite;
}

void freeArbre(Arbre* a) {
	if(a->filsg != NULL) freeArbre(a->filsg);
	if(a->filsd != NULL) freeArbre(a->filsd);
	free(a);
}