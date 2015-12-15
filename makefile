##
 #
 # @gaelfoppolo FOPPOLO Gaël
 # @Ebatsin     PHILIP Bastien
 #
 # @brief Makefile
 #
 # To generate : type "make" or "make learning"
 # To clean : type "make clean"
 #
##

learning: main.o tree.o parser.o colors.o parser_struct.o
	gcc -Wall -O2 -o learning main.o tree.o parser.o colors.o parser_struct.o

main.o: main.c parser/parser.h
	gcc -Wall -O2 -c main.c

tree.o: types/tree.c types/tree.h
	gcc -Wall -O2 -c types/tree.c

parser.o: parser/parser.c parser/parser.h types/colors.h types/parser_struct.h types/vector.h
	gcc -Wall -O2 -c parser/parser.c

colors.o: types/colors.h types/colors.c
	gcc -Wall -O2 -c types/colors.c

parser_struct.o: types/parser_struct.c types/parser_struct.h types/vector.h types/colors.h
	gcc -Wall -O2 -c types/parser_struct.c

clean:
	rm -rf learning *.o
