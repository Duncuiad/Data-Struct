#ifndef SORTING_H
#define SORTING_H

#include "essentials.h"
#include "relations.h"
#include "graph.h"
#include "info.h"

int comesBefore(Graph *graph, unsigned int c1, unsigned int c2);
void quickSort(int *array, int lower, int upper);
void quickSortComponents(Graph *graph, int lower, int upper);
void quickSortWords(Graph *graph, int lower, int upper);

#endif
