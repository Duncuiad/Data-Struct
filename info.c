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

  graph -> graphInfo -> cardsReady = FALSE;

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

  /* Update state */
  graph -> graphInfo -> cardsReady = TRUE;

  return;
}

void getEccentrInfo(Graph *graph) {

  return;
}

void getDiameterInfo(Graph *graph) {

  return;
}

void getInfo(Graph *graph) {

  return;
}

int getEccentricity(Graph *graph, unsigned int index) {
  int i;
  int n; /* cardinalita' della componente connessa a cui appartiene il nodo di indice index */
  int component = graph -> nodeList)[i].cComponent;
  int *queue;
  int head = 0;
  int tail = -1;

  /* Check */
  if (graph -> graphInfo -> cardsReady == FALSE) {
    getCardInfo(graph); /* avere le cardinalita' delle c. connesse mi permette di allocare la coda della BFS con il numero esatto di elementi */
  }

  queue = (int*) malloc((graph -> graphInfo -> cardinalities)[component] * sizeof(int));

  /* all'inizio di ogni giro, head == tail + 1 */
  tail++; /* head == tail */
/* DA QUI IN POI E' DA AGGIORNARE */
  queue[head] = 0; /* inserisco il nuovo nodo in coda */
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

  return 0;
}
