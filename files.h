#ifndef FILES_H
#define FILES_H

#include "utils.h"

FILE *openFile(FILE *fp, char *name, char *operation);
char *changeExtension(char *newName, char *fileName, char *newExt);
void checkExtension(char *fileName, char *correctExt);
void dictionariesToUse(FILE *fpPal, int toCreate[], int maxChanges[]);
void wordsInDictionary(FILE *fpDic, dic *dicArray, int toCreate[]);
void fillTables(dic *dicArray, FILE *fpDic, int toCreate[], int toCreateFree[]);
void printPath(FILE *fpPath, char **words, int st[], int aux, int index, int weight);
void printPathRecur(FILE *fpPath, char **words, int st[], int aux, int index, int weight);
void closeFiles(FILE *fpDic, FILE *fpPal, FILE *fpPath);


#endif