#include <stdio.h>

#include "essentials.h"
#include "string.h"
#include "graph.h"
#include "sorting.h"

int main(int argc, char **argv) {

  Graph grafo;
  int i;
  int cc; /* componentCount */
  int n; /* nodeCount */
  int m; /* maxDegree */
  Info *infoGrafo; /* grafo.graphInfo */
  int *contGradi;
  int *compOrdinate;
  int *paroleOrdinate;
  int index;
  FILE *soluzione; /* stream di uscita */

  /* Apertura dello stream di uscita */
  if (argc < 3) {
    fprintf(stderr, "Errore [main.c]: e' necessario fornire il nome di un file sorgente e di un file di arrivo nella forma [./main.x esempio.txt esempioSoluzione.txt]\n");
    exit(-1);
  }
  soluzione = fopen(argv[2], "w");

  /* Costruzione del grafo */
  constrGraph(&grafo);

  importGraph(&grafo, argv[1]); /* popola il grafo da file */
  n = grafo.nodeCount;

  checkForComponents(&grafo); /* BFS per determinare le componenti connesse */
  cc = grafo.componentCount;

  addInfo(&grafo); /* aggiunge al grafo l'appendice graphInfo, finora NULL */
  getInfo(&grafo); /* compila graphInfo a partire dai dati già raccolti su nodi, lati e componenti connesse */
  infoGrafo = grafo.graphInfo;
  m = infoGrafo -> maxDegree;
  contGradi = infoGrafo -> degreesCount;

  /* ordina le componenti connesse e le parole come richiesto */
  quickSortComponents(&grafo, 0, cc-1);
  quickSortWords(&grafo, 0, n-1);
  compOrdinate = infoGrafo -> sortedComponents;
  paroleOrdinate = infoGrafo -> sortedNodes;

  /* Stampa della soluzione */
  fprintf(soluzione, "%d parole con %d legami\n", grafo.nodeCount, grafo.edgeCount);

  for (i = m; i >= 0; i--) {
    fprintf(soluzione, "%d parol%s di grado %d\n", contGradi[i], (contGradi[i] == 1? "a" : "e"), i);
  }

  fprintf(soluzione, "%d componenti\n", grafo.componentCount);
  for (i = 0; i < cc; i++) {
    index = compOrdinate[i];
    fprintf(soluzione, "Componente %d: %d parole da %s a %s (diametro %d)\n",
    i+1,
    (infoGrafo -> cardinalities)[index],
    (getWord(&grafo, (infoGrafo -> firstWord)[index])),
    (getWord(&grafo, (infoGrafo -> lastWord)[index])),
    (infoGrafo -> diameters)[index]);
  }

  for (i = 0; i < n; i++) {
    fprintf(soluzione, "%s\n", getWord(&grafo, paroleOrdinate[i]));
  }

  destrGraph(&grafo);

  fclose(soluzione);

  printf("\n");
  return 0;
}
