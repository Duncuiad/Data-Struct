#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"

int main() {

  Graph grafo;
  int i;
  int cc;
  int n;

  constrGraph(&grafo);

  loadGraph(&grafo, "./files/Esempio.dat");

  n = grafo.nodeCount;

  checkForComponents(&grafo);

  cc = grafo.componentCount;

  printGraph(&grafo, 's');

  addInfo(&grafo);
  getDegreeInfo(&grafo);
  getCardInfo(&grafo);

  for (i = 0; i < n; i++) {
    printf("[%d]: grado %d\n", i, (grafo.graphInfo -> degrees)[i]);
  }

  for (i = 0; i < cc; i++) {
    printf("Componente n° %d: %d elementi\n", i, (grafo.graphInfo -> cardinalities)[i]);
  }

  destrGraph(&grafo);

  return 0;
}
