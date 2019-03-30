#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"
#define END 256

//Declares NODE as struct node
typedef struct node NODE;

NODE *makeNode(NODE *left, NODE *right)
{
    NODE *rt;
    rt = malloc(sizeof(NODE*));
    assert(rt != NULL);
    rt->count = left->count + right->count;
    rt->parent = NULL;
    left->parent = rt;
    right->parent = rt;
    return rt;
}

//Function compartes the data in two nodes
//Big-O: O(1)
int compare(NODE *first, NODE *second)
{
    int fst1 = first->count;
    int scnd2 = second->count;
    return (fst1 < scnd2) ? -1 : (fst1 > scnd2);
}


int main(int argc, char *argv[])
{
    NODE *pNode = malloc(sizeof(NODE *));;
    NODE *pNode1 = malloc(sizeof(NODE *));;
    FILE *fp;
    fp=fopen(argv[1],"r");
    PQ *pq;

    int i;
    int arr1[END+1];
    NODE *arr2[END + 1];
    int root_tot=0;
    int pn,pn_1;
    for(i=0;i<END+1;i++) //O(1) becuse it will always run 256 times
    {
        arr1[i]=0;
        arr2[i]=NULL;
    }
    i=0;
    while(i!=EOF) //O(n)
    {
        i=getc(fp);
        arr1[i]+=1;
    }
    fclose(fp);
    pq = createQueue(compare);
    NODE *newn = malloc(sizeof(NODE));
    newn->count=0;
    newn->parent=NULL;
    addEntry(pq,newn);
    for(i=0;i<END+1;i++) //O(1)
    {
        arr2[256]=malloc(sizeof(NODE *));
        arr2[256]=newn;
        arr1[256]=0;
        
        if(arr1[i]>0)
        {
            arr2[i]=malloc(sizeof(NODE *));
            assert(arr2[i]!=NULL);
            arr2[i]->count=arr1[i];
            arr2[i]->parent=NULL;
            addEntry(pq,arr2[i]);
            root_tot+=arr1[i];
        }
        addEntry(pq,arr2[256]);
    }
    pn=-1;
    pn_1=-1;
    NODE* rootnode;
    rootnode=malloc(sizeof(NODE*));
    while(numEntries(pq)>1)
    {
        pNode=removeEntry(pq);
        pNode1=removeEntry(pq);
        rootnode=makeNode(pNode,pNode1);
        rootnode->parent=NULL;
        rootnode->count=((pNode->count)+(pNode1->count));
        pNode->parent=rootnode;
        pNode1->parent=rootnode;
        addEntry(pq,rootnode);
        
    }
    
    pn=0;
    pn_1=0;
    NODE *pNode3;
    pNode3=malloc(sizeof(NODE*));
    
    for(i=0;i<END;i++)
    {
        if(arr1[i]>0)
        {
            pn++;
            pNode3=arr2[i];
            for(pn_1=0;pNode3->parent!=NULL;pn_1++)
            {
                pNode3=pNode3->parent;
            }
            printf("\n %c %d x %d bits equals %d bits\n",i,arr2[i]->count,pn_1,(pn_1)*(arr2[i]->count));
            
        }
    }
    printf("number of nonnull %d\n",pn);
    pack(argv[1],argv[2],arr2);
    destroyQueue(pq);
    exit(EXIT_SUCCESS);
}
