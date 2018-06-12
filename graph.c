#include "graph.h"

/* METODI GRAPH */

void constrGraph(Graph *graph) {
  graph -> allocated = 0;
  graph -> nodeCount = 0;
  graph -> edgeCount = 0;
  graph -> nodeList = NULL;
  graph -> componentCount = 0;

  graph -> graphInfo = NULL; /* la variabile graphInfo e' gestita nella libreria info.c */

  graph -> isEmpty = TRUE;
  graph -> nodesReady = FALSE;
  graph -> edgesReady = FALSE;
  graph -> componentsReady = FALSE;
  return;
}

void destrGraph(Graph *graph) {
  int i;
  int n = graph -> nodeCount;
  for (i = 0; i < n; i++) {
    destrNode(&(graph -> nodeList)[n-1-i]);
  }
  free(graph -> nodeList);
  if (graph -> graphInfo != NULL) {
    removeInfo(graph -> graphInfo);
  }
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

void importNodes(Graph *graph, const char *fileName) {
  FILE *fileStream;
  int check = 0;
  char temp[MAX_STR_LEN];

  /* apro lo stream */
  fileStream = fopen(fileName, "r");

  /* controllo che il file esista */
  if (fileStream == NULL) {
    fprintf(stderr, "Errore [graph.c - importNodes]: non esiste un file con questo nome (%s)", fileName);
    exit(-1);
  }

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

  /* Check state */
  if (graph -> nodesReady == FALSE) {
    fprintf(stderr, "Errore [graph.c - checkForEdges]: non ho ancora importato i nodi");
    exit(-1);
  }

  /* Body */
  for (i = 0; i < n; i++) {
    printf("\rSto aggiungendo i lati: %f%% ", 100*((float) i)/n/(n-1)*(2*n-i+1)); /* loading bar */
    for (j = i + 1; j < n; j++) {

      if (areRelated((graph -> nodeList)[i].name, (graph -> nodeList)[j].name)) {
        addEdge(graph, i, j);
      }
    }
  }

  printf("\r                                      "); /* cosmetico */

  /* Update state */
  graph -> edgesReady = TRUE;
  return;
}

void checkForComponents(Graph *graph) { /* BFS */
  int *queue;
  unsigned int head = 0;
  unsigned int tail = -1;
  unsigned int i = 0; /* tiene traccia dell'i-esimo nodo in nodeList per saltare quelli marcati */
  unsigned int n = graph -> nodeCount;
  Node *tempNode; /* puntatore al nodo corrente */
  List *tempList; /* puntatore alla lista di adiacenza del nodo corrente nella coda */
  unsigned int l; /* lunghezza della lista di adiacenza */
  unsigned int j; /* contatore per la lista di adiacenza */
  unsigned int currentAdjacent;
  unsigned int componentCount = 0;

  /* Check */
  if (graph -> edgesReady == FALSE) {
    fprintf(stderr, "Errore [graph.c - checkForComponents]: non ho ancora determinato i lati del grafo");
    exit(-1);
  }

  /* Inizializzo la marcatura di tutti i nodi a -1 ("non marcato"), per sicurezza */

  for (i = 0; i < n; i++) {
    (graph -> nodeList)[i].cComponent = -1;
  }

  queue = (int*) malloc(n * sizeof(int) + 1);

  /* Visita in ampiezza del grafo */
  for (i = 0; i < n; i++) {

    if ((graph -> nodeList)[i].cComponent == -1) { /* lavoro solo su nodi non ancora marcati */

      /* all'inizio di ogni giro, head == tail + 1 */
      tail++; /* head == tail */

      queue[head] = i; /* inserisco il nuovo nodo in coda */
      (graph -> nodeList)[i].cComponent = componentCount; /* e lo marco come visitato */

      do { /* ciclo tra i nodi in coda per aggiungerne (e per marcarne) gli adiacenti */

        tempNode = &((graph -> nodeList)[queue[head]]);
        tempList = &(tempNode -> adjacency);
        l = tempList -> active;

        for (j = 0; j < l; j++) {

          currentAdjacent = readList(tempList, j);

          if ((graph -> nodeList)[currentAdjacent].cComponent == -1) { /* controllo che il nodo non sia già marcato */
            tail++;
            queue[tail] = currentAdjacent; /* aggiungo in coda, pezzo per pezzo, la lista di adiacenza del nodo corrente */
            (graph -> nodeList)[currentAdjacent].cComponent = componentCount; /* marco il nodo appena aggiunto */
          }

        }

        head++; /* vado oltre il nodo appena registrato */

      } while (head <= tail); /* prendo in esame ogni nodo in coda finche' raggiungo la fine della componente connessa */

      componentCount++;
    }
  }

  /* Libero la coda e aggiorno lo stato del grafo */
  free(queue);
  graph -> componentCount = componentCount;
  graph -> componentsReady = TRUE;
  return;
}

void importGraph(Graph *graph, const char * fileName) {

  importNodes(graph, fileName);
  checkForEdges(graph);

  return;
}

void printGraph(Graph *graph, const char option) {
  /* options: 's' - silent; 'n' - normal */
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

  /* la prima parte del file conterra' le informazioni strutturali del grafo */
  fprintf(fileStream, "%d\n%d\n%d\n", graph -> nodeCount, graph -> edgeCount, graph -> componentCount);

  /* la seconda parte del file conterra' l'elenco dei nodi con le loro liste di adiacenza */
  for (i = 0; i < n; i++) {
    tempNode = &(graph -> nodeList)[i];
    l = getDegree(tempNode);
    fprintf(fileStream, "%s %d %d ", tempNode -> name, tempNode -> cComponent, l);
    for (j = 0; j < l; j++) {
      fprintf(fileStream, "%d ", readList(&(tempNode -> adjacency), j));
    }
    fprintf(fileStream, "\n");
  }

  fclose(fileStream);

  return;
}

void loadGraph(Graph *graph, const char *fileName) {
  FILE *fileStream;
  int i;
  int j;
  int n; /* nodeCount; */
  Node *tempNode; /* i-esimo nodo */
  int l; /* grado dell'i-esimo nodo */
  int adjacent;
  char tempString[MAX_STR_LEN];

  /* resetto il grafo (se era gia' vuoto ci mette comunque pochissimo tempo) */
  destrGraph(graph);
  constrGraph(graph);

  /* apro lo stream */
  fileStream = fopen(fileName, "r");

  /* controllo che il file esista */
  if (fileStream == NULL) {
    fprintf(stderr, "Errore [graph.c - loadGraph]: non esiste un file con questo nome (%s)", fileName);
    exit(-1);
  }

  /* registro i dati strutturali del grafo */
  fscanf(fileStream, "%d %d %d ", &n, &(graph -> edgeCount), &(graph -> componentCount)); /* nodeCount deve essere aggiornato da addNode; gli altri due non influiscono sul codice */

  /* Body */

  for (i = 0; i < n; i++) {
    /* crea l'i-esimo nodo */
    fscanf(fileStream, "%s", tempString);
    addNode(graph, tempString);
    tempNode = &((graph -> nodeList)[i]);
    fscanf(fileStream, "%d %d ", &(tempNode -> cComponent), &l);

    /* popola la sua lista di adiacenza */
    for (j = 0; j < l; j++) {
      fscanf(fileStream, "%d ", &adjacent);
      enqueueList(&(tempNode -> adjacency), adjacent);
    }

  }

  fclose(fileStream);

  /* Update state */
  graph -> nodesReady = TRUE;
  graph -> edgesReady = TRUE;
  return;
}

char *getWord(Graph *graph, unsigned int index) {
  return (graph -> nodeList)[index].name;
}
