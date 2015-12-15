#include "parser.h"

int getNextAttribute(FILE* fp, StringPair * sp) {
    char c;
    int keyp = 0, valuep = 0;
    // while not a valid key character, reads
    while((c = fgetc(fp)) != EOF && c != '\n' && (c == ' ' || c == '\t' || c == ','));
    if(c == EOF || c == '\n') return 0;

    // while not '(', reads
    sp->first[keyp++] = c;
    while((c = fgetc(fp)) != EOF && c != '(' && c != '\n') {
        sp->first[keyp++] = c; // stores the key
    }
    if(c != '(') return 0;
    sp->first[keyp] = '\0';

    // reads the value
    while((c = fgetc(fp)) != EOF && c != ')' && c != '\n') {
        sp->second[valuep++] = c; // stores the value
    }
    if(c != ')') return 0;
    sp->second[valuep] = '\0';

    return 1;
}

ModelSample* parse(char* file) {
    FILE * f;
    char c;

    f = fopen(file, "r");

    if(!f) {
        // todo : errors handling
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    // control variables
    int isCounterExample = 0;
    int isIndented = 0;
    StringPair sp;
    sp.first = (char*)malloc(_KEY_VALUE_MAX_SIZE_ * sizeof(char));
    sp.second = (char*)malloc(_KEY_VALUE_MAX_SIZE_ * sizeof(char));

    ModelSample * ms = (ModelSample*)malloc(sizeof(ModelSample));
    initModelSample(ms);

    Example currentExample;
    Object currentObject;

    c = fgetc(f);
    // loop through the file
    while(c != EOF) {
        // read til not space, \t or \n
        while((c == ' ' || c == '\n' || c == '\t') && (c = fgetc(f)) != EOF);

        isCounterExample = c == '!'; // must be on the first char of the example or counter-example (!)

        // reads til the end of line
        while((c = fgetc(f)) != EOF && c != '\n');

        initExample(&currentExample); // alloc the example

        // from now, we add objects each time a line starts with an indentation (ie: (\n)+ or ' '+)
        isIndented = 1;
        while(isIndented) {
            isIndented = 0;
            while((c = fgetc(f)) != EOF && (c == ' ' || c == '\t')) isIndented = 1;

            if(!isIndented) break; // not a new object, must be eof or a new example

            // we go forward til ':'
            while((c = fgetc(f)) != EOF && c != ':');

            while(getNextAttribute(f, &sp)) {
                if(strcmp("shape", sp.first) == 0) { // key = "shape
                    currentObject.shape = getShapeId(sp.second);
                }
                else if(strcmp("size", sp.first) == 0) { // key = size
                    currentObject.size = atoi(sp.second);
                }
                else if(strcmp("color", sp.first) == 0) { // key = size
                    currentObject.color = getColorId(sp.second);
                }
                else {
                    // todo : error handling
                    continue;
                }
            }

            // push the object in the example
            vectPush(Object, currentExample.objects, currentObject);
        }
        if(isCounterExample) {
            vectPush(Example, ms->counterExamples, currentExample);
        }
        else {
            vectPush(Example, ms->examples, currentExample);
        }
    }

    // free section yeah !
    free(sp.first);
    free(sp.second);
    fclose(f);

    return ms;
}

