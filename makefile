##
 #
 # @gaelfoppolo FOPPOLO Gaël
 # @Ebatsin PHILIP Bastien
 #
 # @brief Makefile
 #
 # To generate : type "make" or "make learning"
 # to clean : type "make clean"
## 

learning: main.o tree.o vector_int.o parser.o
	gcc -Wall -o learning main.o tree.o vector_int.o parser.o

main.o: main.c types/tree.c types/shape.h
	gcc -c -Wall main.c 

tree.o: types/tree.c types/tree.h makefile
	gcc -c -Wall types/tree.c

vector_int.o: types/vector_int.c types/vector_int.h makefile
	gcc -c -Wall types/vector_int.c

parser.o: parser/parser.c parser/parser.h types/color.h types/shape.h makefile
	gcc -c -Wall parser/parser.c	

clean:	
	rm -rf learning *.o
