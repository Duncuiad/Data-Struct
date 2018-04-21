#ifndef LIST_INT_H
#define LIST_INT_H

#define TYPE int

#include <stdio.h>

typedef struct _Link_TYPE {
  struct _Link_TYPE *predecessor;
  TYPE data;
  struct _Link_TYPE *successor;
} Link_TYPE;

typedef struct _List_TYPE {
  Link_TYPE *head;
  Link_TYPE *tail;
} List_TYPE;

List_TYPE initList();

#endif
