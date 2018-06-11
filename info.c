#include "info.h"

void addInfo(Graph *graph){

  /* Check */
  if (graph -> componentsReady == FALSE) {
    fprintf(stderr, "Errore [info.c - addInfo]: non posso aggiungere graphInfo prima di aver determinato le componenti connesse");
    exit(-1);
  }

  graph -> graphInfo = (Info*) malloc(sizeof(Info)); /* viene rimosso da removeInfo() */

  graph -> graphInfo -> degrees = (int*) malloc((graph -> nodeCount) * sizeof(int));
  graph -> graphInfo -> cardinalities = (int*) calloc(graph -> componentCount, sizeof(int)); /* azzero tutti i valori perche' aggiorno la cardinalita' con ++ */
  graph -> graphInfo -> eccentricities = (int*) malloc((graph -> nodeCount) * sizeof(int));
  graph -> graphInfo -> diameters = (int*) calloc(graph -> componentCount, sizeof(int)); /* azzero perche' gli elementi di diameters sono massimi di altri vettori, che aggiorno a ogni iterazione se maggiori del valore precedentemente memorizzato */

  graph -> graphInfo -> cardsReady = FALSE;
  graph -> graphInfo -> eccReady = FALSE;

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
  int i;
  int n = graph -> nodeCount;
  int *eccentr;

  /* Check */
  if (graph -> graphInfo == NULL) {
    fprintf(stderr, "\nErrore [info.c - getEccentrInfo]: non ho ancora aggiunto l'appendice graphInfo al grafo. Chiamare la funzione addInfo\n");
    exit(-1);
  }
  eccentr = graph -> graphInfo -> eccentricities;

  /* Body */
  for (i = 0; i < n; i++, eccentr++) {
    *eccentr = getEccentricity(graph, i);
  }

  /* Update state */
  graph -> graphInfo -> eccReady = TRUE;

  return;
}

void getDiameterInfo(Graph *graph) {
  int i;
  int n = graph -> nodeCount;
  int *eccentr;
  int *diams;
  int c; /* componente connessa */
  int cc; /* numero di componente connessa */

  /* Check */
  if (graph -> graphInfo == NULL) {
    fprintf(stderr, "\nErrore [info.c - getDiameterInfo]: non ho ancora aggiunto l'appendice graphInfo al grafo. Chiamare la funzione addInfo\n");
    exit(-1);
  }

  if (graph -> graphInfo -> eccReady == FALSE) {
    getEccentrInfo(graph); /* per determinare i diametri ho bisogno di conoscere l'eccentricita' di ogni nodo */
  }

  eccentr = graph -> graphInfo -> eccentricities;
  diams = graph -> graphInfo -> diameters;

  /* Body */
  for (i = 0; i < n; i++) {
    c = (graph -> nodeList)[i].cComponent;
    if (diams[c] < eccentr[i]) {
      diams[c] = eccentr[i];
    }

  }

  return;
}

void getInfo(Graph *graph) {

  return;
}

int getEccentricity(Graph *graph, unsigned int index) {

  int component = (graph -> nodeList)[index].cComponent; /* usero' l'elemento cComponent di ogni nodo anche come marker, per poi resettarlo al valore iniziale alla fine della procedura */
  int cardinality;

  /* Per scorrere la coda (l'algoritmo e' una BFS) */
  /* Osservazione: la coda induce un ordine totale sugli elementi della stessa componente connessa */
  /* Sfruttero' questo fatto anche usando il vettore queue come dizionario tra gli elementi (ordinati dalla visita) della componente e il loro indice nel grafo totale */
  int *queue;
  int head = 0;
  int tail = 0;

  /* Per scorrere la lista di adiacenza del nodo corrente in coda */
  Node *tempNode;
  List *tempList;
  int j;
  int l;
  int currentAdjacent;

  /* Risultato */
  int depth;

  /* Check */
  if (graph -> graphInfo -> cardsReady == FALSE) {
    getCardInfo(graph); /* avere le cardinalita' delle c. connesse mi permette di allocare la coda della BFS con il numero esatto di elementi */
  }

  cardinality = (graph -> graphInfo -> cardinalities)[component];
  queue = (int*) malloc(cardinality * sizeof(int));

  queue[0] = index; /* inserisco il nodo sorgente in coda */
  (graph -> nodeList)[index].cComponent = -1; /* marco la sorgente */

  /* visita in ampiezza con l'elemento cComponent di ogni nodo come marcatore */
  /* questa scelta di marcatore mi permette di non dover allocare anche per c. c. molto piccole un vettore di marcatori della stessa cardinalita' dell'intero grafo */
  for (head = 0; head < cardinality; head++) { /* ciclo tra i nodi in coda per aggiungerne (e per marcarne) gli adiacenti */

    tempNode = &((graph -> nodeList)[queue[head]]);
    tempList = &(tempNode -> adjacency);
    l = tempList -> active; /* lunghezza della lista di adiacenza del nodo corrente */

    for (j = 0; j < l; j++) {

      currentAdjacent = readList(tempList, j);

      if ((graph -> nodeList)[currentAdjacent].cComponent >= 0) { /* convenzione: tutte le componenti connesse hanno indice >= 0, quindi utilizzo indici negativi per marcare i livelli di profondita' */
        tail++;
        queue[tail] = currentAdjacent; /* aggiungo in coda, pezzo per pezzo, la lista di adiacenza del nodo corrente */
        (graph -> nodeList)[currentAdjacent].cComponent = (tempNode -> cComponent) - 1;
        /* marco il nodo appena aggiunto con un livello in piu' rispetto al nodo da cui e' stato raggiunto */
      }

    }

  }

/* Debug: puo' essere comodo per vedere in azione la scelta della marcatura (su componenti connesse piccole!) */
/*
for (j = 0; j < cardinality; j++) {
  fprintf(stderr, "[posizione in coda: %d] nodo: %d, marker: %d\n", j, queue[j], (graph -> nodeList)[queue[j]].cComponent);
}
*/

  depth = -1 - (graph -> nodeList)[queue[cardinality - 1]].cComponent; /* con la convenzione sulla notazione dei marcatori, il livello massimo di profondita' rispetto al primo nodo e' -1 - d, dove d e' il marcatore dell'ultimo nodo in coda */

  for (j = 0; j < cardinality; j++) {
    (graph -> nodeList)[queue[j]].cComponent = component; /* resetto la componente connessa di ogni nodo a come era in entrata */
  }

  free(queue);

  return depth;
}
