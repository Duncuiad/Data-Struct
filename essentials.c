#include "essentials.h"

struct _List {
  int allocated;
  int active;
  int * array;
}; /* a livello di implementazione si tratta di una tabella */

struct _Node {
  char name[MAX_STR_LEN]; /* parola rappresentata dal nodo */
  int cComponent; /* componente connessa a cui appartiene il nodo */
  List adjacency;
};
