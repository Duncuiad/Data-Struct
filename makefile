# Macros
CC = gcc
CFLAGS = -std=c89 -pedantic
OBJ = essentials.o graph.o
HEAD = $(OBJ:.o=.h)
LIB = -lm

# Dependencies
graph.o: essentials.h
test.o: $(HEAD)

# Commands
test: $(OBJ) test.o
	-rm -f *.gch
	$(CC) $(CFLAGS) -o $@.x $(OBJ) test.o $(LIB)
