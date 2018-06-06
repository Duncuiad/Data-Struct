#include "graph.h"

/* METODI GRAPH */

void constrGraph(Graph *graph) {
  graph -> allocated = 0;
  graph -> nodeCount = 0;
  graph -> edgeCount = 0;
  graph -> nodeList = NULL;
  graph -> componentCount = 0;
  graph -> isEmpty = TRUE;
  graph -> nodesReady = FALSE;
  graph -> edgesReady = FALSE;
  return;
}

void destrGraph(Graph *graph) {
  int i;
  int n = graph -> nodeCount;
  for (i = 0; i < n; i++) {
    destrNode(&(graph -> nodeList)[n-1-i]);
  }
  free(graph -> nodeList);
  return;
}

void addNode(Graph *graph, char *word) {
  /* la definizione ricalca quella di enqueueList: se non c'e' piu' spazio raddoppio il vettore allocato */
  Node temp;
  Node *pointer; /* di appoggio */
  int i;
  int n = graph -> allocated;

  if (graph -> allocated == graph -> nodeCount) {

    pointer = graph -> nodeList;
    graph -> nodeList = (Node*) malloc((n == 0 ? 1 : 2 * n) * sizeof(Node));

    for (i = 0; i < n; i++) {
      (graph -> nodeList)[i] = pointer[i];
    }

    graph -> allocated = (n == 0 ? 1 : 2 * n);
    free(pointer);
  }

  constrNode(&temp, word);
  (graph -> nodeList)[graph -> nodeCount] = temp;
  graph -> nodeCount = (graph -> nodeCount) + 1;
  /* non chiamo destrNode perche' constrNode da solo crea un Nodo con lista di adiacenza == NULL */
  return;
}

void addEdge(Graph *graph, unsigned int firstNode, unsigned int secondNode) {

  /* Check bounds */
  if (firstNode >= graph -> nodeCount) {
    printf("Errore: il grafo non contiene il primo nodo tra i due dati in input");
    exit(-1);
  }
  if (secondNode >= graph -> nodeCount) {
    printf("Errore: il grafo non contiene il secondo nodo tra i due dati in input");
    exit(-1);
  }

  /* Body */
  enqueueList(&((graph -> nodeList)[firstNode].adjacency), secondNode);
  enqueueList(&((graph -> nodeList)[secondNode].adjacency), firstNode);

  return;
}

void printGraph(Graph *graph) {
  int i;
  int n = graph -> nodeCount;
  for (i = 0; i < n; i++) {
    printf("[%d]: ", i);
    printNode(&(graph -> nodeList)[i]);
  }
  return;
}
