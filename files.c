
#include "files.h"
 

/**********************************************************************
Function: 
    openFile
  
Description:
    opens a single file for a determined operation
      
Arguments:
    fp: file pointer
    *name: name of the file
    operation: what to do with the file (read, write, ...)
  
Return Value:
    fp: file pointer
**********************************************************************/  

FILE *openFile(FILE *fp, char *name, char *operation)
{
    fp = fopen(name, operation);
    if(fp == NULL)
        exit(0);
 
    return fp;
}


/**********************************************************************
Function: 
    changeExtension
  
Description:
    replace old extension by a new one
      
Arguments:
    *newName: soon to be name of the file
    *fileName: actual name of the file
    *newExt: soon to be the extension of the file
  
Return Value:
    newName: new name of the file
**********************************************************************/  

char *changeExtension(char *newName, char *fileName, char *newExt)
{
    char *fileExt = {'\0'};
    int length = 0;
 
    fileExt = strrchr(fileName, '.');
    length = strlen(fileName) - strlen(fileExt);
     
    newName = (char *)malloc((length + strlen(newExt) + 1) * sizeof(char));
    if(newName == NULL)
        exit(0);
 
    strcpy(newName, fileName);
    strcpy(newName + length, newExt);
    return newName;
}
 

/**********************************************************************
Function: 
    checkExtension
  
Description:
    check if extension is the expected one
      
Arguments:
    *fileName: name of the file
    *correctExt: expected extension of the file
  
Return Value:
    --
**********************************************************************/   

void checkExtension(char *fileName, char *correctExt)
{
    char *fileExt = {'\0'};
 
    fileExt = strrchr(fileName, '.');
    if(fileExt == '\0')
        exit(0);
 
    if(strcmp(fileExt, correctExt) != 0)
        exit(0);
}


/**********************************************************************
Function: 
    dictionariesToUse
  
Description:
    keeps memory of which size of dictionaries to create
      
Arguments:
    fpPal: problems file
    toCreate[]: represents the dictionaries to be created
    maxChanges: max number of chars to change in one mutation
  
Return Value:
    --
**********************************************************************/  

void dictionariesToUse(FILE *fpPal, int toCreate[], int maxChanges[])
{
    char word1[MAX_WORD_SIZE] = {'\0'};
    char word2[MAX_WORD_SIZE] = {'\0'};
    int changes = 0;
    int length = 0;
    int aux = 0;
 
    while(fscanf(fpPal, "%s %s %d", word1, word2, &changes) == 3)
    {
        length = strlen(word1);
        toCreate[length] = 1;
        if((aux = checkAdjacent(word1,word2, changes)) != -1){
            if(aux > maxChanges[length])
                maxChanges[length] = aux; 
        }
        else if(changes > maxChanges[length])
            maxChanges[length] = changes;
    }
    rewind(fpPal);
}

/**********************************************************************
Function: 
    wordsInDictionary
  
Description:
    count the number of words in each dictionary and alloc memory for them
      
Arguments:
    *newName: soon to be name of the file
    *fileName: actual name of the file
    *newExt: soon to be the extension of the file
  
Return Value:
    newName: new name of the file 
**********************************************************************/  

void wordsInDictionary(FILE *fpDic, dic *dicArray, int toCreate[])
{
    char word1[MAX_WORD_SIZE] = {'\0'};
    int length = 0;
    int i = 0;
 
    while(fscanf(fpDic, "%s ", word1) == 1)
    {   
        length = strlen(word1);
        incrementNumberOfWords(dicArray, length);
    }
 
    for( i = 0; i < MAX_WORD_SIZE; i++)
    {
        if(toCreate[i]==1)
            mallocWords(dicArray,i);
    }
     
    rewind(fpDic);
}


/**********************************************************************
Function: 
    fillTables
  
Description:
    fill the dictionary tables with the words
      
Arguments:
    dicArray: dictionary array of words
    fpDic: dictionary file
    toCreate[]: represents the dictionaries to be created
    toCreateFree[]: number of free spaces in each dictionary to fill
  
Return Value:
   --
**********************************************************************/  

void fillTables(dic *dicArray, FILE *fpDic, int toCreate[], int toCreateFree[])
{
    char word[MAX_WORD_SIZE] = {'\0'};
    int length = 0;
    int nextFreeSpot = 0;
 
    while(fscanf(fpDic, "%s ", word) ==1 )
    {
        length = strlen(word);  
        if(toCreate[length] == 1){
            nextFreeSpot = toCreateFree[length];
            mallocSingleWord(dicArray, length, nextFreeSpot);
            if(isWordNull(dicArray,length, nextFreeSpot))
                exit(0);
 
            strcpy(getSingleWord(dicArray, length, nextFreeSpot), word);
            toCreateFree[length]++;
        }
    }
}

/**********************************************************************
Function: 
    printPath
  
Description:
    Prints the solved problem onto the output file
      
Arguments:
    fpPath: output file
    **words: array of words
    st[]: previous node in the path 
    start
    end
    weight

Return Value:
    --
**********************************************************************/

void printPath(FILE *fpPath, char **words, int st[], int start, int end, int weight)
{
    if(weight == MAX_WT )
    {
        fprintf(fpPath, "%s -1\n%s\n\n", words[start], words[end]);
        return;
    }
    if(weight == 0){
        fprintf(fpPath, "%s 0\n%s\n\n", words[start], words[end]);
        return;
    }
 
    printPathRecur(fpPath, words, st, end, start, weight);
    fprintf(fpPath, "\n");
 
    return;
}
 
/**********************************************************************
Function: 
    printPathRecur
  
Description:
    Recursive function to print
      
Arguments:
    fpPath: output file
    **words: array of words
    st[]: previous node in the path 
    start
    end
    weight

Return Value:
    --
**********************************************************************/

void printPathRecur(FILE *fpPath, char **words, int st[], int end, int start, int weight)
{
    if(end != start)
        printPathRecur(fpPath, words, st, st[end], start, weight);
 
    fprintf(fpPath,"%s", words[end]);
    if(end == start)
        fprintf(fpPath," %d",weight );
 
    fprintf(fpPath,"\n");
    return;
}


/**********************************************************************
Function: 
    closeFiles
  
Description:
    closes all the files opened/created
      
Arguments:
    fpDic: dictionary file
    fpPath: output file
    fpPal: problem file

Return Value:
    --
**********************************************************************/

void closeFiles(FILE *fpDic, FILE *fpPal, FILE *fpPath)
{
    fclose(fpDic);
    fclose(fpPal); 
    fclose(fpPath);
    return;
}
