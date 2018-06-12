#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"

int main() {

  Graph grafo;
  int i;
  int cc;
  int n;
  int eccentricity;

  constrGraph(&grafo);

  importGraph(&grafo, "./files/Canto1.txt");

  n = grafo.nodeCount;

  checkForComponents(&grafo);

  cc = grafo.componentCount;

  printGraph(&grafo, 'n');

  addInfo(&grafo);
  getDegreeInfo(&grafo);
  getDiameterInfo(&grafo);

  for (i = 0; i < cc; i++) {
    printf("Componente n° %d: %d elementi con diametro %d\n", i, (grafo.graphInfo -> cardinalities)[i], (grafo.graphInfo -> diameters)[i]);
  }

  destrGraph(&grafo);

  return 0;
}
