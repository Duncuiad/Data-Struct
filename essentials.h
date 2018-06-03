#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#define MAX_STR_LEN 100

/* STRUTTURE DATI */
typedef struct _List List; /* struttura implementata come tabella */
typedef struct _Node Node;

/* METODI LIST */
void constrList(List *list, int desiredLength);
void destrList(List *list);
void enqueueList(List *list, int value);
void readList(List *list, int index);


/* METODI NODE */
void constrNode(Node *node, char *name);
void destrNode(Node *node);
void adjoin(Node *node_1, Node *node_2); /* l'azione e' simmetrica: il grafo è non orientato */
int getDegree(Node *node);

#endif
