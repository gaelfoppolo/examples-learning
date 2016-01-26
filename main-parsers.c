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

		printf("Chargement du fichier d'exemple. Début de lecture à %zu\n", includePosition);

		Examples* e = loadExampleFile(argv[1], m, includePosition);

		free(c);
		freeModel(m);
	}


	return 0;
}
