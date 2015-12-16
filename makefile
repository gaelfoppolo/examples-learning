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

learning: main.o tree.o parser.o color.o shape.o model.o example.o output.o basic_object.o core.o
	clang -Wall -O2 -o learning main.o tree.o parser.o color.o shape.o model.o example.o output.o basic_object.o core.o

main.o: main.c types/tree.h parser/parser.h app/output.h app/core.h
	clang -Wall -O2 -c main.c

tree.o: types/tree.c types/tree.h
	clang -Wall -O2 -c types/tree.c

parser.o: parser/parser.c parser/parser.h types/model.h
	clang -Wall -O2 -c parser/parser.c

color.o: types/color.h types/color.c
	clang -Wall -O2 -c types/color.c

shape.o: types/shape.h types/shape.c
	clang -Wall -O2 -c types/shape.c

model.o: types/model.c types/model.h types/example.h
	clang -Wall -O2 -c types/model.c

example.o: types/example.c types/example.h types/basic_object.h types/vector.h
	clang -Wall -O2 -c types/example.c

output.o: app/output.c app/output.h types/basic_object.h
	clang -Wall -O2 -c app/output.c

basic_object.o: types/basic_object.c types/basic_object.h types/vector.h types/color.h types/shape.h
	clang -Wall -O2 -c types/basic_object.c

core.o: app/core.c app/core.h types/model.h types/tree.h
	clang -Wall -O2 -c app/core.c

clean:
	rm -rf learning *.o
