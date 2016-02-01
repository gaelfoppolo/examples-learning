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

	printf(SBWHITE "Loading file..." SDEFAULT "\n");

	size_t includePosition;
	char* c = getIncludeFile(argv[1], &includePosition);

	if(c == NULL) {
		printf("The loading of the configuration file failed. The configuration must be linked in the example file.\n");
	}
	else {
		printf(SBWHITE "Loading configuation file: %s" SDEFAULT "\n", c);
		Model* m = loadConfigFile(c);

		if(m == NULL) {
			printf("Configuration file parsing : failed\n");
			free(c);
			return 1;
		}

		printf(SBWHITE "Loading example file: %s" SDEFAULT "\n", argv[1]);

		Examples* e = loadExampleFile(argv[1], m, includePosition);

		if(e == NULL) {
			printf("Example file parsing : failed\n");
			free(c);
			freeModel(m);
			return 1;
		}

		int nb = nbCombi(e);

		printf("NB combi : %d\n", nb);

		Solution* s;
		initSolution(s);
		s = genEmptySol(s, nb);

		printf("size of sol now init = %d\n", vectSize(s->outobjects));

		// printf(SBWHITE "Generating solution..." SDEFAULT "\n");

		//Solution* s = genSolution(m, e); // only one solution in step 1

		//char* out = genOutput(s, m); // we need to pass the model for the int -> string conversion table it holds

		//printf("%s", out);

		free(c);
		freeModel(m);
		freeExamples(e);
		//freeSolution(s);
		//free(out);
	}


	return 0;
}
