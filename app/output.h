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

#include "../types/model.h"
#include "../types/solution.h"
#include "../types/string-type.h"

/**
*	@brief returns a string that contains the representation of the object in a readable presentation
*	@param sol Pointer to the object grouping the common traits of the other objects int the examples
*	@param mdl Pointer to the model object containing structure of the model
*	@return A string representing the object in a readable way. Need to be freed by the user
*/
String genOutput(Solution* sol, Model* mdl);

#endif // _OUTPUT_H_
