#include "info.h"

void addInfo(Graph *graph){

  /* Check */
  if (graph -> componentsReady == FALSE) {
    fprintf(stderr, "Errore [info.c - addInfo]: non posso aggiungere graphInfo prima di aver determinato le componenti connesse");
    exit(-1);
  }

  graph -> graphInfo = (Info*) malloc(sizeof(Info)); /* viene rimosso da removeInfo() */

  graph -> graphInfo -> degrees = (int*) malloc((graph -> nodeCount) * sizeof(int));
  graph -> graphInfo -> cardinalities = (int*) calloc(graph -> componentCount, sizeof(int)); /* azzero tutti i valori */
  graph -> graphInfo -> eccentricities = (int*) malloc((graph -> nodeCount) * sizeof(int));
  graph -> graphInfo -> diameters = (int*) malloc((graph -> componentCount) * sizeof(int));

  return;
}

void removeInfo(Info *info) { /* destrGraph chiama automaticamente removeInfo */

  free(info -> degrees);
  free(info -> cardinalities);
  free(info -> eccentricities);
  free(info -> diameters);

  free(info);
  info = NULL;

  return;
}

void getDegreeInfo(Graph *graph) {

  int i;
  int n = graph -> nodeCount;
  int *degs;
  Node *ithNode = graph -> nodeList; /* puntatore all'i-esimo nodo */

  /* Check */
  if (graph -> graphInfo == NULL) {
    fprintf(stderr, "\nErrore [info.c - getDegreeInfo]: non ho ancora aggiunto l'appendice graphInfo al grafo. Chiamare la funzione addInfo\n");
    exit(-1);
  }

  degs = graph -> graphInfo -> degrees; /* shorthand */

  /* Body */
  for (i = 0; i < n; i++, ithNode++) {
    degs[i] = getDegree(ithNode); /* a ogni iterazione ithNode punta all'i-esimo nodo di graph */
  }

  return;
}

void getCardInfo(Graph *graph) {

  int i;
  int n = graph -> nodeCount;
  int c; /* componente connessa */
  int *cards;
  Node *ithNode = graph -> nodeList; /* puntatore all'i-esimo nodo */

  /* Check */
  if (graph -> graphInfo == NULL) {
    fprintf(stderr, "\nErrore [info.c - getCardInfo]: non ho ancora aggiunto l'appendice graphInfo al grafo. Chiamare la funzione addInfo\n");
    exit(-1);
  }

  cards = graph -> graphInfo -> cardinalities;

  /* Body */
  for (i = 0; i < n; i++, ithNode++) {
    c = ithNode -> cComponent;
    cards[c]++;
  }

  return;
}

void getEccentrInfo(Graph *graph) {

  return;
}

void getDiameterInfo(Graph *graph) {

  return;
}
