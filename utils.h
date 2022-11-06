#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 30
#define MAX_WT 10000
 
typedef struct dic_ dic;  

#include "graph.h"
#include "files.h"

void argumentCount(int count, int nArguments); 
dic *initArray(dic *dicArray, int maxChanges[]);
void sortTables(dic *dicArray, int toCreate[]);
int compare (const void *a, const void *b);
int binarySearch(dic *dicArray, int size, char *word);
void freeEverything(dic *dicArray, char *fileName);
int * mallocIntArray(dic *dicArray, int index);
void mallocWords(dic *dicArray, int index);
int getNumberOfWords(dic *dicArray, int index);
int getMaxChanges(dic *dicArray, int index);
void * getWords(dic *dicArray, int index);
void incrementNumberOfWords(dic *dicArray, int index);
void mallocSingleWord(dic *dicArray, int index, int nextFreeSpot);
int isWordNull(dic *dicArray, int index, int nextFreeSpot);
char* getSingleWord(dic *dicArray, int index, int nextFreeSpot);

#endif
