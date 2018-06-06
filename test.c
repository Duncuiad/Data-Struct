#include <stdio.h>

#include "essentials.h"
#include "graph.h"

int main() {

  int i;
  List lista;
  Graph grafo;

  constrList(&lista, 0);
  constrGraph(&grafo);

  for (i = 0; i<10; i++) {
    enqueueList(&lista, 100-i);
  }

  addNode(&grafo, "Nodo");
  grafo.nodeList[0].adjacency = lista;

  printGraph(&grafo);

  destrGraph(&grafo);
  destrList(&lista);
  return 0;
}
