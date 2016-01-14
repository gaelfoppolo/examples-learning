#include "parser/parsers.h"

int main(int argc, char const *argv[]) {
	if(argc != 2) {
		printf("Un argument est attendu\n");
	}

	printf("Chargement du fichier d'exemples...\n");

	char* c = getIncludeFile(argv[1]);

	if(c == NULL) {
		printf("Le chargement du fichier de config a échoué. Il ne doit pas être linké correctement\n");
	}
	else {
		printf("Chargement du fichier de config : %s\n", c);
		Model* m = loadConfigFile(c);
		printf("Fichier chargé !\n");

		free(c);
		freeModel(m);
	}


	return 0;
}
