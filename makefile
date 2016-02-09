##
 #
 # @gaelfoppolo FOPPOLO Gaël
 # @Ebatsin     PHILIP Bastien
 #
 # @brief Makefile
 #
 # To generate : type "make" or "make learning"
 # To clean : type "make clean" or "make extraclean"
 #
##

# Declaration of variables
CC = clang
CC_FLAGS = -Wall -O2
RM = rm -rf
DOXYGEN = doxygen doc/doxygen.cfg


# File names
OUT = learning
# Looking for C files in working and subdirectories
SOURCES = $(wildcard *.c) $(wildcard */*.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(OUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT)
	# Build documentation
	$(DOXYGEN)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@
	
# To remove generated files except the binary
clean:
	-$(RM) $(OBJECTS) 

# Remove generated files
extraclean:
	-$(MAKE) clean
	-$(RM) $(OUT)
