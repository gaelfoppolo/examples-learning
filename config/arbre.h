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
typedef struct self {
	char *nom;
 	int valeur;
 	struct self *filsg;
 	struct self *filsd;
} arbre, *pArbre;

/**
 * @brief Création d'une nouvelle feuille (arbre)
 * 
 * @param n nom de la figure géométrique
 * 
 * @return le nouvel arbre
 */
pArbre creeFeuille(char* n);

/**
 * @brief Création d'un nouveau noeud (arbre)
 *
 * @param n nom de la figure géomatrique
 * @param[in] fg fils gauche
 * @param[in] fd fils droit
 *
 * @return le nouvel arbre
 */
pArbre creeNoeud(char* n, pArbre fg, pArbre fd);

/**
 * @brief Savoir si l'arbre est une feuille
 *
 * @param a l'arbre à évaluer
 *
 * @return 0 (faux) ou 1 (vrai)
 */
int estFeuille(pArbre a);

#endif
