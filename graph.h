#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"
#include "heaps.h"
      
typedef struct link_ link;
typedef struct graph_ graph; 

graph *createGraph(graph *G, int nWords);
void updateGraph(graph *G, char **words, int nSwitches, int index, int nWords);
int checkAdjacent(char *word1, char *word2, int nSwitches);
void initLink(graph *G, int index, int v, int w);
void solveProblems(dic *dicArray, FILE *fpPal, FILE *fpPath);
void GRAPHpfs(graph *G, int s, int end, int size, int st[], int wt[], int changes, int maxChanges, char **words);
void freeGraph(graph *G, int nWords);
void freeGraphs(graph *graphArray[MAX_WORD_SIZE]);
  
#endif
