#ifndef INFO_H
#define INFO_H

#include "essentials.h"
#include "graph.h"

void addInfo(Graph *graph); /* ogni istanza di Info e' soggetta a un qualche grafo */
void removeInfo(Info *info); /* distruttore della struct Info che puo' essere costruita solo all'interno di un grafo da addInfo */
void getDegreeInfo(Graph *graph);
void getCardInfo(Graph *graph);
void getEccentrInfo(Graph *graph);
void getDiameterInfo(Graph *graph);

#endif
