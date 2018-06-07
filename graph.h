#ifndef GRAPH_H
#define GRAPH_H

#include  <stdio.h>

#include "essentials.h"
#include "string.h"

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
void importNodes(Graph *graph, char *fileName);
void checkForEdges(Graph *graph);
void printGraph(Graph *graph, const char option);

#endif
