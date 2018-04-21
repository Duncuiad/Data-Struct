# Macros
CC = gcc
CFLAGS = -std=c90 -pedantic
OBJ = list_int.o graph.o
HEAD = $(OBJ:.o=.h)
LIB = -lm

# Dependencies
graph.o: list_int.h
test.o: $(HEAD)

# Commands
test: $(OBJ) test.o
	-rm -f *.gch
	$(CC) $(CFLAGS) -o $@.x $(OBJ) test.o $(LIB)
