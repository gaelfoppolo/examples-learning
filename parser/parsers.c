/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The parser
 */

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
	Model* m = (Model*)malloc(sizeof(Model));
	ModelAttribute deflt;
	deflt.name = 0; // silents the uninitialized warning
	char* error;

	vectInit(m->ma);

	if(fp == NULL) {
		printf("The file %s does not exist.\n", pathname);
		return NULL;
	}

	vectPush(ModelAttribute, m->ma, deflt);
	while(parseConfigLine(fp, &error, &vectAt(m->ma, vectSize(m->ma) - 1))) {
		vectPush(ModelAttribute, m->ma, deflt);
	}

	vectRemoveLast(m->ma);

	printf("The model has %d attribute(s).\n", vectSize(m->ma));

	if(error) {
		printf("Error: %s\n", error);
	}

	fclose(fp);

	return m;
}

void freeModel(Model* mo) {
	if(!mo) return;
	for(unsigned int i = 0; i < vectSize(mo->ma); ++i) {
		if(vectAt(mo->ma, i).name) {
			free(vectAt(mo->ma, i).name);
		}
		switch(vectAt(mo->ma, i).mt.type) {
			case TYPE_INT: break;
			case TYPE_ENUM:
				for(unsigned int j = 0; j < vectSize(vectAt(mo->ma, i).mt.enu.enu); ++j) {
					if(vectAt(vectAt(mo->ma, i).mt.enu.enu, j).str) {
						free(vectAt(vectAt(mo->ma, i).mt.enu.enu, j).str);
					}
				}
				vectFree(vectAt(mo->ma, i).mt.enu.enu);
				break;
			case TYPE_TREE:
				if(vectAt(mo->ma, i).mt.tree.left) {
					freeTree(vectAt(mo->ma, i).mt.tree.left);
				}
				if(vectAt(mo->ma, i).mt.tree.right) {
					freeTree(vectAt(mo->ma, i).mt.tree.right);
				}
				if(vectAt(mo->ma, i).mt.tree.str) {
					free(vectAt(mo->ma, i).mt.tree.str);
				}
				break;
		}
	}
	vectFree(mo->ma);
	free(mo);
}

int parseConfigLine(FILE* fp, char** error, ModelAttribute* out) {
	*error = NULL;
	char c;

	out->name = parseAttrName(fp, error);

	if(!out->name) {
		free(out->name);
		return 0;
	}

	printf("\nNew attribute found: \x1B[1;31m%s\x1B[0m\n", out->name);

	// reads til :
	readFileSpaces(fp, "\t ");
	if((c = fgetc(fp)) != ':') {
		String err = strInit(strDuplicate("Unexpected character '"));
		strPush(&err, c);
		strPushStr(&err, "'.");
		*error = err.str;

		free(out->name);
		return 0;
	}

	ModelType* mt = parseAttrType(fp, error);

	if(mt == NULL) {
		*error = "Failed parsing attribute's type definition";
		free(out->name);
		return 0;
	}

	out->mt = *mt;
	free(mt);

	return 1;
}

char* parseAttrName(FILE* fp, char** error) {
	error = NULL;
	char c;
	String attrName = strInit(strDuplicate(""));
	readFileSpaces(fp, "\t \n");
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

	if((c >= '0' && c <= '9') || c == '%' || c == '-') {
		// reads int
		current->type = TYPE_INT;
		fseek(fp, -1, SEEK_CUR);
		Interval* it = parseAttrTypeInterval(fp, error);
		if(it == NULL) {
			free(current);
			return NULL;
		}
		current->inter = *it;
		free(it);
		printf("\x1B[1;32mInterval:\x1B[0m %d - %d\n", current->inter.min, current->inter.max);
	}
	else if(c == '(') {
		// reads tree
		current->type = TYPE_TREE;
		fseek(fp, -1, SEEK_CUR);
		int index = 0;
		Tree* t = parseAttrTypeTree(fp, error, &index);
		if(t == NULL) {
			free(current);
			return NULL;
		}
		current->tree = *t;
		free(t);
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
		free(e);
		printf("\x1B[1;32mEnum:\x1B[0m ");
		for(int i = 0; i < vectSize(current->enu.enu); ++i) {
			printf("\x1B[1;36m%s\x1B[0m \x1B[33m(ID = %d)\x1B[0m", vectAt(current->enu.enu, i).str, vectAt(current->enu.enu, i).id);
			if (i+1 < vectSize(current->enu.enu)) printf(", ");	
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
		fseek(fp, -1, SEEK_CUR);
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
		String err = strInit(strDuplicate("End of file reached while reading interval."));
		*error = err.str;
		free(current);
		return NULL;
	}

	// Finds the first '-'
	if(c != '-') {
		while((c = fgetc(fp)) && (c == ' ' || c == '\t'));
		if(c != '-') {
			String err = strInit(strDuplicate(c == EOF ? "End of file reached while reading interval." : "Unallowed character found in place of '-' in interval."));
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

	fseek(fp, -1, SEEK_CUR);
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
		for(int i = 0; i < vectSize(current->enu); ++i) {
			free(vectAt(current->enu, i).str);
		}
		free(current);
		return NULL;
	}

	return current;
}

Tree* parseAttrTypeTree(FILE* fp, char** error, int* index) {
	char c;
	Tree* t = (Tree*)malloc(sizeof(Tree));
	t->id = (*index)++;


	// reads til '('
	readFileSpaces(fp, "\t ");

	if((c = fgetc(fp)) == EOF || c != '(') {
		if(c == EOF) {
			printf("Parenthesis expected.");
		}
		else {
			printf("Parenthesis expected but found '%c'.", c);
		}
		free(t);
		return NULL;
	}

	t->str = parseAttrName(fp, error);

	if(t->str == NULL) {
		printf("Tree root value invalid.");
		free(t->str);
		free(t);
		return NULL;
	}

	printf("Name: \x1B[1;36m%s\x1B[0m \x1B[33m(ID = %d)\x1B[0m\n", t->str, t->id);

	readFileSpaces(fp, "\t\n ");
	if((c = fgetc(fp)) != ')' && c != ',') {
		printf("Expected ')' or ',' but found '%c' instead", c);
		free(t->str);
		free(t);
		return NULL;
	}

	if(c == ')') {
		printf("[\x1B[1;36m%s\x1B[0m] No child detected, \x1B[1;32mleaf\x1B[0m.\n", t->str);
		// leaf
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	else {
		// at least one child
		printf("[\x1B[1;36m%s\x1B[0m] First child: \n", t->str);
		readFileSpaces(fp, "\t\n ");
		if((c = fgetc(fp)) != '(') {
			printf("character '%c' unexpected while parsing the first child of [%s]", c, t->str);
			free(t->str);
			free(t);
			return NULL;
		}
		fseek(fp, -1, SEEK_CUR);
		// reccursive call
		t->left = parseAttrTypeTree(fp, error, index);
		if(!t->left) {
			printf("An error occured while parsing the first child of [%s]", t->str);
			free(t->str);
			free(t);
			return NULL;
		}

		// we are on the closing parenthesis of the first child.
		if((c = fgetc(fp)) != ',' && c != ')') {
			readFileSpaces(fp, "\t\n ");
			c = fgetc(fp);
		}

		if(c == ')') {
			// no second child
			printf("[\x1B[1;36m%s\x1B[0m] No second child detected.\n", t->str);
			t->right = NULL;
			return t;
		}
		else if(c != ',') {
			printf("Expected ',' but '%c' found instead while parsing [%s]", c, t->str);
			free(t->str);
			free(t);
			return NULL;
		}
		else {
			// right child
			printf("[\x1B[1;36m%s\x1B[0m] Second child: \n", t->str);
			readFileSpaces(fp, "\t\n ");
			if((c = fgetc(fp)) != '(') {
				printf("character '%c' unexpected while parsing the second child of [%s]", c, t->str);
				free(t->str);
				free(t);
				return NULL;
			}
			fseek(fp, -1, SEEK_CUR);
			t->right = parseAttrTypeTree(fp, error, index);
			if(!t->right) {
				printf("An error occured while parsing the second child of [%s]", t->str);
				free(t->str);
				free(t);
				return NULL;
			}

			// go to the last parenthesis
			readFileSpaces(fp, "\t\n ");
			if(fgetc(fp) != ')') {
				printf("Expected a closing parenthesis at the end of [%s]", t->str);
				free(t->str);
				free(t);
				return NULL;
			}
			return t;
		}

	}

	return NULL;
}

int isValidAttrChar(char c, unsigned int first) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
		return 1;
	}
	return first ? 0 : ((c >= '0' && c <= '9') || c == '-');
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
