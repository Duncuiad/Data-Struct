#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

/* STRUTTURE DATI */
typedef struct _List List; /* struttura implementata come tabella */
typedef struct _Node Node;

/* METODI LIST */
void constrList(List *list, int desiredLength);
void destrList(List *list);
void enqueueList(List *list, int value);
int readList(List *list, int index);


/* METODI NODE */
void constrNode(Node *node, char *name);
void destrNode(Node *node);
int getDegree(Node *node);

#endif
