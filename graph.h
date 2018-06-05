#ifndef GRAPH_H
#define GRAPH_H

#include  <stdio.h>

#include "essentials.h"

typedef struct _Graph Graph;

void adjoin(Graph *graph, int firstNode, int secondNode);

#endif
