#ifndef LIST_INT_H
#define LIST_INT_H

#define TYPE int

#include <stdio.h>

typedef struct Link_TYPE {
  Link_TYPE *predecessor; /* BROKEN */
  TYPE data;
  Link_TYPE *successor;
} Link_TYPE;

typedef struct List_TYPE {
  Link_TYPE *head;
  Link_TYPE *tail;
} List_TYPE;

List_TYPE initList();

#endif
