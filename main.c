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

	unsigned int argOffset = 1; // the place where the path to the exp file is expected in the argv array

	if(argc < 2) {
		output(LERROR, "You must pass the example file as argument like this : ./learning examples.exp\nThe example file must contains a link to the config file (include).\n");
		return 1;
	}

	if(argc == 3) { // expect a verbosity setting
		if(argv[1][0] == '-') { // verbosity setting
			argOffset = 2; // the path is after the param
			setOutputImportance(extractVerbosityFromArg(argv[1]));
		}
		else if(argv[2][0] == '-') { // verbosity setting after the exp argument
			setOutputImportance(extractVerbosityFromArg(argv[2]));
		}
	}

	size_t includePosition;
	char* c = getIncludeFile(argv[argOffset], &includePosition);

	if(c == NULL) {
		output(LERROR, "The loading of the configuration file failed. The configuration must be linked in the example file.\n");
	}
	else {
		output(L1, SBDEFAULT "Loading configuation file : %s" SDEFAULT "\n", c);
		Model* m = loadConfigFile(c);

		if(m == NULL) {
			output(LERROR, "Configuration file parsing : failed\n");
			free(c);
			return 1;
		}

		output(L1, SBDEFAULT "Loading examples file: %s" SDEFAULT "\n", argv[argOffset]);

		Examples* e = loadExampleFile(argv[argOffset], m, includePosition);

		if(e == NULL) {
			output(LERROR, "Example file parsing : failed\n");
			free(c);
			freeModel(m);
			return 1;
		}

		output(L1, SBDEFAULT "Generating solutions...\n");

		Solution* s = genAllCombi(m, e);
		genAllRelations(s, e, m);

		output(L1, SBDEFAULT "Solutions:\n\n");
		
		genOutput(s, m);

		free(c);
		freeModel(m);
		freeExamples(e);
		freeSolution(s);
	}


	return 0;
}
