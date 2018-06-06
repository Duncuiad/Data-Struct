#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100
#define TRUE 1
#define FALSE 0

/* STRUTTURE DATI */
typedef unsigned char Bool;
typedef struct _List List; /* struttura implementata come tabella */
typedef struct _Node Node;

struct _List {
  int allocated;
  int active;
  int *array;
}; /* a livello di implementazione si tratta di una tabella */

struct _Node {
  char name[MAX_STR_LEN]; /* parola rappresentata dal nodo */
  int cComponent; /* componente connessa a cui appartiene il nodo */
  List adjacency;
};

/* METODI LIST */
void constrList(List *list, unsigned int desiredLength);
void destrList(List *list);
void enqueueList(List *list, int value);
int readList(List *list, unsigned int index);
void printList(List *list);
void lightPrintList(List *list);


/* METODI NODE */
void constrNode(Node *node, char *chosenName);
void destrNode(Node *node);
int getDegree(Node *node);
void printNode(Node *node);

#endif
