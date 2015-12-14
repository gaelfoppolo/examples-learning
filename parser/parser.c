/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief Functions and structures used by the parser
 */

#include <stdio.h>
#include "parser.h"
#include <stdlib.h>

ModelSample* parse(char* file) {
	// file descriptor
 	FILE* fd;
 	char* line = NULL;
    size_t len = 0;
    ssize_t read;

 	fd = fopen(file,"r");

 	//over the file
 	while ((read = getline(&line, &len, fd)) != -1) {
        //if it is an exemple == begin by "E"
    	if (strlen(line) < strlen("E") ? 0 : strncmp("E", line, strlen("E")) == 0) {
    		// iterate over the object

    	} else { // it's a counter-examples
    		// iterate over the object
    	}
    }

 	fclose(fd);
 	free(line);

 	return NULL;
 }