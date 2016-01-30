/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Main
 */

#include "parser/parsers.h"
#include "app/core.h"
#include "app/output.h"

int main(int argc, char const *argv[]) {

	if(argc < 2) {
		printf("You must pass the example file as argument like this : ./learning examples.exp\nThe example file must contains a link to the config file (include).\n");
		return 1;
	}

	printf("\e[1mLoading file...\e[0m\n");

	size_t includePosition;
	char* c = getIncludeFile(argv[1], &includePosition);

	if(c == NULL) {
		printf("The loading of the configuration file failed. The configuration must be linked in the example file.\n");
	}
	else {
		printf("\e[1mLoading configuation file: %s\e[0m\n", c);
		Model* m = loadConfigFile(c);

		if(m == NULL) {
			printf("Configuration file parsing : failed\n");
			free(c);
			return 1;
		}

		printf("\e[1mLoading example file: %s\e[0m\n", argv[1]);

		Examples* e = loadExampleFile(argv[1], m, includePosition);

		if(e == NULL) {
			printf("Example file parsing : failed\n");
			free(c);
			freeModel(m);
			return 1;
		}

		printf("\e[1mMaking magic...\e[0m\n");

		// Solution* s = genSolution(m, e); // only one solution in step 1

		// char* out = genOutput(s, m); // we need to pass the model for the int -> string conversion table it holds

		// printf("%s", out);

		free(c);
		freeModel(m);
		freeExamples(e);
		// freeSolution(e);
		// free(out);
	}


	return 0;
}
