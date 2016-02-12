/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
 * @brief Main
 */

//#include <unistd.h>

#include <getopt.h>
 #include <unistd.h>

#include "parser/parsers.h"
#include "app/core.h"
#include "app/output.h"

#define PROG_NAME "learning"

 static int flagHelp = 0, flagNoCounterExample = 0, flagNoGeneralization = 0, flagExpandRelation = 0, flagVerbose = 0, flagNoColor = 0;

int main(int argc, char **argv) {
	int flag;
	const char* filename = NULL;

	// retrieve the options
	while(1) {
		static struct option long_options[] = {
			{"help", no_argument, &flagHelp, 1},
			{"no-counter-examples", no_argument, &flagNoCounterExample, 1},
			{"no-generalization", no_argument, &flagNoGeneralization, 1},
			{"expand-relations", no_argument, &flagExpandRelation, 1},
			{"no-color", no_argument, &flagNoColor, 1},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		flag = getopt_long (argc, argv, "vh", long_options, &option_index);

		/* Detect the end of the options. */
		if (flag == -1) {
			break;
		}

		switch(flag) {
			case 0:
				// all long option set flags, they will be checked after
				break;
			case 'v':
				// each occurence of a v add a verbosity level
				++flagVerbose;
				break;
			case 'h':
				flagHelp = 1;
				break;
			case '?':
				/* getopt_long already printed an error message. */
				break;
			default:
				abort ();
		}
	}

	if (optind < argc) {
		filename = argv[optind];
	}
	else if(!flagHelp) {
		output(LERROR, "An example file must be passed as an argument. Re run with --help for more informations.\n");
		return 1;
	}
	else {
		output(L0, PROG_NAME " is a programs that aims to find similarities in objects of same type.\n");
		output(L0, "Usage: " PROG_NAME " --help\n");
		output(L0, "       " PROG_NAME " <example-file-path>\n\n");
		output(L0, "--help                  Print the options that can be given to the program\n");
		output(L0, "--expand-relations      On solution objects that contains relations, print the object linked instead of writing its name\n");
		output(L0, "--no-generalization     Skip the generalization step of the solutions generation.\n");
		output(L0, "--no-counter-examples   Prevent the use of counter-exemples to reduce the solutions.\n");
		output(L0, "--no-color              Disable the colored output.\n");
		output(L0, "-v                      Set the verbosity level. 4 levels are available (up to -vvvv)\n");

		return 0;
	}

	setOutputImportance(flagVerbose);

	// if the user ask for no color or the output streams (wether stdout or stderr) aren't terminals, remove colors
	if(flagNoColor || !isatty(fileno(stdout)) || !isatty(fileno(stderr))) {
		enableColors(0);
	}

	size_t includePosition;
	char* c = getIncludeFile(filename, &includePosition);

	if(c == NULL) {
		output(LERROR, "The loading of the configuration file failed. The configuration must be linked in the example file (example file loaded : %s).\n", filename);
	}
	else {
		output(L1, "%sLoading configuation file : %s%s\n", SBDEFAULT, c, SDEFAULT);
		Model* m = loadConfigFile(c);

		if(m == NULL) {
			output(LERROR, "Configuration file parsing : failed\n");
			free(c);
			return 1;
		}

		output(L1, "%sLoading examples file: %s%s\n", SBDEFAULT, filename, SDEFAULT);

		Examples* e = loadExampleFile(filename, m, includePosition);

		if(e == NULL) {
			output(LERROR, "Example file parsing : failed\n");
			free(c);
			freeModel(m);
			return 1;
		}

		output(L1, "%sGenerating solutions...%s\n", SBDEFAULT, SDEFAULT);

		Solution* s = genAllCombi(m, e);
		genAllRelations(s, e, m);

		if(!flagNoGeneralization) {
			genGeneralisation(m, s);
		}

		if(!flagNoCounterExample) {
			genCounterExamples(m, e, s);
		}

		output(L1, "%sSolutions:%s\n\n", SBDEFAULT, SDEFAULT);
		
		genOutput(s, m);

		free(c);
		freeModel(m);
		freeExamples(e);
		freeSolution(s);
	}

	return 0;
}
