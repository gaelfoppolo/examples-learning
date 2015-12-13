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
*   @brief Structure contenant les exemples et contre-exemples associ� au mod�le � tester
*   @field examples tableau d'exemples
*   @field counterExamples tableau de contre exemples
*/
typedef struct __basic_model_sample {
    Example* examples;
    Example* counterExamples;
} ModelSample;

/**
*   @brief g�n�re la structure contenant les exemples et contre exemples � partir d'un fichier
*   @param file le chemin vers le fichier � charger
*   @return une structure g�n�r�e � partir du fichier
*/
ModelSample* parse(char* file);

/**
*   @brief Lib�re la m�moire allou�e lors de la g�n�ration de la structure principale
*   @param ms Le mod�le sample g�n�r� par la fonction parse
*/
void freeModelSample(ModelSample* ms);

#endif // _PARSER_H_
