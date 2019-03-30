//Created by Shreya Venkatesh
//COEN 12 Lab 4
//Submitted on Sunday Feb 24,2019

#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node //struct node which stores data and pointers to the next and previous nodes
{
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

struct list //struct lists consists of nodes that has the reference pointer to the head at the front of the list. Compare function is a predesigned function
{
	int count;
	NODE *head;
	int (*compare)();
};

/* The function allocates memory and creates a list with a dummy node. The list keeps track of the number of elements it has.
 Runtime: O(1)
 */
LIST *createList(int(*compare)())
{
	LIST *lp;

	lp = malloc(sizeof(LIST));
	assert(lp!=NULL);

	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
    assert(lp->head!=NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}
/*
 Function destroys the list by removing the last element in the list.
 Runtime: O(n)
 */
void destroyList(LIST *lp)
{
	assert(lp!=NULL);
    NODE *pnext;
    NODE *pDel = lp->head;
    do
    {
        pnext = pDel->next;
        free(pDel);
        pDel = pnext;
    }while(pDel!=lp->head);
    free(lp);
}
/*
 Function returns the number of items in the list
 Runtime: O(1)
 */
int numItems(LIST *lp)
{
	assert(lp!=NULL);
	return lp->count;
}
/*
 The function inserts a node into a list with data at the front of the queue.
 Runtime: O(1)
 */
void addFirst(LIST *lp,void *item)
{
    assert(lp!=NULL && item!=NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->next = lp->head->next;
    new->prev = lp->head;
    lp->head->next = new;
    new->next->prev = new;
    lp->count++;
}
/*
 The function inserts a node into a list with some data at the rear end of the queue.
 Runtime: O(1)
 */
void addLast(LIST *lp, void *item)
{
    assert(lp!=NULL && item!=NULL);
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = item;
    newNode->next = lp->head;
    newNode->prev = lp->head->prev;
    lp->head->prev = newNode;
    newNode->prev->next = newNode;
    lp->count++;
}
/*
 The function removes the first element of the list and returns the data of the removed element.
 Runtime: O(1)
 */
void *removeFirst(LIST *lp)
{
	assert(lp!=NULL);
	
	NODE *firstNode = lp->head->next;
	void *firstData = firstNode->data;

	lp->head->next = firstNode->next;
	firstNode->next->prev = lp->head;

	free(firstNode);
	lp->count--;
	
	return firstData;
}
/*
 The function removes the last element of the list and returns the data of the removed element. The functionality of the function is the same as removeFirst but the operations are done at the other end of the list.
 Runtime: O(1)
 */
void *removeLast(LIST *lp)
{
	assert (lp->count>0);
	NODE *lastNode = lp->head->prev;
	void *lastData = lastNode->data;

	lastNode->prev->next = lp->head;
	lp->head->prev = lastNode->prev;

	free(lastNode);
	lp->count--;

	return lastData;
}
/*
 The function returns data of the first element in dequeue.
 Runtime:O(1)
 */
void *getFirst(LIST *lp)
{
	assert(lp->count>0);
	return lp->head->next->data;
}
/*
 The function returns data of last element in the dequeue
 Runtime: O(1)
 */
void *getLast(LIST *lp)
{
	assert(lp->count>0);
	return lp->head->prev->data;
}
/*
 The function removes a node given the list and data. The function traverses the list until the data is found.
 Runtime: O(n)
 */
void removeItem(LIST *lp,void *item)
{
	assert(lp!=NULL && item != NULL);
    NODE *temp;
    NODE *nextp;
    NODE *prevp;
    temp = lp->head->next;
    int i;
    if(lp->count > 0)
    {
        for(i=0; i<lp->count;i++)
        {
            nextp = temp->next;
            prevp = temp->prev;
            if((*lp->compare)(temp->data,item) == 0)
            {
                prevp->next = nextp;
                nextp->prev = prevp;
                free(temp);
                lp->count --;
                i = lp->count;
            }
            else
                temp = temp->next;
        }
    }
}
/*
 The function returns data if a node with data is found in the lisst else it returns NULL value.
 Runtime: O(n)
 */
void *findItem(LIST *lp,void *item)
{
	assert(lp!=NULL && item!=NULL);
    NODE *temp;
    temp = lp->head->next;
    
    if(lp->head != lp->head->next)
    {
        for(int i=0;i<lp->count;i++)
        {
            if((*lp->compare)(temp->data,item) == 0)
                return temp->data;
            temp = temp->next;
        }
    }
    return NULL;
}
/*
 The function returns an arraay with all the data from eeach node based on user preference. The function initializes an array and then traverses through the entire list and copies each node's data into the array.
 Runtime: O(n)
 */
void *getItems(LIST *lp)
{
	void **ar;
	ar = malloc(sizeof(void*)*lp->count);
	int i;
	NODE *theNode = lp->head->next;
	for(i=0;i<lp->count;i++)
	{
		ar[i] = theNode->data;
		theNode = theNode->next;
	}
	return ar;
}
