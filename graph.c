#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
 
 struct link_{
    int vertex; 
    int weight;
    struct link_ *next;
};
  
struct graph_{
    int V; 
    int E; 
    struct link_ **adj;
};

/**********************************************************************
Function: 
    createGraph
  
Description:
    creates a graph, initializes it
      
Arguments:
    G: graph of words
    nWords: number of words in the dictionary
  
Return Value:
    G: graph created
**********************************************************************/

graph* createGraph(graph *G, int nWords)
{
    int i = 0;
     
    G = (graph*)malloc(sizeof(graph));
    if(G == NULL)
        exit(0);
 
    G->adj = (link**) malloc (nWords * sizeof(link*));
    if(G->adj == NULL)
        exit(0);
 
    for(i = 0; i < nWords; i++)
        G->adj[i] = NULL;
 
    G->V = nWords;
    G->E = 0;
    return G;
}
   

/**********************************************************************
Function: 
    updateGraph
  
Description:
    updates the graph creating links for adjacent words
      
Arguments:
    G: graph of words
    **words: array with words in dictionary
    nSwitches: max number of character changes
    nWords: number of words in the dictionary
  
Return Value:
    --
**********************************************************************/  

void updateGraph(graph *G, char **words, int nSwitches, int index, int nWords)
{
    int v = 0;
    int dist = 0;
 
    for(v = 0; v < nWords; v++){
        dist = checkAdjacent(words[index], words[v], nSwitches);
        if(dist > 0 && dist <= nSwitches)
            initLink(G, index, v, dist * dist);
    }
}
 

/**********************************************************************
Function: 
    initLink
  
Description:
    initializes a link, a node for the adjacency list
      
Arguments:
    G: graph of words
    index: position of the initial word in the array
    v: vertex
    w: weight
  
Return Value:
    --
**********************************************************************/  

void initLink(graph *G, int index, int v, int w)
{
    link *newNode = NULL;
 
    newNode = (link*) malloc (sizeof(link));
    if(newNode == NULL)
        exit(0);
 
    newNode->vertex = v;
    newNode->weight = w;
 
    newNode->next = G->adj[index];
    G->adj[index] = newNode;
}
 

/**********************************************************************
Function: 
    checkAdjacent
  
Description:
    checks how many different chars both words have 
      
Arguments:
    word1
    word2
   changes: max number of character changes
  
Return Value:
    n: number of different chars
**********************************************************************/  

int checkAdjacent(char *word1, char *word2, int changes)
{
    int i = 0;
    int n = 0;
   
    for(i = 0; word1[i] != '\0'; i++)
    {
        if(word1[i] != word2[i])
            n++;
        if(n > changes)
            return -1;
    }
   
    return n;
}

/**********************************************************************
Function: 
    solveProblems
  
Description:
    Takes a problem written in the file and solves it
      
Arguments:
   dicArray: dictionary array of words
    fpPal: problem file
    fpPath: output file
  
Return Value:
    --
**********************************************************************/

void solveProblems(dic *dicArray, FILE *fpPal, FILE *fpPath)
{
    char word1[MAX_WORD_SIZE] = {'\0'};
    char word2[MAX_WORD_SIZE] = {'\0'};
 
    int changes = 0;
    int *st = {0};
    int *wt = {0};
    int start = 0;
    int end = 0;
    int length = 0;
    int i;

    graph **graphArray = NULL;

    graphArray = (graph**) malloc (MAX_WORD_SIZE * sizeof(graph*));
    for(i = 0; i < MAX_WORD_SIZE; i++){
        graphArray[i] = NULL;
    }
 
    while(fscanf(fpPal, "%s %s %d", word1, word2, &changes) == 3)
    {
        length = strlen(word1);
        wt = mallocIntArray(dicArray, length);
        st = mallocIntArray(dicArray, length);
        
        if(graphArray[length] == NULL) 
            graphArray[length] = createGraph(graphArray[length], getNumberOfWords(dicArray, length));
        
        start = binarySearch(dicArray, length, word1);
        end = binarySearch(dicArray, length, word2);
        
        
        GRAPHpfs(graphArray[length], start, end, getNumberOfWords(dicArray, length), st, wt, changes, getMaxChanges(dicArray,length), getWords(dicArray,length));
        printPath(fpPath, getWords(dicArray,length), st, start, end, wt[end]);
         
        free(wt);
        free(st);
    }
    freeGraphs(graphArray);
}
 
   
/**********************************************************************
Function: 
    GRAPHpfs
  
Description:
    Executes Djikstra's algorithm to find the shortest path tree
      
Arguments:
    G = graph of words
    s: start
    end
    size
    st[]: previous node in the path 
    wt[]: direct distance to word
    changes
    maxChanges: max number of chars to change
    **words: array of words

Return Value:
    --
**********************************************************************/   
 
void GRAPHpfs(graph *G, int s, int end, int size, int st[], int wt[], int changes, int maxChanges, char **words)
{ 
    int v = 0;
    int w = 0; 

    link *l = NULL;
    queue *Q = NULL;
 
    Q = PQinit(Q, size, wt);
 
    for (v = 0; v < G->V; v++){
        st[v] = -1;
        wt[v] = MAX_WT;
        PQinsert(v, Q);
    }
 
    wt[s] = 0;
    PQinc(Q, s);   

    while (!IsEmpty(Q))
        if(wt[v = PQdelmax(Q)] != MAX_WT)
        {
            if(G->adj[v] == NULL)
                updateGraph(G, words, maxChanges, v, size);
            for (l = G->adj[v]; l != NULL; l = l->next)
            {
                w = l->vertex;
                if(l->weight > changes * changes)
                    continue;
                if (wt[w] > (wt[v] + l->weight))
                {
                    wt[w] = (wt[v] + l->weight);
                    PQinc(Q, w);                     
                    st[w] = v;
                }
            }
 
            if(v == end)
            {
                freeQueue(Q);
                return ;
            }
        }
 
    freeQueue(Q);
    return ;          
} 


/**********************************************************************
Function: 
    freeGraph
  
Description:
    frees a single graph
      
Arguments:
    G: graph of words
    nWords: number of words in the dictionary
  
Return Value:
    --
**********************************************************************/  
 
void freeGraph(graph *G, int nWords)
{
    int i = 0;
    link *aux = NULL;
    link *next = NULL;
    for(i = 0; i < nWords; i++)
    {
        for(aux = G->adj[i]; aux != NULL; aux = next)
        {
            next = aux->next;
            free(aux);
        }
    }    
    free(G->adj);
    free(G);
}


/**********************************************************************
Function: 
    freesGraphs
  
Description:
    frees all graphs created
      
Arguments:
    graphArray[]: graph of words
  
Return Value:
    --
**********************************************************************/  

void freeGraphs(graph *graphArray[MAX_WORD_SIZE]){
    int i = 0;
    for(i = 0; i < MAX_WORD_SIZE; i++){
        if(graphArray[i] != NULL)
            freeGraph(graphArray[i], graphArray[i]->V);
    }
    free(graphArray);
}