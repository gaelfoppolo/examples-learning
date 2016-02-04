/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The parser
 */

#include "parsers.h"

char* getIncludeFile(char const* pathname, size_t * pos) {
	FILE* fp = fopen(pathname, "r");
	char includeStr[] = "include";
	char c;

	if(fp == NULL) {
		return NULL;
	}

	// skip all the spaces and line breaks til we found something
	while((c = fgetc(fp)) != EOF && (c == ' ' || c == '\t' || c == '\n'));

	if(c == EOF) {
		fclose(fp);
		return NULL;
	}

	String str = strInit(strDuplicate(""));
	strPush(&str, c);

	// reads the word found and stores it
	while((c = fgetc(fp)) != EOF && c != '\n' && c != '\t' && c != ' ') {
		strPush(&str, c);
	}

	// test if str == include (case insensitive) - length check
	if(strLength(&str) != 7) { // 7 is the length of "include" (something something magic numbers)
		free(str.str);
		fclose(fp);
		return NULL;
	}

	// test if str == include (case insensitive) - char comparaison
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

	*pos = ftell(fp); // save the position of the last char of the include

	fclose(fp);

	return str.str;

}

Examples* loadExampleFile(char const* pathname, Model* model, size_t startPos) {
	FILE* fp = fopen(pathname, "r");
	Examples* e = (Examples*)malloc(sizeof(Examples));
	Example dflt;

	char* error;
	int type;

	if(fp == NULL) {
		output(LERROR, SBRED "The file %s does not exist.\n" SDEFAULT, pathname);
		if(e) {
			free(e);
		}
		return NULL;
	}

	if(e == NULL) {
		fclose(fp);
		return NULL;
	}

	vectInit(e->examples);
	vectInit(e->counterExamples);

	// go past the include line
	fseek(fp, startPos, SEEK_SET);

	// find [counter-]example line definition and returns wether it's a counter-example or an exemple
	while((type = getNextExample(fp))) {
		if(type == PARSED_EXAMPLE) {
			vectPush(Example, e->examples, dflt); // add a default example to me modified by parseExample
			if(!parseExample(fp, &error, &vectAt(e->examples, vectSize(e->examples) - 1), model)) {
				// TODO : remove the last example parsed
				if(error) {
					output(LERROR, "\n" SBRED "Error " SDEFAULT " : %s\n", error);
					free(error);
					// The example isn't freed in the case of an error
					return NULL;
				}
			}
		}
		else {
			vectPush(Example, e->counterExamples, dflt);
			if(!parseExample(fp, &error, &vectAt(e->counterExamples, vectSize(e->counterExamples) - 1), model)) {
				// TODO : remove the last example parsed
				if(error) {
					output(LERROR, "\n" SBRED "Error " SDEFAULT " : %s\n", error);
					free(error);
					// The example isn't freed in the case of an error
					return NULL;
				}
			}
		}
	}

	fclose(fp);

	return e;
}

unsigned int getNextExample(FILE* fp) {
	char c;
	readTil(fp, "\n");
	output(L2, "\n");
	while(!feof(fp) && (c = fgetc(fp))) {
		if((c = fgetc(fp)) == '!') {
			// counter-example
			output(L2, "New " SBPURPLE "counter-example" SDEFAULT " found.\n");

			readTil(fp, "\n");
			fseek(fp, -1, SEEK_CUR);
			return PARSED_COUNTEREXAMPLE;
		}
		else if(!feof(fp) && c != ' ' && c != '\t' && c != '\n') {
			output(L2, "New " SBPURPLE "example" SDEFAULT " found.\n");
			readTil(fp, "\n");
			fseek(fp, -1, SEEK_CUR);
			return PARSED_EXAMPLE;
		}
		readTil(fp, "\n");
	}

	return 0;
}

int parseExample(FILE* fp, char** error, Example* ex, Model* m) {
	Object dfltObj;
	Attribute dfltAttr;
	char* name;
	char c;
	struct __basic_string_vector seenObjects; // contains the objects already seen
	int id; // the id of the current object

	*error = NULL;

	readTil(fp, "\n");

	// vectors initialization
	vectInit(ex->objects);
	vectInit(seenObjects.seen);

	// the first fgetc reads the \n of the previous line. The second check wether we are at the begining of the declaration of an object or not
	while((c = fgetc(fp)) != EOF && (c = fgetc(fp)) == '\t') {
		readFileSpaces(fp, "\t ");

		// read the object's name
		name = parseAttrName(fp, error);
		if(name == NULL) {
			vectFree(ex->objects);
			vectFree(seenObjects.seen);
			return 0;
		}

		// check wether the name has already been seen
		id = -1;
		for(unsigned int i = 0; i < vectSize(seenObjects.seen); ++i) {
			if(strcmp(vectAt(seenObjects.seen, i), name) == 0) {
				id = i;
				break;
			}
		}
		if(id == -1) { // if the name have never been seen before, we add it to the seenObjects
			id = vectSize(seenObjects.seen); // its ID is the first ID available (so, the size og the already seen objects)
			// duplicate the string to be able to free all the struct without caring if the string is shared or not
			vectPush(char*, seenObjects.seen, strDuplicate(name));
		}
		// adjust the size of the objects vector to always have object ID = index in the array
		while(vectSize(ex->objects) < vectSize(seenObjects.seen)) {
			vectPush(Object, ex->objects, dfltObj);
			vectInit(vectAt(ex->objects, vectSize(ex->objects) - 1).attributes); // initialize the object we just added tothe array
			vectInit(vectAt(ex->objects, vectSize(ex->objects) - 1).relations); // initialize the object's relations
		}
		vectAt(ex->objects, id).id = id; // set the id of the object
		vectAt(ex->objects, id).name = name; // set the name of the object

		output(L3, "\n");
		output(L2, "Object's name: " SBGREEN "%s" SDEFAULT "", name);

		fgetc(fp); //reads the ':' char after the object's name
		for(unsigned int i = 0; i < vectSize(m->ma); ++i) { // fill the array with as much element that we have possible attributes
			vectPush(Attribute, vectAt(ex->objects, id).attributes, dfltAttr);
		}

		for(unsigned int i = 0; i < vectSize(m->rel); ++i) { // fill the array with as much element that we have possible relations
			vectPush(Attribute, vectAt(ex->objects, id).relations, dfltAttr);
			// inits the relation value to NORELATION (relations are optionnal)
			vectAt(vectAt(ex->objects, id).relations, i).type = TYPE_NORELATION;
		}

		// read the attributes values
		if(!parseExampleObject(fp, error, &vectAt(ex->objects, id), m, &seenObjects)) {
			vectFree(ex->objects);
			vectFree(seenObjects.seen);
			free(name);
			return 0;
		}

		output(L2, "\n");

		readTil(fp, "\n");
	}

	if(!feof(fp)) fseek(fp, -2, SEEK_CUR);

	for(unsigned int i = 0; i < vectSize(seenObjects.seen); ++i) {
		free(vectAt(seenObjects.seen, i)); // we can free all the strings, they are duplicates, not originals
	}

	vectFree(seenObjects.seen);

	return 1;
}

int parseExampleObject(FILE* fp, char** error, Object* o, Model* m, struct __basic_string_vector* seenObjects) {
	*error = NULL;
	char* name;
	int position;
	attrType type;
	char c;

	if(getOutputImportance() < 4) { // design purpose. If > 3, line break will be added by the attributes
		output(L3, "\n");
	}

	while(1) {
		name = parseAttrName(fp, error);

		position = getAttributePosition(name, m);
		if(position == -1) {
			position = getRelationPosition(name, m);
			if(position == -1) {
				*error = cPrint(SBRED "The attribute " SWHITE "%s" SBRED " is not defined." SDEFAULT, name);
				return 0;
			}
			output(L4, "\n"); // if the attributes values are printed, we add a line break
			// the current attribute is a relation
			output(L3, "\t" SBCYAN "%s (relation)" SDEFAULT, name);
			type = TYPE_RELATION; // the type of the attribute to read

			fgetc(fp); // reads the '('

			// reads the relation's value
			parseAttrValue(fp, error, m, type, &vectAt(o->relations, position), position, seenObjects);
		}
		else {
			output(L4, "\n"); // if the attributes values are printed, we add a line break
			output(L3, "\t" SBCYAN "%s" SDEFAULT, name);
			type = vectAt(m->ma, position).mt.type;

			fgetc(fp); // reads the '('

			// reads the attribute's value
			parseAttrValue(fp, error, m, type, &vectAt(o->attributes, position), position, seenObjects);
		}


		free(name); // do not need it after


		if(*error != NULL) {
			return 0;
		}

		readTil(fp, ")"); // reads til the closing parenthesis of the attribute's value
		fgetc(fp); // reads the parenthesis
		readFileSpaces(fp, " \t"); // reads potential spaces
		if((c = fgetc(fp)) != ',') {
			fseek(fp, -1, SEEK_CUR);
			break;
		}

		// loops
	}

	return 1;
}

int getAttributePosition(const char* attr, Model* m) {
	for(unsigned int i = 0; i < vectSize(m->ma); ++i) {
		if(strcmp(attr, vectAt(m->ma, i).name) == 0) {
			return i;
		}
	}

	return -1;
}

int getRelationPosition(const char* rel, Model* m) {
	for(unsigned int i = 0; i < vectSize(m->rel); ++i) {
		if(strcmp(rel, vectAt(m->rel, i)) == 0) {
			return i;
		}
	}

	return -1;
}

void parseAttrValue(FILE* fp, char** error, Model* m, attrType type, Attribute* attr, unsigned int position, struct __basic_string_vector* seenObjects) {
	String str = strInit(strDuplicate(""));
	char c;
	int tmp;

	*error = NULL;

	readFileSpaces(fp, " \t");

	while((c = fgetc(fp)) != EOF && c != ' ' && c != '\t' && c != ')') {
		strPush(&str, c);
	}

	attr->type = type;

	switch(type) {
		case TYPE_INT:
			attr->value = atoi(str.str);
			if(attr->value < vectAt(m->ma, position).mt.inter.min || attr->value > vectAt(m->ma, position).mt.inter.max) {
				*error = cPrint("Integer value not in bounds (expected between %d and %d, found %d)", vectAt(m->ma, position).mt.inter.min, vectAt(m->ma, position).mt.inter.max, attr->value);
				free(str.str);
				return;
			}
			output(L4, ": %s " SYELLOW "(ID = %d)" SDEFAULT, str.str, attr->value);
			free(str.str);
			break;
		case TYPE_ENUM:
			tmp = getEnumId(str.str, m, position);
			if(tmp < 0) { // the value does not exist
				*error = cPrint("Expected an enum value but found '" SPURPLE "%s" SDEFAULT "' instead", str.str);
				free(str.str);
				return;
			}
			attr->value = tmp;
			output(L4, ": %s " SYELLOW "(ID = %d)" SDEFAULT, str.str, attr->value);
			free(str.str);
			break;
		case TYPE_TREE:
			tmp = getTreeId(str.str, m, position);
			if(tmp < 0) { // the value does not exist
				*error = cPrint("Expected a tree value but found '" SPURPLE "%s" SDEFAULT "' instead", str.str);
				free(str.str);
				return;
			}
			attr->value = tmp;
			output(L4, ": %s " SYELLOW "(ID = %d)" SDEFAULT, str.str, attr->value);
			free(str.str);
			break;
		case TYPE_RELATION:
			// search for the objects name in the seenObjects
			tmp = -1;
			for(unsigned int i = 0; i < vectSize(seenObjects->seen); ++i) {
				if(strcmp(vectAt(seenObjects->seen, i), str.str) == 0) {
					tmp = i;
					break;
				}
			}
			if(tmp > -1) { // the object has already been seen. Juste set its ID
				attr->value = tmp;
			}
			else { // never seen - add the object as seen and assign its ID
				attr->value = vectSize(seenObjects->seen);
				vectPush(char*, seenObjects->seen, str.str);
			}
			output(L4, ": %s " SYELLOW "(ID = %d)" SDEFAULT, str.str, attr->value);
			if(tmp > -1) {
				free(str.str);
			}
			break;
	}

	fseek(fp, -1, SEEK_CUR);
}

Model* loadConfigFile(char const* pathname) {
	FILE* fp = fopen(pathname, "r");
	Model* m = (Model*)malloc(sizeof(Model));
	ModelAttribute deflt;
	deflt.name = 0; // silents the uninitialized warning (its ugly, I know)
	char* error;

	vectInit(m->ma);
	vectInit(m->rel);

	if(fp == NULL) {
		output(LERROR, SBRED "The file %s does not exist.\n" SDEFAULT, pathname);
		return NULL;
	}

	/*vectPush(ModelAttribute, m->ma, deflt);
	while(parseConfigLine(fp, &error, &vectAt(m->ma, vectSize(m->ma) - 1))) {
		vectPush(ModelAttribute, m->ma, deflt);
	}*/
	while(parseConfigLine(fp, &error, m));

	//vectRemoveLast(m->ma);

	output(L2, "\n" SBDEFAULT "The model has %d attribute%s and %d relation%s" SDEFAULT ".\n", vectSize(m->ma), vectSize(m->ma) > 1 ? "s": "", vectSize(m->rel), vectSize(m->rel) > 1 ? "s": "");

	if(error) {
		output(LERROR, SBRED "Error: %s\n" SDEFAULT, error);
	}

	fclose(fp);

	return m;
}

int parseConfigLine(FILE* fp, char** error, Model* out) {
	*error = NULL;
	char c;
	ModelAttribute current;
	int isRelation = 0;

	current.name = parseAttrName(fp, error);

	if(!current.name) {
		return 0;
	}

	if(strcmp(current.name, "relation") == 0) {
		isRelation = 1;
		output(L3, SBPURPLE "\nRelations" SDEFAULT " found: ");
	}
	else {
		output(L3, "\nNew attribute found: " SBPURPLE "%s" SDEFAULT "\nType: ", current.name);
	}


	// reads til :
	readFileSpaces(fp, "\t ");
	if((c = fgetc(fp)) != ':') {
		String err = strInit(strDuplicate(SBRED "Unexpected character '" SDEFAULT));
		strPush(&err, c);
		strPushStr(&err, "'.");
		*error = err.str;

		free(current.name);
		return 0;
	}

	ModelType* mt = parseAttrType(fp, error);

	if(mt == NULL) {
		*error = "Failed parsing attribute's type definition";
		free(current.name);
		return 0;
	}

	current.mt = *mt;
	free(mt);

	// check wether it's a relation or a basic attribute
	if(isRelation) {
		for(unsigned int i = 0; i < vectSize(current.mt.enu.enu); ++i) {
			vectPush(char*, out->rel, vectAt(current.mt.enu.enu, i).str);
		}
		vectFree(current.mt.enu.enu);
		free(current.name);
	}
	else {
		vectPush(ModelAttribute, out->ma, current);
	}

	return 1;
}

char* parseAttrName(FILE* fp, char** error) {
	*error = NULL;
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
		output(L3, SBGREEN "Interval" SDEFAULT "\nRange: " SBCYAN "[%d ; %d]\n" SDEFAULT, current->inter.min, current->inter.max);
	}
	else if(c == '(') {
		// reads tree
		output(L3, SBGREEN "Tree\n" SDEFAULT);
		current->type = TYPE_TREE;
		fseek(fp, -1, SEEK_CUR);
		int index = 0;
		Tree* t = parseAttrTypeTree(fp, error, &index, 0);
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
		output(L3, SBGREEN "Enum" SDEFAULT "\n");
		output(L4, "Values: ");
		for(int i = 0; i < vectSize(current->enu.enu); ++i) {
			output(L4, SBCYAN "%s" SBYELLOW " (ID = %d)" SDEFAULT, vectAt(current->enu.enu, i).str, vectAt(current->enu.enu, i).id);
			if (i+1 < vectSize(current->enu.enu)) {
				output(L4, "\n\t");
			} 
		}
		output(L4, "\n");
	}

	return current;
}

// TODO : use fscanf to read integers
Interval* parseAttrTypeInterval(FILE* fp, char** error) {
	char c;
	Interval* current = (Interval*)malloc(sizeof(Interval));
	int min = 0, max = 0, minusMin = 0, minusMax = 0;

	if((c = fgetc(fp)) == '%') {
		if((c = fgetc(fp)) == 'U') {
			current->min = 0;
			current->max = INT_MAX;
		} else {
			current->min = INT_MIN;
			current->max = INT_MAX;
		}
		readFileSpaces(fp, "\n");
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

Tree* parseAttrTypeTree(FILE* fp, char** error, int* index, int indent) {
	char c;
	Tree* t = createLeaf((*index)++, NULL);
	Tree* tmp;

	// reads til '('
	readFileSpaces(fp, "\t ");

	if((c = fgetc(fp)) == EOF || c != '(') {
		if(c == EOF) {
			output(LERROR, "Parenthesis expected.");
		}
		else {
			output(LERROR, "Parenthesis expected but found '%c'.", c);
		}
		freeTree(t);
		free(t);
		return NULL;
	}

	t->str = parseAttrName(fp, error);

	if(t->str == NULL) {
		output(LERROR, SBRED "Tree root value invalid." SDEFAULT);
		freeTree(t);
		free(t);
		return NULL;
	}
	printIndent(indent);
	output(L4, SBCYAN "%s" SBYELLOW " (ID = %d)\n" SDEFAULT, t->str, t->id);

	readFileSpaces(fp, "\t\n ");
	if((c = fgetc(fp)) != ')' && c != ',') {
		output(LERROR, "Expected ')' or ',' but found '%c' instead", c);
		freeTree(t);
		free(t);
		return NULL;
	}

	while(c != ')') {
		// at least one child
		readFileSpaces(fp, ",\t\n ");
		if((c = fgetc(fp)) != '(') {
			output(LERROR, "character '%c' unexpected while parsing the first child of [%s]", c, t->str);
			free(t->str);
			free(t);
			return NULL;
		}
		fseek(fp, -1, SEEK_CUR);
		// reccursive call
		tmp = parseAttrTypeTree(fp, error, index, indent+1);
		if(!tmp) {
			output(LERROR, "An error occured while parsing the first child of [%s]", t->str);
			freeTree(t);
			return NULL;
		}

		addChild(t, tmp);
		free(tmp);

		// we are on the closing parenthesis of the first child.
		if((c = fgetc(fp)) != ',' && c != ')') {
			readFileSpaces(fp, "\t\n ");
			c = fgetc(fp);
		}

		if(c != ')' && c != ',') {
			output(LERROR, "Expected ',' or ')' but '%c' found instead while parsing [%s]", c, t->str);
			freeTree(t);
			return NULL;
		}
	}

	return t;
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
	while((current = fgetc(fp)) != EOF) {
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

void readTil(FILE* fp, char const* set) {
	char current;
	unsigned int i;
	while((current = fgetc(fp)) != EOF) {
		i = 0;
		while(set[i]) {
			if(set[i] == current) {
				fseek(fp, -1, SEEK_CUR);
				return;
			}
			++i;
		}
	}
}

void printIndent(int indent) {
	for (int i = 0; i < indent; ++i) {
		output(L4, "\t");
	}
}
