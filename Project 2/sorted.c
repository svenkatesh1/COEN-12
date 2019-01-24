#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<assert.h>
#include "set.h"
#include <stdbool.h>

//Set structure declaration
typedef struct set
{
	int length;
	int count;
	char **data;
}SET;

static int binsearch(SET *, char *, bool *);

/*  Function name: createSet
    Algorithm complexity O(1) */

SET *createSet(int maxElts)
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*  Function name: destroySet
 Algorithm complexity O(n) */

void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	for(i=0;i<sp->count;i++)
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

/*  Function name: numElements
 Algorithm complexity O(1) */

int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*  Function name: numElements
 Algorithm complexity O(1) */
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
	bool isfound = true;
	int idx = binsearch(sp,elt,&isfound);
	int i;
	if(isfound == false)
	{
		for(i = sp->count;i>idx ; i--)
			sp->data[i] = sp->data[i-1];
		sp->data[idx] = strdup(elt);
		sp->count++;
	}
}

/*  Function name: removeElement
 Algorithm complexity O(n) */

void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
	bool isfound = true;
	int idx = binsearch(sp,elt,&isfound);
	int i;
	if(isfound == true)
	{
        free(sp->data[idx]);
		for(i = idx + 1; i<sp->count; i++)
			sp->data[i-1] = sp->data[i];
		sp->count--;
	}
}

/*  Function name: findElement
 Algorithm complexity O(logn) */

char *findElement(SET*sp,char *elt)
{
	assert(sp!=NULL);
	bool isfound = true;
	int idx = binsearch(sp,elt,&isfound);
	if(isfound == true)
		return elt;
    else
        return NULL;
}

/*  Function name: getElements
 Algorithm complexity O(n) */

char **getElements(SET *sp)
{
	assert(sp!=NULL);
	char **strings;
	memcpy(strings,sp->data,sp->length);
	return strings;
}

/*  Function name: binsearch
 Algorithm complexity O(logn) */

static int binsearch(SET *sp, char *elt, bool *found)
{
	int lo = 0;
	int mid;
	int hi = sp->count-1;

	while(lo<=hi)
	{
		mid = (lo+hi)/2;
		if(strcmp(elt,sp->data[mid]) < 0)
		{
			hi = mid - 1;
		}
		else if(strcmp(elt, sp->data[mid]) > 0)
			lo = mid + 1;
		else
		{
			*found = true;
			return mid;
		}
	}
	*found = false;
	return lo;
}
