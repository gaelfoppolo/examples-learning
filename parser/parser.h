/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions and structures used by the parser
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "../types/model.h"

#define _KEY_VALUE_MAX_SIZE_ 100

typedef struct __basic_string_pair {
    char* first;
    char* second;
} StringPair;

/**
*   @brief Returns the next pair of key->value in the file
*   @param fp The file pointer of the file to read
*   @param sp The Stringpair in which to store the key and value. The member must be allocated by the user
*   @return Returns 1 in case of success. 0 otherwise
*/
int getNextAttribute(FILE* fp, StringPair * sp);

/**
*   @brief Generate a structure that contains all the examples and counter-examples parsed in a file
*   @param file The path to the file to parse
*   @return A structure that represents the content of the file
*/
ModelSample* parse(char const* file);

#endif // _PARSER_H_
