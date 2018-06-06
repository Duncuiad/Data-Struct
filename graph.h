#ifndef GRAPH_H
#define GRAPH_H

#include  <stdio.h>

#include "essentials.h"

typedef struct _Graph Graph;

struct _Graph {

  /* MEMBERS */
  int allocated; /* Il grafo è implementato come tabella di nodi */
  int nodeCount;
  int edgeCount;
  Node *nodeList;
  int componentCount;

  /* FAC: INFO */

  /* FLAGS (mostly debug) */
  Bool isEmpty;
  Bool nodesReady;
  Bool edgesReady;

};

/* METODI GRAPH */
void constrGraph(Graph *graph);
void destrGraph(Graph *graph);
void addNode(Graph *graph, char *word);
void addEdge(Graph *graph, unsigned int firstNode, unsigned int secondNode);
void printGraph(Graph *graph);

#endif
