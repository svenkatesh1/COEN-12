//Created by Shreya Venkatesh
//COEN 12 Lab 4
//Submitted on Feb 24,2019

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"
#include <string.h>
#define AVG_LENGTH 20

typedef struct set
{
    int count;
    int length;
    LIST **lists;
    int (*compare)();
    unsigned(*hash)();
}SET;

/*
Function allocates memory and creates a set that keeps track of the number of elements, length of the array and the lists.
 * Runtime: O(n)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp;
    sp=malloc(sizeof(SET)); //declare set and allocate memory
    assert(sp!=NULL && compare!=NULL);
    sp->count = 0; //tracker for number of elements in the set
    sp->length=maxElts/AVG_LENGTH; //length of array
    sp->lists = malloc(sizeof(LIST*)*sp->length); //array that stores the nodes for data storage
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for (i = 0;i<sp->length;i++)
    {
        sp->lists[i]=createList(compare); //create an empty list at eacg arrat spot which will fill the node with data
    }
	assert(sp->lists !=NULL);	
    return sp;
}

/*
Function frees the lists array by going through each node of the list
 * Runtime: O(1)
 */
void destroySet(SET *sp){
    assert(sp != NULL);
    for(int i= 0; i<sp->length;i++)
    {
        free(sp->lists[i]);  //free each node in list
    }
    free(sp->lists);    //completely free the lists
    free(sp);   //free the set
}

/*
Function returns the number of elements in the list
 * Runtime: O(1)
 */
int numElements(SET *sp)
{
    assert(sp!=NULL);
    return sp->count;
}

/*
 Function implementation was mostly done in list.c. The hash location is kept in tracking and then findItem is used to determine if we fount the item in that spot in the array. if not found, it will be added to the list.
 * Runtime: O(n)
 */
void addElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int index = (*sp->hash)(elt)%sp->length;
    if (!findItem(sp->lists[index],elt))
    {
        addFirst(sp->lists[index],elt);
        sp->count++;
    }
    
}

/*
 Similar to addElement(), the removeElement function uses the findItem to search for the element. if found, the removeItem in list.c is used to delete the node from the list.
 * Runtime: O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int index = (*sp->hash)(elt)%sp->length;
    if (findItem(sp->lists[index],elt)!= NULL)
    {
        removeItem(sp->lists[index],elt);
        sp->count--;
    }
}

/*
 Function returns the element if found. If not found returns NULL. Function finds the hash location in the array and calls FindElement.
 * Runtime: O(n)
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp!=NULL && elt!=NULL);
    int index = (*sp->hash)(elt)%sp->length;
    return findItem(sp->lists[index],elt);
}
/*
 Function returns the copy of the array. The function returns a 1-d array that is formed from the linked lists given. 
 * Runtime: O(n^2)
 */
void *getElements(SET *sp)
{
	assert(sp!=NULL);
	void **arr = malloc(sizeof(void*)*sp->count);
    void **copy;
	assert(arr != NULL);
	int j = 0,i;
	for(i = 0; j< sp->count; i++)
	{
        copy = malloc(sizeof(void*)*(numItems(sp->lists[i])));
        copy = getItems(sp->lists[i]);
        memcpy(arr + j, arr, sizeof(void*)*numItems(sp->lists[i]));
        j+=numItems(sp->lists[i]);
        free(copy);
    }
    return arr;
}

