#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

//Defined constant and macros
#define START 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

typedef struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare) ();
}PQ;

//Function creates and initializes queue
//O(1)
PQ *createQueue(int (*compare)())
{
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = START;
    pq->compare = compare;
    assert(compare != NULL);
    pq->data = malloc(sizeof(void*)*(pq->length));
    return pq;
}

//Function destroys queue by freeing from memory
//O(1)
void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

//Function returns the number of nodes
//Big-O: O(1)
int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return pq->count;
}

//Function adds a node to the priority queue and reallocates memory to 2x size if full to limit expensive reallocation
//O(log n)
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);
    if(pq->length == pq->count)
    {
        pq->length *= 2;
        pq->data = realloc(pq->data, sizeof(void *)*pq->length*2);
    }
    pq->data[pq->count] = entry;
    int location = pq->count;
    while(pq->compare(pq->data[location], pq->data[p(location)]) < 0)
    {
        void *temp = pq->data[p(location)];
        pq->data[p(location)] = pq->data[location];
        pq->data[location] = temp;
        location = p(location);
    }
    pq->count++;
}

//Function returns the deleted element and reorganizes queue as neccessary
//O(log n)
void *removeEntry(PQ *pq)
{
    assert(pq != NULL);
    void *root = pq->data[0];
    int location, small;
    location = 0;
    small = 0;
    pq->data[location] = pq->data[pq->count - 1];
    pq->count--;
    while(l(location) < pq->count)
    {
        small = l(location);
        if(r(location) < pq->count)
        {
            if(pq->compare(pq->data[l(location)] , pq->data[r(location)]) < 0)
                small = l(location);
            else
                small = r(location);
        }
        if(pq->compare(pq->data[small],pq->data[location]) < 0)
        {
            void *temp = pq->data[small];
            pq->data[small] = pq->data[location];
            pq->data[location] = temp;
            location = small;
        }
        else
            break;
    }
    return root;
}
