# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>

#define EMPTY 1
#define FILLED 2
#define DELETED 3

static int search(SET *sp, char *elt, bool *found);

//Function hashes char * and returns unsigned
//Big-O: O(1)
unsigned strhash(char *s)
{
    unsigned hash = 0;
    while(*s != 0)
        hash = 31 * hash + *s ++;
    return hash;
}

typedef struct set
{
    int count;
    int length;
    char ** data;
    int *flags;
} SET;

//Function allocates memory and creates a set that keeps track of number of elements, length of the array and the array data.
//Big-O: O(n)
SET *createSet(int maxElts)
{
    int i;
    SET *sp;
    sp = (SET*)malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = (char **)malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    sp->flags = malloc(sizeof(int*)*maxElts);
    assert(sp->flags != NULL);
    for(i = 0; i < sp->length; i++)
    {
        sp->flags[i] = EMPTY;
    }
    return sp;
}

//Fucntion destroys the sets by freeing memory
//Big-O: O(n)
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++)
    {
        if(sp->flags[i] == FILLED)
            free(sp->data[i]);
    }
    free(sp->data);
    free(sp->flags);
    free(sp);
    return;
}

//Function returns number of elements
//Big-O: O(1)
int numElements(SET *sp)
{
    assert(sp != NULL);
    return (sp->count);
}

//Function adds elements by hashing. Searches using linear probling and the bool is used to keep tracking of whether it is found
//Big-O: O(n)
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    if (sp->count == sp->length) return;
    bool found = false;
    int index = search(sp, elt, &found);
    
    if(found == true || index == -1) return;
    
    sp->data[index] = strdup(elt);
    sp->flags[index] = FILLED;
    sp->count++;
    return;
}

//Function hashes then removes elements and sets the flag to DELETED
//Big-O: O(n)
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found == true)
    {
        free(sp->data[index]);
        sp->flags[index] = DELETED;
        sp->count--;
    }
    return;
}

//Uses the search function. If search is true, then element is returned else NULL is returned
//Big-O: O(n)
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if(found == true)
        return (sp->data[index]);
    return NULL;
    
}

//Function allocates and copys char** data then returns a copy of the array
//Big-O: O(n)
char **getElements(SET *sp)
{
    assert(sp != NULL);
    char ** copy = malloc(sizeof(char *)* sp->count);
    assert(copy != NULL);
    int i, j;
    j = 0;
    for(i = 0; i < sp->length; i++)
    {
        if(sp->flags[i] == FILLED)
        {
            memcpy(copy[j],sp->data[i], sizeof(char*)*sp->count);
            j++;
        }
    }
    return copy;
}

//Function uses a hash function to search
//Big-O: O(n)
static int search(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int i, pos;
    int first = -1;
    *found = false;
    unsigned key = strhash(elt);
    
    for(i = 0; i < sp->length; i++)
    {
        pos = (key + i) % (sp->length);
        
        if(sp->flags[pos] == FILLED)
        {
            if(strcmp(elt, sp->data[pos]) == 0)
            {
                *found = true;
                return (pos);
            }
        }
        if(sp->flags[pos] == DELETED)
        {
            first = pos;
        }
        if(sp->flags[pos] == EMPTY)
        {
            if(first > -1)
            {
                return first;
            }
            return pos;
        }
    }
    return -1;
}
