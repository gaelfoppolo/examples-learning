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

learning: parsing-main.o tree.o parser.o colors.o model.o example.o
	gcc -Wall -O2 -o learning parsing-main.o tree.o parser.o colors.o model.o example.o

parsing-main.o: parsing-main.c parser/parser.h
	gcc -Wall -O2 -c parsing-main.c

tree.o: types/tree.c types/tree.h
	gcc -Wall -O2 -c types/tree.c

parser.o: parser/parser.c parser/parser.h types/colors.h types/model.h
	gcc -Wall -O2 -c parser/parser.c

colors.o: types/colors.h types/colors.c
	gcc -Wall -O2 -c types/colors.c

model.o: types/model.c types/model.h types/example.h
	gcc -Wall -O2 -c types/model.c

example.o: types/example.c types/example.h types/basic_object.h types/vector.h
	gcc -Wall -O2 -c types/example.c

clean:
	rm -rf learning *.o
