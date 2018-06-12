#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"
#include "sorting.h"

int main() {

  Graph grafo;
  int i;
  int cc;
  int n;
  int eccentricity;
  int *sorted;
  int *sortedNames;

  constrGraph(&grafo);

  importGraph(&grafo, "./files/Canto1.txt");

  n = grafo.nodeCount;

  checkForComponents(&grafo);

  cc = grafo.componentCount;

  printGraph(&grafo, 's');

  addInfo(&grafo);
  getInfo(&grafo);

  quickSortComponents(&grafo, 0, cc-1);
  quickSortWords(&grafo, 0, n-1);
fprintf(stderr, "Tutto ok\n");

  sorted = grafo.graphInfo -> sortedComponents;
  sortedNames = grafo.graphInfo -> sortedNodes;
/*
  for (i = 0; i < cc; i++) {
    printf("Comp. n° %d: [card %d] [diam %d] [first %s] [last %s]\n", i,
    (grafo.graphInfo -> cardinalities)[sorted[i]],
    (grafo.graphInfo -> diameters)[sorted[i]],
    (getWord(&grafo, (grafo.graphInfo -> firstWord)[sorted[i]])),
    (getWord(&grafo, (grafo.graphInfo -> lastWord)[sorted[i]])));
  }
*/

  for (i = 0; i < n; i++) {
    printf("%s\n", getWord(&grafo, sortedNames[i]));
  }

  destrGraph(&grafo);

  return 0;
}
