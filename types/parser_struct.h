/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Structures used by the parser
 */

#ifndef _PARSER_STRUCT_H_
#define _PARSER_STRUCT_H_

#include "vector.h"
#include "colors.h"

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
    Vector(Object) objects;
} Example;

/**
*   @brief Structure that contains the examples and counter-examples of the current model
*   @field examples Array of examples
*   @field counterExamples Array of counter-examples
*/
typedef struct __basic_model_sample {
    Vector(Example) examples;
    Vector(Example) counterExamples;
} ModelSample;

void initModelSample(ModelSample * ms);
void freeModelSample(ModelSample * ms);

void initExample(Example * e);
void freeExample(Example * e);

#endif // _PARSER_STRUCT_H_
