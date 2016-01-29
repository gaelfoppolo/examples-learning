/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Convertion tools from structures to strings
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdio.h>
#include <stdarg.h>

#include "../types/model.h"
#include "../types/solution.h"
#include "../types/string-type.h"

// Bash colors
#define SDEFAULT	"\e[0m"
#define SBLACK		"\e[0;30m"
#define SRED		"\e[0;31m"
#define SGREEN		"\e[0;32m"
#define SYELLOW		"\e[0;33m"
#define SBLUE		"\e[0;34m"
#define SPURPLE		"\e[0;35m"
#define SCYAN		"\e[0;36m"
#define SWHITE		"\e[0;37m"
#define SBBLACK		"\e[1;30m"
#define SBRED		"\e[1;31m"
#define SBGREEN		"\e[1;32m"
#define SBYELLOW	"\e[1;33m"
#define SBBLUE		"\e[1;34m"
#define SBPURPLE	"\e[1;35m"
#define SBCYAN		"\e[1;36m"
#define SBWHITE		"\e[1;37m"
#define SUBLACK		"\e[4;30m"
#define SURED		"\e[4;31m"
#define SUGREEN		"\e[4;32m"
#define SUYELLOW	"\e[4;33m"
#define SUBLUE		"\e[4;34m"
#define SUPURPLE	"\e[4;35m"
#define SUCYAN		"\e[4;36m"
#define SUWHITE		"\e[4;37m"
#define SBUBLACK	"\e[1;4;30m"
#define SBURED		"\e[1;4;31m"
#define SBUGREEN	"\e[1;4;32m"
#define SBUYELLOW	"\e[1;4;33m"
#define SBUBLUE		"\e[1;4;34m"
#define SBUPURPLE	"\e[1;4;35m"
#define SBUCYAN		"\e[1;4;36m"
#define SBUWHITE	"\e[1;4;37m"

/**
*	@brief returns a string that contains the representation of the object in a readable presentation
*	@param sol Pointer to the object grouping the common traits of the other objects int the examples
*	@param mdl Pointer to the model object containing structure of the model
*	@return A string representing the object in a readable way. Need to be freed by the user
*/
char* genOutput(Solution* sol, Model* mdl);

/**
*	@brief Returns a string that contains the formatted output by concatening all the arguments
*	@param fmt The format string (same used by the printf family)
*	@param args The list of arguments to include in the output string
*
*	@return A newly allocated string that contains the arguments given to the function formated
*/
char* cPrint(const char * fmt, ...);

#endif // _OUTPUT_H_
