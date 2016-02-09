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

# Declaration of variables
CC = clang
CC_FLAGS = -Wall -O2 #-Wno-uninitialized
RM = rm -rf
DOXYGEN = doxygen doxygen.cfg
DOC_PATH = doc
LATEX_DOC_PATH = $(DOC_PATH)/latex


# File names
OUT = learning
# Looking for C files in working and subdirectories
SOURCES = $(wildcard *.c) $(wildcard */*.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(OUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUT)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@
# Build documentation
	-$(DOXYGEN)
	-mv $(LATEX_DOC_PATH)/refman.pdf $(DOC_PATH)/documentation.pdf

# To remove generated files except the binary
clean:
	-$(RM) $(OBJECTS) 
	-$(RM) $(LATEX_DOC_PATH)

# Remove generated files
cleanall:
	-$(MAKE) clean
	-$(RM) $(OUT)
