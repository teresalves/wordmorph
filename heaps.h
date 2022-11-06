#ifndef HEAPS_H
#define HEAPS_H
   
typedef struct queue_ queue;

void PQinsert(int v, queue *Q);
queue* PQinit(queue *Q, int size, int *wt);
void fixUp(queue *Q, int index);
int lessPri(int idx1, int idx2, queue *Q);
void exchange(int *a, int *b);
int IsEmpty(queue *Q);
int PQdelmax(queue *Q);
void PQinc(queue* Q, int v);
void fixDown(int index, queue *Q);
void freeQueue(queue *Q);
   
#endif
