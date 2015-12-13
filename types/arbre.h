/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Entête module des arbres binaires
 */

#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * @brief Structure de l'arbre binaire
 * 
 * @field nom Nom de la forme géométrique
 * @field valeur Valeur entière strictement supérieur à 0
 * @field *filsg Pointeur vers le fils gauche
 * @field *filsd Pointeur vers le fils gauche
 *
 */
typedef struct self_arbre {
	char* nom;
 	int valeur;
 	struct self_arbre *filsg;
 	struct self_arbre *filsd;
} Arbre;

/**
 * @brief Création d'une nouvelle feuille (arbre)
 * 
 * @param n nom de la figure géométrique
 * @param val la valeur correspondante à la figure
 * 
 * @return le nouvel arbre
 */
Arbre* creeFeuille(char* n, int val);

/**
 * @brief Création d'un nouveau noeud (arbre)
 *
 * @param n nom de la figure géomatrique
 * @param val la valeur correspondante à la figure
 * @param[in] fg fils gauche
 * @param[in] fd fils droit
 *
 * @return le nouvel arbre
 */
Arbre* creeNoeud(char* n, int val, Arbre* fg, Arbre* fd);

/**
 * @brief Savoir si l'arbre est une feuille
 *
 * @param a l'arbre à évaluer
 *
 * @return 0 (faux) ou 1 (vrai)
 */
int estFeuille(Arbre* a);

/**
 * @brief Trouve le plus petit ancêtre commun entre deux noeuds/feuilles
 * @description Complexité θ(n). On ne parcours l'arbre qu'une seule fois.
 * On part de la racine en descendant, jusqu'à trouver un noeud qui correspond
 * ou être sur une feuille et on fait remonter cette valeur au parent.
 * Celui-ci teste ensuite si le fils gauche et le fils droit contient la valeur.
 * Si c'est le cas, le parent est le PPAC, sinon on remonte celui qui contient le noeud
 * ou NULL si aucun ni fils gauche ni fils droit ne la contiennent.
 *
 * @param racine La racine de l'arbre
 * @param a le premier noeud
 * @param b le second noeud
 *
 * @return le plus petit ancêtre commun
 */
Arbre* PPAC(Arbre* racine, Arbre* a, Arbre* b);

/**
 * @brief Supprime de la mémoire l'espace occupé par l'arbre
 *
 * @param a le pointeur de l'arbre a supprimé de la mémoire
 */
void freeArbre(Arbre* a);

#endif
