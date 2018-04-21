# Macros
CC = gcc
CFLAGS = -std=c90 -pedantic
OBJ = list.o graph.o
HEAD = $(OBJ:.o=.h)
LIB = -lm

# Dependencies
graph.o: list.h
test.o: $(HEAD)

# Commands
test: $(OBJ) test.o
	-rm -f *.gch
	$(CC) $(CFLAGS) -o $@.x $(OBJ) test.o $(LIB)
