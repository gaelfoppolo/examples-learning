#include "parsers.h"

char* getIncludeFile(char const* pathname) {
	FILE* fp = fopen(pathname, "r");
	char includeStr[] = "include";
	char c;

	if(fp == NULL) {
		return NULL;
	}

	while((c = fgetc(fp)) != EOF && (c == ' ' || c == '\t' || c == '\n'));

	if(c == EOF) {
		fclose(fp);
		return NULL;
	}

	String str = strInit(strDuplicate(""));
	strPush(&str, c);

	while((c = fgetc(fp)) != EOF && c != '\n' && c != '\t' && c != ' ') {
		strPush(&str, c);
	}

	// test if str == include (case insensitive)
	if(strLength(&str) != 7) { // 7 is the length of "include" (something something magic numbers)
		free(str.str);
		fclose(fp);
		return NULL;
	}

	for(int i = 0; i < strLength(&str); ++i) {
		if(includeStr[i] != str.str[i] && includeStr[i] != (str.str[i]) + ('a' - 'A')) { // test for upper and lower case as include is case insensitive
			// not include
			free(str.str);
			fclose(fp);
			return NULL;
		}
	}

	// reads until pathname
	while((c = fgetc(fp)) != EOF && (c == ' ' || c == '\t' || c == '\n'));

	// stores pathname
	free(str.str);
	str = strInit(strDuplicate(""));
	strPush(&str, c);
	while((c = fgetc(fp)) != EOF && c != '\n' && c != '\t' && c != ' ') {
		strPush(&str, c);
	}


	fclose(fp);

	return str.str;

}

Model* loadConfigFile(char const* pathname) {
	FILE* fp = fopen(pathname, "r");
	ModelAttribute* ma;
	char* error;

	if(fp == NULL) {
		printf("The file %s does not exist.\n", pathname);
		return NULL;
	}

	while((ma = parseConfigLine(fp, &error))) {
		// TODO : handling
	}

	if(error) {
		printf("Error : %s\n", error);
	}

	return NULL;
}

ModelAttribute* parseConfigLine(FILE* fp, char** error) {
	*error = NULL;
	char c;
	ModelAttribute* current = (ModelAttribute*)malloc(sizeof(ModelAttribute));

	current->name = parseAttrName(fp, error);

	if(!current->name) {
		free(current->name);
		free(current);
		return NULL;
	}

	printf("New attribute found : %s\n", current->name);

	// reads til :
	readFileSpaces(fp, "\t ");
	if((c = fgetc(fp)) != ':') {
		String err = strInit(strDuplicate("Unexpected character '"));
		strPush(&err, c);
		strPushStr(&err, "'.");
		*error = err.str;

		free(current->name);
		free(current);
		return NULL;
	}

	ModelType* mt = parseAttrType(fp, error);

	if(mt == NULL) {
		*error = "Failed parsing attribute's type definition";
		free(current->name);
		free(current);
		return NULL;
	}

	current->mt = *mt;

	return current;
}

char* parseAttrName(FILE* fp, char** error) {
	error = NULL;
	char c;
	String attrName = strInit(strDuplicate(""));
	readFileSpaces(fp, "\t ");
	if(feof(fp)) {
		free(attrName.str);
		return NULL;
	}
	if((c = fgetc(fp)) && isValidAttrChar(c, 1)) {
		strPush(&attrName, c);
		while((c = fgetc(fp)) && isValidAttrChar(c, 0)) {
			strPush(&attrName, c);
		}
	}
	fseek(fp, -1, SEEK_CUR);

	if(strLength(&attrName) == 0) {
		free(attrName.str);
		return NULL;
	}

	return attrName.str;
}

ModelType* parseAttrType(FILE* fp, char** error) {
	*error = NULL;
	char c;
	ModelType* current = (ModelType*)malloc(sizeof(ModelType));

	readFileSpaces(fp, "\t ");
	if(feof(fp)) {
		free(current);
		return NULL;
	}

	c = fgetc(fp);

	if((c >= '0' && c <= '9') || c == '%') {
		// reads int
		current->type = TYPE_INT;
		fseek(fp, -1, SEEK_CUR);
		Interval* it = parseAttrTypeInterval(fp, error);
		if(it == NULL) {
			free(current);
			return NULL;
		}
		current->inter = *it;
		printf("Interval : %d - %d\n", current->inter.min, current->inter.max);
	}
	else if(c == '(') {
		// reads tree
		current->type = TYPE_TREE;
		fseek(fp, -1, SEEK_CUR);
		Tree* t = parseAttrTypeTree(fp, error);
		if(t == NULL) {
			free(current);
			return NULL;
		}
		current->tree = *t;
	}
	else {
		//reads enum
		current->type = TYPE_ENUM;
		fseek(fp, -1, SEEK_CUR);
		Enum* e = parseAttrTypeEnum(fp, error);
		if(e == NULL) {
			free(current);
			return NULL;
		}
		current->enu = *e;
		printf("Enum : ");
		for(int i = 0; i < vectSize(current->enu.enu); ++i) {
			printf("%s(id=%d), ", vectAt(current->enu.enu, i).str, vectAt(current->enu.enu, i).id);
		}
		printf("\n");
	}

	return current;
}

// TODO : use fscanf to read integers
Interval* parseAttrTypeInterval(FILE* fp, char** error) {
	char c;
	Interval* current = (Interval*)malloc(sizeof(Interval));
	int min = 0, max = 0, minusMin = 0, minusMax = 0;

	if((c = fgetc(fp)) == '%') {
		readFileSpaces(fp, "\n");
		current->min = INT_MIN;
		current->max = INT_MAX;
		while((c = fgetc(fp)) && c != '\n');
		return current;
	}
	else if(!c) {
		free(current);
		return NULL;
	}

	if(c == '-') {
		minusMin = 1;
	}
	else {
		fseek(fp, -1, SEEK_CUR);
	}

	while((c = fgetc(fp)) && (c >= '0' && c <= '9')) {
		min = 10 * min + (c - '0');
	}
	if(!c) {
		String err = strInit(strDuplicate("End of file reached while reading interval"));
		*error = err.str;
		free(current);
		return NULL;
	}

	// Finds the first '-'
	if(c != '-') {
		while((c = fgetc(fp)) && (c == ' ' || c == '\t'));
		if(c != '-') {
			String err = strInit(strDuplicate(c == EOF ? "End of file reached while reading interval" : "Unallowed character found in place of '-' in interval"));
			*error = err.str;
			free(current);
			return NULL;
		}
	}

	while((c = fgetc(fp)) && (c == ' ' || c == '\t'));

	if(c == '-') {
		minusMax = 1;
	}
	else {
		fseek(fp, -1, SEEK_CUR);
	}

	while((c = fgetc(fp)) != EOF && (c >= '0' && c <= '9')) {
		max = 10 * max + (c - '0');
	}

	min = min * (minusMin ? -1 : 1);
	max = max * (minusMax ? -1 : 1);

	if(min > max) {
		current->min = max;
		current->max = min;
	}
	else {
		current->min = min;
		current->max = max;
	}

	while((c = fgetc(fp)) && c != '\n');

	return current;
}

Enum* parseAttrTypeEnum(FILE* fp, char** error) {
	char c;
	Enum* current = (Enum*)malloc(sizeof(Enum));
	EnumType currentEnu;
	vectInit(current->enu);
	char* name;
	int index = 0;
	while((name = parseAttrName(fp, error))) {
		if(name[0] == '\0') { // end of line, no more enum possibilities
			free(name);
			break;
		}

		// adds it to the enum
		currentEnu.id = index++;
		currentEnu.str = strDuplicate(name);
		vectPush(EnumType, current->enu, currentEnu);

		readFileSpaces(fp, "\t "); // move to the next possible value
		if((c = fgetc(fp)) == EOF || c == '\n') {
			free(name);
			break;
		}
		free(name);
	}

	if(*error) {
		free(current); // TODO : fix possible data loss in strings stored in the vector
		return NULL;
	}

	return current;
}

Tree* parseAttrTypeTree(FILE* fp, char** error) {
	char c;
	while((c = fgetc(fp)) != EOF && c != '\n');
	return NULL;
}

int isValidAttrChar(char c, unsigned int first) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-' || c == '_') {
		return 1;
	}
	return first ? 0 : (c >= '0' && c <= '9');
}

void readFileSpaces(FILE* fp, char const* set) {
	char current;
	unsigned int i, inSet;
	while((current = fgetc(fp))) {
		i = 0;
		inSet = 0;
		while(set[i]) {
			if(set[i] == current) {
				inSet = 1;
				break;
			}
			++i;
		}
		if(!inSet) {
			fseek(fp, -1, SEEK_CUR);
			return;
		}
	}
}
