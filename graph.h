#ifndef GRAPH_H
#define GRAPH_H

#include  <stdio.h>

#include "essentials.h"
#include "relations.h"

typedef struct _Graph Graph;

struct _Graph {

  /* MEMBERS */
  int allocated; /* Il grafo è implementato come tabella di nodi */
  int nodeCount;
  int edgeCount;
  Node *nodeList;
  int componentCount;

  Info *graphInfo;

  /* FLAGS (mostly debug) */
  Bool isEmpty;
  Bool nodesReady;
  Bool edgesReady;
  Bool componentsReady;

};

/* METODI GRAPH */
void constrGraph(Graph *graph);
void destrGraph(Graph *graph);
void addNode(Graph *graph, char *word);
void addEdge(Graph *graph, unsigned int firstNode, unsigned int secondNode);
void importNodes(Graph *graph, const char *fileName);
void checkForEdges(Graph *graph);
void checkForComponents(Graph *graph);
void importGraph(Graph *graph, const char * fileName);
void printGraph(Graph *graph, const char option);
void saveGraph(Graph *graph, const char *fileName);
void loadGraph(Graph *graph, const char *fileName);

char *getWord(Graph *graph, unsigned int index);

#endif
