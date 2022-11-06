#include <stdio.h>
#include <stdlib.h>
#include "heaps.h"


struct queue_{
    int free_;
    int qsize;
    int *heapPos;       /* Heap queue */
    int *graphPos;      /* Array to locate the word in the heap */
    int *weight;        /* Array with the weights */
};   

/**********************************************************************
Function: 
    PQinc
  
Description:
    check if vertex is in the heap and fixup
      
Arguments:
    Q : priority queue
    v: vertex

Return Value:
    --
**********************************************************************/      

void PQinc(queue *Q, int v)
{
    if(Q->graphPos[v] == -1) 
        exit(0);
 
    fixUp(Q,Q->graphPos[v]);
}
   

/**********************************************************************
Function: 
    PQinsert
  
Description:
    insert vertex in the heap
      
Arguments:
    Q : priority queue
    v: vertex

Return Value:
    --
**********************************************************************/      

void PQinsert(int v, queue *Q)
{
    if ((Q->free_) < Q->qsize)
    {
        Q->heapPos[Q->free_] = v; 
        Q->graphPos[v] = Q->free_;
        fixUp(Q, Q->graphPos[v]);
        Q->free_ +=1;
    }
}


/**********************************************************************
Function: 
    PQinit
  
Description:
    initialize queue
      
Arguments:
    Q : priority queue
    size
    wt[]: direct distance to word

Return Value:
    Q: initialized queue
**********************************************************************/     
   
queue *PQinit(queue *Q, int size, int *wt)
{
    int i = 0;
    Q = (queue *) malloc (sizeof(queue));
    Q->qsize = size;
    Q->heapPos = (int*) malloc (size * sizeof(queue));
    Q->graphPos = (int*) malloc (size *  sizeof(queue));
    for(i = 0; i < Q->qsize; i++){
        Q->heapPos[i] = -1;
        Q->graphPos[i] = -1;
    } 
    Q->free_ = 0;
    Q->weight = wt;
    return Q;
}
   

/**********************************************************************
Function: 
    fixUp
  
Description:
    switches the ertex with its parent is the heap condition is not true
      
Arguments:
    Q : priority queue
    index

Return Value:
    --
**********************************************************************/     
   
void fixUp(queue *Q, int index){
       
   
    while(index >=0 && lessPri(Q->heapPos[(index-1)/2], Q->heapPos[index], Q) && Q->heapPos[index] != -1)
    {
        exchange(&Q->heapPos[index], &Q->heapPos[(index - 1) / 2]);
        exchange(&Q->graphPos[Q->heapPos[index]],&Q->graphPos[Q->heapPos[(index-1)/2]]);
           
        index = (index - 1) / 2;     
    }
       
}
   

/**********************************************************************
Function: 
    lessPri
  
Description:
    heap condition
      
Arguments:
    Q: queue
    idx1
    idx2

Return Value:
    Condition: True or false
**********************************************************************/    
   

int lessPri(int idx1, int idx2, queue *Q){
    return Q->weight[idx1] > Q->weight[idx2]? 1 : 0 ;
}

   
/**********************************************************************
Function: 
    exchange
  
Description:
    exchange values given
      
Arguments:
    *a
    *b
    
Return Value:
    --
**********************************************************************/  

void exchange(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
   

/**********************************************************************
Function: 
    isEmpty
  
Description:
    checks if queue is empty
      
Arguments:
    free

Return Value:
    Condition: True or false
**********************************************************************/  
   
int IsEmpty(queue *Q) {
    return Q->free_ == 0 ? 1 : 0;
}
   
   
/**********************************************************************
Function: 
    PQdelmax
  
Description:
    deletes root of the heap
      
Arguments:
    Q: queue

Return Value:
    vertex 
**********************************************************************/  

int PQdelmax(queue *Q){
    int aux;
    if(!IsEmpty(Q)){
        aux = Q->heapPos[0];
        exchange(&Q->heapPos[0], &Q->heapPos[Q->free_-1]);
        exchange(&Q->graphPos[Q->heapPos[0]], &Q->graphPos[Q->heapPos[Q->free_-1]]);
        Q->graphPos[Q->heapPos[Q->free_-1]] = -1;
        Q->heapPos[Q->free_-1] = -1;
        Q->free_ -= 1;
        fixDown(0, Q);
        return aux;
    }
   
    return -1;
}
   

/**********************************************************************
Function: 
    fixDown
  
Description:
    changes vertex with its child if the heap condition is not true
      
Arguments:
    Q: queue
    index

Return Value:
    --
**********************************************************************/  

void fixDown(int index, queue *Q){
    int child = index* 2 +1;
    while(child < Q->free_){
        if(child < (Q->free_-1) && lessPri(Q->heapPos[child], Q->heapPos[child + 1], Q)){
            child++;
        }
        if(!lessPri(Q->heapPos[index], Q->heapPos[child], Q) && Q->heapPos[index] != -1)
            break;
        exchange(&Q->heapPos[child], &Q->heapPos[index]);
        exchange(&Q->graphPos[Q->heapPos[index]], &Q->graphPos[Q->heapPos[child]]);
        index = child;
        child = 2*index + 1;
    }
}
  
 
/**********************************************************************
Function: 
    freeQueue
  
Description:
    frees the priority queue
      
Arguments:
    Q: queue

Return Value:
    --
**********************************************************************/  

void freeQueue(queue *Q)
{
    free(Q->heapPos);
    free(Q->graphPos);
    free(Q);
}