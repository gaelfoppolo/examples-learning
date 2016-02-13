/**
 *	@file output.h
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 *	@brief File containing the output functions and helpers
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdio.h>
#include <stdarg.h>

#include "../types/model.h"
#include "../types/solution.h"
#include "../types/string-type.h"

/**
*	@name TTY colors
*	@brief Color values in Unix and MacOS terminals
*/
//@{
char* SDEFAULT;
char* SBDEFAULT;
char* SBLACK;
char* SRED;
char* SGREEN;
char* SYELLOW;
char* SBLUE;
char* SPURPLE;
char* SCYAN;
char* SWHITE;
char* SBBLACK;
char* SBRED;
char* SBGREEN;
char* SBYELLOW;
char* SBBLUE;
char* SBPURPLE;
char* SBCYAN;
char* SBWHITE;
char* SUBLACK;
char* SURED;
char* SUGREEN;
char* SUYELLOW;
char* SUBLUE;
char* SUPURPLE;
char* SUCYAN;
char* SUWHITE;
char* SBUBLACK;
char* SBURED;
char* SBUGREEN;
char* SBUYELLOW;
char* SBUBLUE;
char* SBUPURPLE;
char* SBUCYAN;
char* SBUWHITE;
//@}

/** @brief Flag for the output function. Represents an error */
#define LERROR		8
/**
*	@name output importance
*	@brief Flags for the output function. Represents levels of importance
*/
//@{
#define L0			0
#define L1			1
#define L2			2
#define L3			3
#define L4			4
#define L5			5
#define L6			6
#define L7			7
//@}

/**
*	@brief Returns a string that contains the representation of the object in a readable presentation
*	@param sol Pointer to the object grouping the common traits of the other objects int the examples
*	@param mdl Pointer to the model object containing structure of the model
*	@param recur Boolean to presize wheter relations must be printed recursively or just their name (0 : no recursion, 1: recursion)
*/
void genOutput(Solution* sol, Model* mdl, int recur);

/**
*	@brief Print an object
*	@param oo The object to print
*	@param m The model
*	@param recur -1 if no recursion is allowed (juste print name of object linked by relation), or the number of indentations
*/
void genObjectOutput(OutObject* oo, Model* m, int recur);

/**
*	@brief Returns a string that contains the formatted output by concatening all the arguments
*	@param fmt The format string (same used by the printf family)
*	@param ... The list of arguments to include in the output string
*
*	@return A newly allocated string that contains the arguments given to the function formated
*/
char* cPrint(const char* fmt, ...);

/**
*	@brief Sets the max level of the messages to output (0 : only critical messages, the higher the value, the less importance the messages)
*	@param level The level to set
*/
void setOutputImportance(unsigned int level);

/**
*	@brief Gets the max level of the messages to output (0 : only critical messages, the higher the value, the less importance the messages)
*/
unsigned int getOutputImportance();

/**
*	@brief Print the message in the standard output only if its importance is high enough to be printed
*	@param level The importance level of the message (flags, can use L[0-7] and add the flag LERROR if you want to write in the error stream
*			LERROR alone is aquivalent to L0 | LERROR
*	@param fmt The message to be printed
*	@param ... The arguments needed by the fmt argument
*/
void output(unsigned int level, const char* fmt, ...);

/**
*	@brief Extract the verbosity value from the "-v[v..]" formated string.
*	@param verbosity The string to extract the verbosity from
*
*	@return The level extracted
*/
unsigned int extractVerbosityFromArg(const char* verbosity);

/**
*	@brief Enables or not the colors in the output
*	@param enable Boolean. If @a enable = 0, the colors are disabled, colors are activated for any other values
*/
void enableColors(unsigned int enable);

/*
*	@brief Print a fixed number of time a character
*	@param level The importance level of the message (flags, can use L[0-7] and add the flag LERROR if you want to write in the error stream
*			LERROR alone is aquivalent to L0 | LERROR
*	@param c The character to print
*	@param n The number of time to print the character
*/
void printNChar(unsigned int level, char c, unsigned int n);

#endif // _OUTPUT_H_
