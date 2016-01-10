/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Convertion tools from structures to strings
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdlib.h>
#include <stdio.h>

#include "../types/out-object.h"
#include "utils.h"

/**
*	@brief returns a string that contains the representation of the object in a readable presentation
*	@param out The object grouping the common traits of the other objects int the examples
*	@return A string representing the object in a readable way. Need to be freed by the user
*/
char* stringifyCommonObject(OutObject* out);

#endif // _OUTPUT_H_
