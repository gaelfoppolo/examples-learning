/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions and structures used by the parser
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include "../types/colors.h"

typedef int Color;
typedef int Shape;

/**
*   @brief All the attributes of the object
*   @field size The object's size
*   @field color The object's color
*   @field shape The object's shape
*/
typedef struct __basic_object {
    int size;
    Color color;
    Shape shape;
} Object;


/**
*   @brief All the objects composing an example (or a counter-example)
*   @field objects An array of the objects composing the example
*/
typedef struct __basic_example {
    Object* objects;
} Example;

/**
*   @brief Structure that contains the examples and counter-examples of the current model
*   @field examples Array of examples
*   @field counterExamples Array of counter-examples
*/
typedef struct __basic_model_sample {
    Example* examples;
    Example* counterExamples;
} ModelSample;

/**
*   @brief Generate a structure that contains all the examples and counter-examples parsed in a file
*   @param file The path to the file to parse
*   @return A structure that represents the content of the file
*/
ModelSample* parse(char* file);

/**
*   @brief Free the memory allocated while parsing
*   @param ms The ModelSample created by the parse function
*/
void freeModelSample(ModelSample* ms);

#endif // _PARSER_H_
