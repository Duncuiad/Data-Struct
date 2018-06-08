#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"

int main() {

  Graph grafo;

  constrGraph(&grafo);

  loadGraph(&grafo, "./files/English.dat");

  printGraph(&grafo, 's');

  destrGraph(&grafo);

  return 0;
}
