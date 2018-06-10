#include "essentials.h"

/* METODI LIST */

void constrList(List *list, unsigned int desiredLength) {
  int i = 0; /* counter */
  int base = 1; /* variabile di appoggio per una potenza di 2 */

  if (desiredLength == 0) {
    list -> allocated = 0;
    list -> active = 0;
    list -> array = NULL;
  }
  else {
    while (desiredLength > base) {
      base = base * 2;
    }
    list -> allocated = base;
    list -> active = 0;
    list -> array = (int*) malloc(base*sizeof(int));
  }
  return;
}


void destrList(List *list) {
  free(list -> array);
  return;
}


void enqueueList(List *list, int value) {
  int *pointer; /* di appoggio */
  int i; /* counter */
  int n = list -> allocated;

  /* controllo che la tabella non sia piena, e nel caso rialloco il doppio della memoria */
  if (list -> active == n) {

    pointer = list -> array; /* tiene traccia del vettore vecchio */
    list -> array = (int*) malloc((n == 0 ? 1 : 2 * n) * sizeof(int));

    for (i = 0; i < n; i++) {
      (list -> array)[i] = pointer[i]; /* copia puntualmente il vettore vecchio su quello nuovo */
    }

    list -> allocated = (n == 0 ? 1 : 2 * n); /* aggiorna la dimensione allocata */
    free(pointer); /* elimina il vettore vecchio */
  }

  /* aggiungo in coda <value> */
  (list -> array)[list -> active] = value;
  list -> active = (list -> active) + 1;
  return;
}


int readList(List *list, unsigned int index) {
  if (index >= (list -> active)) {
    fprintf(stderr, "Errore: lettura lista con indice di posizione troppo grande");
    exit(-1);
  }
  return (list -> array)[index];
}

void printList(List *list) {
  int i;
  for (i = 0; i < list -> active; i++) {
    printf("[%d]: %d\n", i, readList(list, i));
  }
}

void lightPrintList(List *list) {
  int i;
  int n = list -> active;
  for (i = 0; i < n; i++) {
    printf("%d", readList(list, i));
    if (i != n-1) {
      printf(", ");
    }
    else {
      printf("\n");
    }
  }
}

/* METODI NODE */
void constrNode(Node *node, char *chosenName) {
  strcpy(node -> name, chosenName);
  node -> cComponent = -1;
  constrList(&(node -> adjacency), 0);
  return;
}


void destrNode(Node *node) {
  destrList(&(node -> adjacency));
  return;
}

int getDegree(Node *node) {
  return (node -> adjacency).active;
}

void printNode(Node *node) {
  printf("%s, comp. conn.: %d, adiac.: ", node -> name, node -> cComponent);
  lightPrintList(&node -> adjacency);
  return;
}

/* FUNZIONI VARIE */
