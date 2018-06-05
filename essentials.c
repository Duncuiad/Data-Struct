#include "essentials.h"

/* STRUTTURE DATI */

struct _List {
  int allocated;
  int active;
  int *array;
}; /* a livello di implementazione si tratta di una tabella */

struct _Node {
  char name[MAX_STR_LEN]; /* parola rappresentata dal nodo */
  int cComponent; /* componente connessa a cui appartiene il nodo */
  List adjacency;
};

/* METODI LIST */

void constrList(List *list, int desiredLength) {
  int i = 0; /* counter */
  int base = 1; /* variabile di appoggio per una potenza di 2 */
  if (desiredLength < 0) {
    fprintf(stderr, "Errore: lista inizializzata con lunghezza negativa");
    exit(-1);
  }
  else if (desiredLength == 0) {
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

  /* controllo che la tabella non sia piena, e nel caso rialloco il doppio della memoria */
  if (list -> active == list -> allocated) {

    pointer = list -> array; /* tiene traccia del vettore vecchio */
    list -> array = (int*) malloc(2 * (list -> allocated) * sizeof(int));

    for (i = 0; i < list -> allocated; i++) {
      (list -> array)[i] = pointer[i]; /* copia puntualmente il vettore vecchio su quello nuovo */
    }

    list -> allocated = 2 * (list -> allocated); /* aggiorna la dimensione allocata */
    free(pointer); /* elimina il vettore vecchio */
  }

  /* aggiungo in coda <value> */
  (list -> array)[list -> active] = value;
  list -> active = (list -> active) + 1;
  return;
}


int readList(List *list, int index) {
  if (index < 0) {
    fprintf(stderr, "Errore: lettura lista con indice di posizione negativo");
    exit(-1);
  }
  if (index >= (list -> active)) {
    fprintf(stderr, "Errore: lettura lista con indice di posizione out of bounds");
    exit(-1);
  }
  return (list -> array)[index];
}

/* METODI NODE */
void constrNode(Node *node, char *chosenName) {
  strcpy(node -> name, chosenName);
  node -> cComponent = 0;
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
