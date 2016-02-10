/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Main
 */

#include "parser/parsers.h"
#include "app/core.h"
#include "app/output.h"

 #define PROG_NAME "learning"

int main(int argc, char const *argv[]) {

	unsigned int argOffset = 1; // the place where the path to the exp file is expected in the argv array

	if(argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		output(L0, PROG_NAME " is a programs that aims to find similarities in objects of same type.\n");
		output(L0, "Usage: " PROG_NAME " --help\n");
		output(L0, "       " PROG_NAME " <example-file-path> [--extend-relations]\n\n");
		output(L0, "--extend-relations	On solution objects that contains relations, print the object linked instead of writing its name\n");
		output(L0, "-v                	Set the verbosity level. 4 levels are available (up to -vvvv)\n");

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
		output(LERROR, "The loading of the configuration file failed. The configuration must be linked in the example file (example file loaded : %s).\n", argv[argOffset]);
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

		genGeneralisation(m, s);

		output(L1, SBDEFAULT "Solutions:\n\n");
		
		genOutput(s, m);

		// printf("Height of the tree: %d\n", height(&vectAt(m->ma, 2).mt.tree));

		// int id = 9;

		// printf("Depth of %s: %d\n", getTreeStr(id, m, 2), depth(&vectAt(m->ma, 2).mt.tree, id));

		// int maxSpe = 1; 
		
		// for (int i = 0; i < vectSize(s->outobjects); ++i) {
		// 	printf("Specificity oo n°%d = %d\n", i, vectAt(s->outobjects, i).specificity);
		// 	maxSpe = max(maxSpe, vectAt(s->outobjects, i).specificity);
		// }

		// printf("Best specificity = %d\n", maxSpe);

		free(c);
		freeModel(m);
		freeExamples(e);
		freeSolution(s);
	}


	return 0;
}
