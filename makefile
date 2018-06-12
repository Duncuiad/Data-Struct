# Macros
CC = gcc
CFLAGS = -std=c89 -pedantic
OBJ = essentials.o relations.o graph.o info.o sorting.o
HEAD = $(OBJ:.o=.h)
LIB = -lm

# Dependencies
graph.o: essentials.h relations.h
info.o: essentials.h graph.h
sorting.o: essentials.h relations.h graph.h info.h
test.o: $(HEAD)

# Commands
test: $(OBJ) test.o
	-rm -f *.gch
	$(CC) $(CFLAGS) -o $@.x $(OBJ) test.o $(LIB)
