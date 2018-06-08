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

  graph -> edgeCount = graph -> edgeCount + 1;

  return;
}

void importNodes(Graph *graph, char *fileName) {
  FILE *fileStream;
  int check = 0;
  char temp[MAX_STR_LEN];

  /* apro lo stream */
  fileStream = fopen(fileName, "r");

  while (TRUE) {
    check = fscanf(fileStream, "%s", temp);
    if (check != 1) {
      break;  /* l'unica possibilita' che il ciclo continui all'infinito (check == 1) e' che il file non finisca mai */
    }
    addNode(graph, temp);
  }

  fclose(fileStream);

  graph -> nodesReady = TRUE;

  return;
}

void checkForEdges(Graph *graph) {
  int i;
  int j;
  int n = graph -> nodeCount;

  if (graph -> nodesReady == FALSE) {
    fprintf(stderr, "Errore [graph.c - checkForEdges]: non ho ancora importato i nodi");
    exit(-1);
  }

  for (i = 0; i < n; i++) {
    printf("\rSto aggiungendo i lati: %f%% ", 100*((float) i)/n/(n-1)*(2*n-i+1));
    for (j = i + 1; j < n; j++) {

      if (areRelated((graph -> nodeList)[i].name, (graph -> nodeList)[j].name)==TRUE) {
        addEdge(graph, i, j);
      }
    }
  }

  printf("\r                                      "); /* cosmetico */

  graph -> edgesReady = TRUE;
  return;
}


void printGraph(Graph *graph, const char option) {
  /* options: "s" - silent; "n" - normal */
  int i;
  int n = graph -> nodeCount;
  printf("\nGrafo. Nodi: %d. Lati: %d. Componenti connesse: %d.", n, graph -> edgeCount, graph -> componentCount);
  if (option != 's') {
    for (i = 0; i < n; i++) {
      printf("\n[%d]: ", i);
      printNode(&(graph -> nodeList)[i]);
    }
  }
  printf("\n");
  return;
}

void saveGraph(Graph *graph, const char *fileName) {
  FILE *fileStream;
  int i;
  int j; /* contatore per la lista di adiacenza */
  int n = graph -> nodeCount;
  Node *tempNode; /* i-esimo nodo */
  int l; /* lunghezza della lista di adiacenza per ogni nodo */

  /* apro lo stream */
  fileStream = fopen(fileName, "w");

  fprintf(fileStream, "%d\n%d\n%d\n", graph -> nodeCount, graph -> edgeCount, graph -> componentCount);

  for (i = 0; i < n; i++) {
    tempNode = &(graph -> nodeList)[i];
    l = getDegree(tempNode);
    fprintf(fileStream, "%s %d ", tempNode -> name, tempNode -> cComponent);
    for (j = 0; j < l; j++) {
      fprintf(fileStream, "%d ", readList(&(tempNode -> adjacency), j));
    }
    fprintf(fileStream, "\n");
  }

  return;
}
void loadGraph(Graph *graph, const char *fileName);
