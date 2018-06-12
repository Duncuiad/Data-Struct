#ifndef RELATIONS_H
#define RELATIONS_H

#include <string.h>
#include "essentials.h"

Bool areRelated(const char *firstWord, const char *secondWord);
int comesBefore(Graph *graph, unsigned int c1, unsigned int c2);

#endif
