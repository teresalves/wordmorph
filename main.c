#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "utils.h"

 
int main(int argc, char *argv[]){    
    /* Definition of Variables */   
    char *newName = {'\0'};
    int nArguments = 3;
    int toCreate[MAX_WORD_SIZE] = {0};
    int toCreateFree[MAX_WORD_SIZE] = {0};
    int maxChanges[MAX_WORD_SIZE] = {0};
    FILE *fpPal = NULL;
    FILE *fpDic = NULL;
    FILE *fpPath = NULL;
    dic *dicArray = NULL;

    /* Main Functions */
    argumentCount(argc, nArguments);
    checkExtension(argv[1], ".dic");
    checkExtension(argv[2], ".pal");
    fpDic = openFile(fpDic, argv[1], "r");
    fpPal = openFile(fpPal, argv[2], "r");
 
    newName = changeExtension(newName, argv[2], ".path");
    fpPath = openFile(fpPath, newName, "w");
     
    dictionariesToUse(fpPal, toCreate, maxChanges);
    dicArray = initArray(dicArray, maxChanges);
    wordsInDictionary(fpDic, dicArray, toCreate);
 
    fillTables(dicArray, fpDic, toCreate, toCreateFree);
    sortTables(dicArray, toCreate);
 
    solveProblems(dicArray, fpPal, fpPath);
     
    closeFiles(fpDic, fpPal, fpPath);  
    freeEverything(dicArray, newName);
    return(0);
}