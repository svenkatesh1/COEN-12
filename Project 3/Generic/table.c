#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "set.h"

#define EMPTY 1
#define FILLED 2
#define DELETED 3

static int search(SET *sp,void *elt, bool *found);

//Set for storing data structurees
typedef struct set
{
	int count;
	int length;
	void **data;
	int *flags;
	int (*compare)();
	unsigned (*hash)();
}SET;

/*The function allocates memory and creates a set that keeps track of the number of elements, length of the array. On initilizing sets, it sets all flags to empty
BigO: O(n)
*/
SET *createSet(int maxElts, int (*compare)(),unsigned (*hash)())
{
	int i;
	SET *sp;
	sp = (SET*)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = (void **)malloc(sizeof(void*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);
	for(i=0;i<sp->length;i++)
	{
		sp->flags[i] = EMPTY;
	}
	sp->compare = compare;
	sp->hash = hash;
	return sp;
}

/* 
Function destroys the set by freeing the memory
BigO: O(1)
*/
void destroySet(SET *sp)
{
	assert(sp != NULL);
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}

/*
Function returns the number of elements in the set
BigO: O(1)
*/
int numElements(SET *sp)
{
	assert(sp != NULL);
	return(sp->count);
}

/* 
Function adds all the elements into the data. Search is done using linear probing.
BigO: O(n)
*/
void addElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    if (sp->count == sp->length)
        return;
    bool found = false;
    int index = search(sp, elt, &found);
    
    if(found == true || index == -1)
        return;
    
    sp->data[index] = elt;
    sp->flags[index] = FILLED;
    sp->count++;
    return;
}

/*
 Function searches using linear probing. If found, memory is freed at that location and the flag is changed to DELETED
 BigO: O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool searching = false;
    int index = search(sp, elt, &searching);
    if (searching == true)
    {
        free(sp->data[index]);
        sp->flags[index] = DELETED;
        sp->count--;
    }
    return;
}

/*
 Function uses the search function and if the searching is positive, then the element is returned, else NULL is returned
 BigO: O(n)
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if(found == true)
        return (sp->data[index]);
    return NULL;
}
    
/*
 Function returns the copy of array.
 BigO: O(n)
 */
void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **cpy = malloc(sizeof(void *)* sp->count);
    assert(cpy != NULL);
    int i, j;
    j = 0;
    for(i = 0; i < sp->length; i++)
    {
        if(sp->flags[i] == FILLED)
        {
            cpy[j] = sp->data[i];
            j++;
        }
    }
    return cpy;
}

/*
 Function uses a hash function to search and return the index of the element searched.
 BigO: O(n)
 */
static int search(SET *sp, void *elt, bool *found)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int i, position;
    int first = -1;
    *found = false;
    unsigned key = sp->hash(elt);
        
    for(i = 0; i < sp->length; i++)
    {
        position = (key + i) % (sp->length);
        if(sp->flags[position] == FILLED)
        {
            if((*sp->compare) (elt, sp->data[position]) == 0)
            {
                *found = true;
                return (position);
            }
        }
        if(sp->flags[position] == DELETED)
        {
            first = position;
        }
        if(sp->flags[position] == EMPTY)
        {
            if(first > -1)
                return first;
            return position;
        }
    }
    return -1;
}

