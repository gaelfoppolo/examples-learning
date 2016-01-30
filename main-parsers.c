#include "parser/parsers.h"

int main(int argc, char const *argv[]) {
	if(argc != 2) {
		printf("Un argument est attendu\n");
	}

	printf("Chargement du fichier d'exemples...\n");

	size_t includePosition;
	char* c = getIncludeFile(argv[1], &includePosition);

	if(c == NULL) {
		printf("Le chargement du fichier de config a échoué. Il ne doit pas être linké correctement\n");
	}
	else {
		printf("Chargement du fichier de config : %s\n", c);
		Model* m = loadConfigFile(c);
		printf("Fichier chargé !\n");

		printf("\e[1mChargement du fichier d'exemple. Début de lecture à %zu\e[0m\n", includePosition);

		Examples* e = loadExampleFile(argv[1], m, includePosition);

		free(c);
		freeModel(m);
		freeExamples(e);
	}


	return 0;
}
