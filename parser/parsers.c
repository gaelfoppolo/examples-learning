/**
 *
 *	@author Bastien Philip (ebatsin)
 *	@author Gaël Foppolo (gaelfoppolo)
 *
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

	// reads until pathname (format : include pathname)
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
		output(LERROR, "%sThe file %s does not exist.%s\n", SBRED, pathname, SDEFAULT);
		if(e) {
			free(e);
		}
		return NULL;
	}

	if(e == NULL) {
		fclose(fp);
		return NULL;
	}

	// inits the fields of the Examples
	vectInit(e->examples);
	vectInit(e->counterExamples);

	// go past the include line
	fseek(fp, startPos, SEEK_SET);

	// find [counter-]example line definition and returns whether it's a counter-example or an exemple
	while((type = getNextExample(fp))) {
		if(type == PARSED_EXAMPLE) {
			vectPush(Example, e->examples, dflt); // add a default example to me modified by parseExample
			if(!parseExample(fp, &error, &vectAt(e->examples, vectSize(e->examples) - 1), model)) {
				// error in the last parsing, we remove the object added
				vectRemoveLast(e->examples);
				if(error) {
					output(LERROR, "\n%sError %s : %s\n", SBRED, SDEFAULT, error);
					free(error);
					// The example isn't freed in the case of an error
					return NULL;
				}
			}
		}
		else { // PARSED_COUNTEREXAMPLE
			vectPush(Example, e->counterExamples, dflt);
			if(!parseExample(fp, &error, &vectAt(e->counterExamples, vectSize(e->counterExamples) - 1), model)) {
				vectRemoveLast(e->counterExamples);
				if(error) {
					output(LERROR, "\n%sError %s : %s\n", SBRED, SDEFAULT, error);
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

	readTil(fp, "\n"); // reads all the line break

	output(L2, "\n");

	while(!feof(fp) && (c = fgetc(fp))) {
		// check the first character of the line, if (!), it's a counter-example
		if((c = fgetc(fp)) == '!') {
			output(L2, "New %scounter-example%s found.\n", SBPURPLE, SDEFAULT);

			readTil(fp, "\n");
			fseek(fp, -1, SEEK_CUR);
			return PARSED_COUNTEREXAMPLE;
		}
		else if(!feof(fp) && c != ' ' && c != '\t' && c != '\n') {
			output(L2, "New %sexample%s found.\n", SBPURPLE, SDEFAULT);
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
	int id; // the id of the current object

	/*
	*	contains the name of the objects already seen
	*	The relations link to an object (ex : on(x5), x5 being the name of an object)
	*	So, each object has an ID, but a relation can be linked to an object not parsed yet
	*	When the first occurence of an object either in a definition or in a relation is seen, it
	*	is added to this array. When seen after, we can use the same ID, and so, store the
	*	object in the right place in the example (its ID matching its index in the array, as
	*	needed by the core)
	*/
	struct StringVector seenObjects;

	*error = NULL;

	readTil(fp, "\n");

	// vectors initialization
	vectInit(ex->objects);
	vectInit(seenObjects.seen);

	// the first fgetc reads the \n of the previous line. The second check whether we are at the begining of the declaration of an object or not
	while((c = fgetc(fp)) != EOF && (c = fgetc(fp)) == '\t') {
		readFileSpaces(fp, "\t ");

		// read the object's name
		name = parseAttrName(fp, error);
		if(name == NULL) {
			vectFree(ex->objects);
			vectFree(seenObjects.seen);
			return 0;
		}

		// check whether the name has already been seen
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

		output(L2, "Object's name: %s%s%s", SBGREEN, name, SDEFAULT);

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

	// if the example is emtpy, print a warning, return 0 but raise no error
	if(vectSize(ex->objects) == 0) {
		output(LERROR | L1, "%sWarning : empty example found (to remove this warning, delete the empty example)%s\n", SBYELLOW, SDEFAULT);
		return 0;
	}

	return 1;
}

int parseExampleObject(FILE* fp, char** error, Object* o, Model* m, struct StringVector* seenObjects) {
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

		position = getAttributePosition(name, m); // get the attribute position in the model
		if(position == -1) { // if not in the attributes, may be a relation or an error
			position = getRelationPosition(name, m); // get the relation position in the model
			if(position == -1) {
				*error = cPrint("%sThe attribute %s%s%s is not defined.%s", SBRED, SWHITE, name, SBRED, SDEFAULT);
				return 0;
			}
			output(L4, "\n"); // if the attributes values are printed, we add a line break
			// the current attribute is a relation
			output(L3, "\t%s%s (relation)%s", SBCYAN, name, SDEFAULT);
			type = TYPE_RELATION; // the type of the attribute to read

			fgetc(fp); // reads the '('

			// reads the relation's value
			parseAttrValue(fp, error, m, type, &vectAt(o->relations, position), position, seenObjects);
		}
		else {
			output(L4, "\n"); // if the attributes values are printed, we add a line break
			output(L3, "\t%s%s%s", SBCYAN, name, SDEFAULT);
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
		if((c = fgetc(fp)) != ',') { // end of the attributes, can exit the loop
			fseek(fp, -1, SEEK_CUR);
			break;
		}
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

void parseAttrValue(FILE* fp, char** error, Model* m, attrType type, Attribute* attr, unsigned int position, struct StringVector* seenObjects) {
	String str = strInit(strDuplicate(""));
	char c;
	int tmp;

	*error = NULL;

	readFileSpaces(fp, " \t");

	// reads and store the value
	while((c = fgetc(fp)) != EOF && c != ' ' && c != '\t' && c != ')') {
		strPush(&str, c);
	}

	attr->type = type;

	switch(type) {
		case TYPE_INT:
			attr->value = atoi(str.str); // in case of error, returns 0, no fail check
			// bounds check (must be in between the min and max autorized by this interval type)
			if(attr->value < vectAt(m->ma, position).mt.inter.min || attr->value > vectAt(m->ma, position).mt.inter.max) {
				*error = cPrint("Integer value not in bounds (expected between %d and %d, found %d)", vectAt(m->ma, position).mt.inter.min, vectAt(m->ma, position).mt.inter.max, attr->value);
				free(str.str);
				return;
			}
			output(L4, ": %s %s(ID = %d)%s", str.str, SYELLOW, attr->value, SDEFAULT);
			free(str.str);
			break;
		case TYPE_ENUM:
			tmp = getEnumId(str.str, m, position);
			if(tmp < 0) { // the value does not exist
				*error = cPrint("Expected an enum value but found '%s%s%s' instead", SPURPLE, str.str, SDEFAULT);
				free(str.str);
				return;
			}
			attr->value = tmp;
			output(L4, ": %s %s(ID = %d)%s", str.str, SYELLOW, attr->value, SDEFAULT);
			free(str.str);
			break;
		case TYPE_TREE:
			tmp = getTreeId(str.str, m, position);
			if(tmp < 0) { // the value does not exist
				*error = cPrint("Expected a tree value but found '%s%s%s' instead", SPURPLE, str.str, SDEFAULT);
				free(str.str);
				return;
			}
			attr->value = tmp;
			output(L4, ": %s %s(ID = %d)%s", str.str, SYELLOW, attr->value, SDEFAULT);
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
			output(L4, ": %s %s(ID = %d)%s", str.str, SYELLOW, attr->value, SDEFAULT);
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
	char* error;

	vectInit(m->ma);
	vectInit(m->rel);

	if(fp == NULL) {
		output(LERROR, "%sThe file %s does not exist.\n%s", SBRED, pathname, SDEFAULT);
		return NULL;
	}

	// a line is a whole 'attributeName : attributeValue' set (multiline in case of a tree)
	while(parseConfigLine(fp, &error, m));

	output(L2, "\n%sThe model has %d attribute%s and %d relation%s%s.\n", SBDEFAULT, vectSize(m->ma), vectSize(m->ma) > 1 ? "s": "", vectSize(m->rel), vectSize(m->rel) > 1 ? "s": "", SDEFAULT);

	if(error) {
		output(LERROR, "%sError: %s\n%s", SBRED, error, SDEFAULT);
	}

	fclose(fp);

	return m;
}

int parseConfigLine(FILE* fp, char** error, Model* out) {
	*error = NULL;
	char c;
	ModelAttribute current;
	int isRelation = 0;
	char* tmp;

	// a line is "attribute-name : value", we read the first part here
	current.name = parseAttrName(fp, error);

	if(!current.name) {
		return 0;
	}

	if(strcmp(current.name, "relation") == 0) { // check for keyword relation (case sensitive)
		isRelation = 1;
		output(L3, "%s\nRelations%s found: ", SBPURPLE, SDEFAULT);
	}
	else {
		output(L3, "\nNew attribute found: %s%s%s\nType: ", SBPURPLE, current.name, SDEFAULT);
	}


	// reads spaces til the separator (':')
	readFileSpaces(fp, "\t ");
	if((c = fgetc(fp)) != ':') {
		tmp = cPrint("%sUnexpected character '%s", SBRED, SDEFAULT);
		String err = strInit(strDuplicate(tmp));
		free(tmp);
		strPush(&err, c);
		strPushStr(&err, "'.");
		*error = err.str;

		free(current.name);
		return 0;
	}

	// read the second part of the line (the value)
	ModelType* mt = parseAttrType(fp, error);

	if(mt == NULL) {
		*error = "Failed parsing attribute's type definition";
		free(current.name);
		return 0;
	}

	current.mt = *mt;
	free(mt);

	// check whether it's a relation or a basic attribute
	// relations are parsed by the enum parsing function, to prevent duplication
	// of code, but we need to convert it in a relation here
	if(isRelation) {
		// convert the enum parsed to a relation
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

	// reads and store the attribute name while the chars are valid
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

	if((c >= '0' && c <= '9') || c == '%' || c == '-') { // either a integer (or negative integer) or a constant (%constant-name)
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
		output(L3, "%sInterval%s\nRange: %s[%d;%d]\n", SBGREEN, SDEFAULT, SBCYAN, current->inter.min, current->inter.max);
	}
	else if(c == '(') { // only trees starts with '('
		// reads tree
		output(L3, "%sTree%s\n", SBGREEN, SDEFAULT);
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
	else { // if none of the above, must be an enum
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
		output(L3, "%sEnum%s\n", SBGREEN, SDEFAULT);
		output(L4, "Values: ");
		for(int i = 0; i < vectSize(current->enu.enu); ++i) { // only pretty print. Does nothing
			output(L4, "%s%s%s (ID = %d)%s", SBCYAN, vectAt(current->enu.enu, i).str, SBYELLOW, vectAt(current->enu.enu, i).id, SDEFAULT);
			if (i+1 < vectSize(current->enu.enu)) {
				output(L4, "\n\t");
			} 
		}
		output(L4, "\n");
	}

	return current;
}

// TODO : use fscanf to read integers
// an interval looks like this : min - max
// or %INT or %UINT
Interval* parseAttrTypeInterval(FILE* fp, char** error) {
	char c;
	Interval* current = (Interval*)malloc(sizeof(Interval));
	int min = 0, max = 0, minusMin = 0, minusMax = 0;

	if((c = fgetc(fp)) == '%') { // the value is a constant (%INT or %UINT)
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

	if(c == '-') { // the number is negative
		minusMin = 1;
	}
	else {
		fseek(fp, -1, SEEK_CUR);
	}

	while((c = fgetc(fp)) && (c >= '0' && c <= '9')) { // reads the first number and stores it
		min = 10 * min + (c - '0');
	}
	if(!c) {
		String err = strInit(strDuplicate("End of file reached while reading interval."));
		*error = err.str;
		free(current);
		return NULL;
	}

	// Finds the separator ('-')
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

	while((c = fgetc(fp)) != EOF && (c >= '0' && c <= '9')) { // reads the second number and stores it
		max = 10 * max + (c - '0');
	}

	// apply the sign
	min = min * (minusMin ? -1 : 1);
	max = max * (minusMax ? -1 : 1);

	// in case interval is given in the wrong ordre, reverse it
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

// an enum look slike this : value1, value2, value3, ...
Enum* parseAttrTypeEnum(FILE* fp, char** error) {
	char c;
	Enum* current = (Enum*)malloc(sizeof(Enum));
	EnumType currentEnu;
	vectInit(current->enu);
	char* name;
	int index = 0;

	// use the attributeName function to parse the values, the allowed characters are the same
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

// a tree looks liek this : (node-name[, (node-name[, (...)])])
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

	t->str = parseAttrName(fp, error); // trees values respect the same syntax as attributes name, can use the same function to parse them

	if(t->str == NULL) {
		output(LERROR, "%sTree root value invalid.%s", SBRED, SDEFAULT);
		freeTree(t);
		free(t);
		return NULL;
	}
	printNChar(L4, '\t', indent);
	output(L4, "%s%s%s (ID = %d)%s\n", SBCYAN, t->str, SBYELLOW, t->id, SDEFAULT);

	readFileSpaces(fp, "\t\n ");
	if((c = fgetc(fp)) != ')' && c != ',') {
		output(LERROR, "Expected ')' or ',' but found '%c' instead", c);
		freeTree(t);
		free(t);
		return NULL;
	}

	// reads while new chilren are found
	while(c != ')') {
		readFileSpaces(fp, ",\t\n ");
		if((c = fgetc(fp)) != '(') {
			output(LERROR, "character '%c' unexpected while parsing the first child of [%s]", c, t->str);
			free(t->str);
			free(t);
			return NULL;
		}
		fseek(fp, -1, SEEK_CUR);

		// reccursive call, get the subtree
		tmp = parseAttrTypeTree(fp, error, index, indent+1);

		if(!tmp) {
			output(LERROR, "An error occured while parsing the first child of [%s]", t->str);
			freeTree(t);
			return NULL;
		}

		addChild(t, tmp); // append the subtree found a a child of t
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

// valide chars are : "[a-zA-Z_]" if first char of the name and "[a-zA-Z_\-0-9]" if not first
int isValidAttrChar(char c, unsigned int first) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') { // check if the character match [a-zA-Z_\-\d] (or [a-zA-Z_] if first character)
		return 1;
	}
	return first ? 0 : ((c >= '0' && c <= '9') || c == '-');
}

// misleading name, reads any char of the set, not only spaces
void readFileSpaces(FILE* fp, char const* set) {
	char current;
	unsigned int i, inSet;
	while((current = fgetc(fp)) != EOF) {
		i = 0;
		inSet = 0;
		while(set[i]) { // check if the current char is in the set
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
		while(set[i]) { // check if the currrent char is in the set
			if(set[i] == current) {
				fseek(fp, -1, SEEK_CUR);
				return;
			}
			++i;
		}
	}
}
