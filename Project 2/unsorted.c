#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include "set.h"
#include <string.h>

typedef struct set
{
	int count;
	int length;
	char **data;
}SET;

static int search(SET *sp, char *elt);

/*  Function name: createSet
 Algorithm complexity O(1) */

SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*  Function name: destroySet
 Algorithm complexity O(n) */

void destroySet(SET *sp)
{
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->count;i++)
	{
		free (sp->data[i]);
	}
	free (sp->data);
	free(sp);
}

/*  Function name: numElements
 Algorithm complexity O(1) */

int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/*  Function name: numElements
 Algorithm complexity O(1) */

void addElement(SET *sp, char *elt)
{
	if(search(sp,elt) == -1)
	{
		sp->data[sp->count] = strdup(elt);
		sp->count++;
	} 
}

/*  Function name: removeElement
 Algorithm complexity O(n) */

void removeElement(SET *sp, char *elt)
{
	int x = search(sp,elt);
	if(x != -1)
	{
		free(sp->data[x]);
		sp->data[x] = sp->data[sp->count-1];
	}
	sp->count --;
}

/*  Function name: findElement
 Algorithm complexity O(n) */

char *findElement(SET *sp,char *elt)
{
	assert(sp!=NULL);
	int x = search(sp,elt);
	if(x == -1)
        return NULL;
	return sp->data[x];
}

/*  Function name: getElements
 Algorithm complexity O(n) */

char **getElements(SET *sp)
{
	assert(sp != NULL);
	char **strings = malloc(sizeof(char*)*sp->count);
	for(int i = 0;i<sp->count;i++)
	{
		strings[i] = strdup(sp->data[i]);
	}
	return strings;
}

/*  Function name: binsearch
 Algorithm complexity O(n) */

static int search(SET *sp, char *elt)
{
	assert(sp!=NULL);
	int i = 0;
	while(i<sp->count)
	{
		if(strcmp(sp->data[i],elt) == 0)
		{
			return i;
		}
		i++;
	}
	return -1; //if element is not found
}

