/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Main
 */

#include <stdio.h>
#include "app/core.h"

int main(int argc, char const *argv[]) {
	if(argc < 2) {
		printf("You must pass the example file as argument like this : prgm examples.exp\nIf the example file does not contain a link to the config file (include), you must add the config file as second argument.\n");
		return 1;
	}

	char* configName = getConfigName(argv[1]);

	if(configName == NULL) { // no include, we check the second argument
		if(argc == 3) {
			configName = argv[2];
		}
		else {
			printf("The example file does not contains a link to the config file. You must add it or pass the config file as second argument.");
			return 1;
		}
	}

	Model* model = loadModel(configName); // load the config file and gen all the model types

	if(model == NULL) {
		printf("The config file does not exist or contains errors.\n");
		free(configName);
		return 1;
	}

	Examples* examples = loadExamples(argv[1], model);

	if(examples == NULL) {
		printf("The examples file contains errors. Please check and rerun the program.\n");
		free(configName);
		freeModel(model);
		return 1;
	}

	Solution* sol = genSolution(model, examples); // only one solution in step 1
	
	char* out = genOutput(sol, model); // we need to pass the model for the int -> string conversion table it holds

	printf("%s", out);

	free(out);
	free(configName);
	freeModel(model);
	freeExamples(examples);
	freeSolutions(sol);

	return 0;
}
