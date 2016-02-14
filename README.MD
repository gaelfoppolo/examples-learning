## Examples learning

abstract - On le met pas ? Déja le sujet lui même est un bon résumé, pas trop besoin de faire plus court

## Project

This project aims to find similarities in a set of formatted data. It works using the concept of examples and objects, each example beeing composed of objects, each one beeing composed of characteristics (or attributes) and relations with other object in the same example. The program tries to find the similarities that carry the most information.

This project is an enginnering school programming subject : [Subject](https://github.com/gaelfoppolo/examples-learning/blob/step4/subject.pdf)

[Documentation](http://gaelfoppolo.github.io/examples-learning/)

## How to use

The programs use two different types of file to generate the solutions of a problem.
The informations on the _model_ (ie: the definition of the object's attributes, the possible relations, the bounds of the values, etc...) is defined in a file with the _.cfg_ extension. It follows this syntax :
```
attribute-name : attribute-value
relation : relation-name[, relation-name]
# each value can be of one of the three followinf types :
# integer, in interval, defined like this :
integer-attribute : <min> - <max>
# an enumeration item, from an enumeration, defined like this :
enum-attribute : <item> [, <item>]
# a tree node, from a tree, defined like this :
tree-attribute : (<node-name>, (<child-name>[, ...]), (<child-name>))
# a tree definition can be split on more than one line to allow a greater readability

# to define the possible relations between the objects, you must use the 'relation' keyword
relation: relation-name[, relation-name]
```

The model defines the rules behind the examples, which are defined in a file with the _.exp_ extension. It follows this syntax :
```
include <path-to-model-file>

Example-name
	object-name:attribute-name(attribute-value)[, attribute-name(attribute-value)][,relation-name(object-linked-name)]
	[...]
!Counter-example-name
	# same syntax as of the examples
```

## Options and usage

The program only need the path to the example file as a parameter :
```
learning <path-to-example-file>
```

It accept some options :
**--help | -h**
Print some help on basic options

**--expand-relations**
When the solution have relations, print the whole object linked instead of its name

**--no-generalization**
Skip the generalization step (print all the solutions, even duplicates and non-important solutions)

**--no-counter-examples**
Skip the counter-examples handling. Prevent the suppression of solutions, even if they match the counter-examples in the example file

**--no-color**
Remove all colors from the output

**-v**
Verbosity level, you can use up to 4 -v to add informations

### How to populate inputs files

Pas comprit ce que tu veux dire par "populate input files"
`namefile.txt`

**bold** 

```
// Foo
var bar = 0;
```
 
### How to run

explain how to run with some examples of combinaisons of options
Pas comprit non plus, déja expliqué dans usage nan ?

## Slides

link to slides
