#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
 
 struct dic_{
    int nWords;
    int maxChanges;
    char **words;
};

/**********************************************************************
Function: 
    initArray
  
Description:
    Initializes values of the word's table
      
Arguments:
    dicArray: Array with the word tables
  
  
Return Value:
    dicArray
  
**********************************************************************/
 
dic *initArray(dic *dicArray, int maxChanges[])
{
    int i = 0;
 
    dicArray = (dic *)malloc(MAX_WORD_SIZE * sizeof(dic));
    if(dicArray == NULL)
        exit(0);

    for(i = 0; i < MAX_WORD_SIZE; i++)
    {
        dicArray[i].words = NULL;
        dicArray[i].nWords = 0;
        dicArray[i].maxChanges = maxChanges[i];
    }
 
    return dicArray;
}
    
/**********************************************************************
Function: 
    freeEverything
  
Description:
    frees all the word tables
      
Arguments:
    dicArray: Array with the word tables
  
  
Return Value:
    --
  
**********************************************************************/
 
void freeEverything(dic* dicArray, char *fileName)
{
    int i = 0;
    int j = 0;
    
    for(i = 0; i < MAX_WORD_SIZE; i++)
    {
        if(dicArray[i].words != NULL)
        {
            for(j = 0; j < dicArray[i].nWords; j++)
                free(dicArray[i].words[j]);
 
            free(dicArray[i].words);
        }
    }
 
    free(fileName);
    free(dicArray);
}
 
 
 /**********************************************************************
Function: 
    compare
  
Description:
    compares two words (used in qsort)
      
Arguments:
    a: first word
    b: second word
  
Return Value:
    Returns 1, 0 or -1, depending on the relative position of the word
***********************************************************************/
 
int compare (const void * a, const void * b)
{
    char* word1 = *(char**) a;
    char* word2 = *(char**) b;
    return ( strcmp(word1, word2));
}


   
 
/**********************************************************************
Function: 
    binarySearch
  
Description:
    Searches the index of a word in a table
      
Arguments:
    dicArray: Array with the word tables
    size: size of word to find
    word: word to find index for
  
Return Value:
    Returns the index found
**********************************************************************/
 
int binarySearch(dic *dicArray, int size, char* word)
{
    int first = 0;
    int middle = 0;
    int last = 0;
 
    last = dicArray[size].nWords - 1;
   
    while(first <= last)
    {
        middle = (first + last) / 2;
        if(strcmp(dicArray[size].words[middle], word) == 0)
            return middle;
 
        else if(strcmp(dicArray[size].words[middle], word) > 0)
            last = middle - 1;
 
        else if(strcmp(dicArray[size].words[middle], word) < 0)
            first = middle + 1;
    }
 
    return -1;
   
}

 
/**********************************************************************
Function: 
    argumentCount
  
Description:
    Verifies if there are enough arguments
      
Arguments:
    count: argument count
    nArguments: number of expected arguments
  
Return Value:
    --
**********************************************************************/
 
void argumentCount(int count, int nArguments)
{
    if(count < nArguments)
        exit(0);
}


/**********************************************************************
Function: 
    sortTables
  
Description:
    Uses qsort to arrange the tables
      
Arguments:
   dicArray: dictionary array of words
    toCreate: represents the dictionaries to be used in the program

Return Value:
    --
**********************************************************************/

void sortTables(dic *dicArray, int toCreate[])
{
    int i = 0;
 
    for(i = 1; i < MAX_WORD_SIZE; i++)
        if(toCreate[i] == 1)
            qsort((char**)dicArray[i].words, (size_t)(dicArray[i].nWords), sizeof(char*), compare);
}


int * mallocIntArray(dic *dicArray, int index)
{
    return (int*)malloc(dicArray[index].nWords * sizeof(int));
}

void mallocWords(dic *dicArray, int index)
{
    dicArray[index].words = (char**)malloc(dicArray[index].nWords * sizeof(char*));
}

void mallocSingleWord(dic *dicArray, int index, int nextFreeSpot)
{
    dicArray[index].words[nextFreeSpot] = (char *)malloc((index + 1) * sizeof(char));
}
int getNumberOfWords(dic *dicArray, int index)
{
    return dicArray[index].nWords;
}

int getMaxChanges(dic *dicArray, int index)
{
    return dicArray[index].maxChanges;
}

void * getWords(dic *dicArray, int index)
{
    return dicArray[index].words;
};

char* getSingleWord(dic *dicArray, int index, int nextFreeSpot)
{
    return dicArray[index].words[nextFreeSpot];
} 

void incrementNumberOfWords(dic *dicArray, int index)
{
    dicArray[index].nWords++;
}
int isWordNull(dic *dicArray, int index, int nextFreeSpot)
{
   return dicArray[index].words[nextFreeSpot] == NULL;
}