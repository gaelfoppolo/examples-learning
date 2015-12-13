#ifndef _PARSER_H_
#define _PARSER_H_

#include "../config/colors.h"

typedef int Color;
typedef int Forme;

/**
*   @brief Structure des objets
*   @field id Identifiant de l'objet
*   @field taille taille de l'objet
*   @field couleur couleur de l'objet
*   @field forme forme de l'objet
*/
typedef struct __basic_object {
    int id;
    int taille;
    Color couleur;
    Forme forme;
} Object;


/**
*   @brief Structure des exemples et contre exemples
*   @field objectList Tableau contenant tous les objets composant l'exemple
*/
typedef struct __basic_example {
    Object* objects;
} Example;

/**
*   @brief Structure contenant les exemples et contre-exemples associé au modèle à tester
*   @field examples tableau d'exemples
*   @field counterExamples tableau de contre exemples
*/
typedef struct __basic_model_sample {
    Example* examples;
    Example* counterExamples;
} ModelSample;

/**
*   @brief génère la structure contenant les exemples et contre exemples à partir d'un fichier
*   @param file le chemin vers le fichier à charger
*   @return une structure générée à partir du fichier
*/
ModelSample* parse(char* file);

/**
*   @brief Libère la mémoire allouée lors de la génération de la structure principale
*   @param ms Le modèle sample généré par la fonction parse
*/
void freeModelSample(ModelSample* ms);

#endif // _PARSER_H_
