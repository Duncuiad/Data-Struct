#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"

int main() {

  Graph grafo;

  Bool temp = areRelated("casa", "caste");

  if (temp==TRUE) {
    printf("Yes");
  }
  else {
    printf("No");
  }

  constrGraph(&grafo);

  importNodes(&grafo, "./files/English.txt");
  /* checkForEdges(&grafo); */

  printGraph(&grafo, 's');

  destrGraph(&grafo);

  return 0;
}
