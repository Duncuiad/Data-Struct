#include "info.h"

void addInfo(Graph *graph){

  /* Check */
  if (graph -> componentsReady == FALSE) {
    fprintf(stderr, "Errore [info.c - addInfo]: non posso aggiungere graphInfo prima di aver determinato le componenti connesse");
    exit(-1);
  }

  graph -> graphInfo = (Info*) malloc(sizeof(Info)); /* viene rimosso da removeInfo() */

  graph -> graphInfo -> degrees = (int*) malloc((graph -> nodeCount) * sizeof(int));
  graph -> graphInfo -> cardinalities = (int*) malloc((graph -> componentCount) * sizeof(int));
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

void getDegreeInfo(Graph *graph);
void getCardInfo(Graph *graph);
void getEccentrInfo(Graph *graph);
void getDiameterInfo(Graph *graph);
