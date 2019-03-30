#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataset.h"

#define EMPTY 0
#define FILL 1
#define DELETE 2

//struct to store student information and data
typedef struct studentinfo
{
    int age;
    int id;
}student;

//datastructure to store students
typedef struct DataSet
{
    int count;
    int length;
    char *flag;
    student **data; //Student data as an array of student pointers
}SET;

//function declarations
static int cmp(int x,int y);
static int quadsearch(SET *sp, int id, bool *iffound);

/*
 * The function createSet creates a new set that contains students and returns the pointer to the new set
 * BigO runtime: O(n)
 */
SET *createSet(int x)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    
    sp->data = malloc(sizeof(student*)*x);
    assert(sp->data != NULL);
    
    sp->flag = malloc(sizeof(char)*x);
    assert(sp->flag != NULL);
    
    //Set flag to default values for all other variables
    int i;
    for(i=0 ; i<x; i++)
        sp->flag[i] = EMPTY;
    
    sp->length = x;
    sp->count = 0;
    return sp;
}

/*
 * The function destroySet frees all memory in SET pointed by sp
 * BigO runtime: O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i=0; i<sp->length; i++)
    {
        if(sp->flag[i] == FILL)
            free(sp->data[i]);
    }
    
    //free all the remaining data
    free(sp->flag);
    free(sp->data);
    free(sp);
}

/*
 * The function searchid uses a hashtable to find the student with the specified id and print out whether it is found in the table.
 * BigO runtime: Worst case - O(n), Best Case - O(1)
 */
void searchid(SET *sp, int id)
{
    assert(sp != NULL);
    bool iffound = false;
    
    //Hash function to locate index of the student
    int a = quadsearch(sp, id, &iffound);
    if(iffound)
        printf("Student with id %d and age %d has been found\n", id, sp->data[a]->age);
    else
        printf("The student you are looking for cannot be located");
}

/*
 * The function insertstu inserts a student with a given id and age into the hashtable
 * BigO runtime: Worst case - O(n), Best case - O(1)
 */
void insertstu(SET *sp, int id, int age)
{
    assert(sp != NULL);
    bool iffound = false;
    
    //Hash function to find the index to be inserted at
    int a = quadsearch(sp, id, &iffound);
    
    //Add the student if the student is not in the list
    if(!iffound)
    {
        sp->data[a] = malloc(sizeof(student));
        sp->data[a]->id = id;
        sp->data[a]->age = age;
        sp->flag[a] = FILL;
        sp->count++;
        printf("Student %d of age %d is being added at [%d]\n",a,id,age);
    }
    else
        printf("Student already exists in the list\n");
}

/*
 * The function removeStu removes the student of specific hashtable
 * BigO runtime: Worst Case - O(n), Best case - O(1)
 */
void removeStu(SET *sp, int id)
{
    assert(sp != NULL);
    bool iffound = false;
    
    int a = quadsearch(sp, id, &iffound);
    
    if(iffound)
    {
        printf("Removing student with id %d of age %d\n", id, sp->data[a]->age);
        free(sp->data[a]);
        sp->flag[a] = DELETE;
        sp->count--;
    }
    else
        printf("Student cannot be found\n");
}

/*
 * The function comp compares two integers and returns the difference between x and y
 * BigO runtime: O(1)
 */
static int comp(int x, int y)
{
    return (x-y);
}

/*
 * The function quadsearch uses quadratic probing to find the student in a hashtable wish a specific ID and returns the index at which the student was found and if not found, the index where the student can be inserted is returned
 * BigO runtime: Worst Case - O(n), Best case - O(1)
 */
static int quadsearch(SET *sp, int id, bool *iffound){
    
    assert(sp != NULL);
    int loc = -1;
    int a = 0;
    *iffound = false;
    int i;
    
    for(i = 0; i < sp->length; i++)
    {
        //Linear Probing
        a = (id + i) % sp->length;
        
        //Checks all three cases for the flag
        if(sp->flag[a] == FILL)
        {
            //Check if the values are the same if a filled element is encountered
            if(comp(sp->data[a]->id, id) == 0)
            {
                *iffound = true;
                return a;
            }
        }
        else if(sp->flag[a] == EMPTY)
        {
            //Search ends when an empty element is encountered
            if(loc > -1)
                //Return last deleted index if one is found
                return loc;
            else
            {
                //Return hash otherwise
                return a;
            }
        }
        else if(sp->flag[a] == DELETE)
        {
            //Remember the first deleted slot
            if(loc < 0)
                loc = a;
        }
    }
    return loc;
}
