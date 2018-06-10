# Macros
CC = gcc
CFLAGS = -std=c89 -pedantic
OBJ = essentials.o string.o graph.o info.o
HEAD = $(OBJ:.o=.h)
LIB = -lm

# Dependencies
graph.o: essentials.h string.h
info.o: essentials.h graph.h
test.o: $(HEAD)

# Commands
test: $(OBJ) test.o
	-rm -f *.gch
	$(CC) $(CFLAGS) -o $@.x $(OBJ) test.o $(LIB)
