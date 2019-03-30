#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataset.h"

//structure to store the information of the students
typedef struct studentinfo
{
    int id;
    int age;
}student;

//structure to store all students in an array
typedef struct studata
{
    student **data;
    int count;
    int length;
}SET;

static bool searchid(SET *sp, int id); 

/*
 * The function makestu creates a new student structure and returns the student struct pointer
 */
static student *makestu(int id, int age)
{
    student *stu = malloc(sizeof(student));
    assert(stu != NULL);
    stu->id = id;
    stu->age = age;
    
    return stu;
}

/*
 * The function searchID searches if the student id is in the data list of sp and returns true if found, false if not
 * BigO runtime: O(n)
 */
static bool searchid(SET *sp, int id)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++)
    {
        if(sp->data[i]->id == id)
        {
            return true;
        }
    }
    return false;
}

/*
 * The function createDataSet creates a new set containing students. The function returns a pointer to the new set
 * BigO runtime: O(n)
 */
SET *createDataSet(int m)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    
    sp->data = malloc(sizeof(student*)*m);
    assert(sp->data != NULL);
    //default values are assigned to count and length
    sp->length = m;
    sp->count = 0;
    return sp;
}


/*
 * The function destroyDataSet deallocates all memory that is contained in the node pointed by sp
 * BigO runtime: O(n)
 */
void destroyDataSet(SET *sp)
{
    assert(sp != NULL);
    int i;
    //individually frees every single data
    for(i=0; i<sp->count; i++)
        free(sp->data[i]);
    //frees the entire data set and pointer
    free(sp->data);
    free(sp);
}

/*
 * The function searchAge prints the id of all students with the age age_ent
 * BigO runtime: O(n)
 */
void searchAge(SET *sp, int age_ent)
{
    assert (sp != NULL);
    printf("Please wait... searching for student with age %d\n", age_ent);
    bool iffound = false;
    
    //Searches for value in the array until age is founf and prints the corresponding id if the age is found
    int i;
    for(i=0; (i<sp->count) && (sp->data[i]->age <= age_ent); i++)
    {
        if(sp->data[i]->age == age_ent)
        {
            printf("Student found! Student id is: %d\n",age_ent);
            iffound = true;
        }
    }
    if(!iffound)
        printf("No students with age %d were found in the list\n",age_ent);
}

/*
 * The function insertstu inserts a new student into the array of SET sp in ascending order based on age
 * BigO runtime: O(n)
 */
void insertstu(SET *sp, int id, int age)
{
    assert(sp!= NULL);
    
    //Checking to see if student is not in the list
    if(searchid(sp,id))
    {
        printf("Insertion failed. Student %d is already in the list", id);
        return;
    }
    
    bool index;
    //Use binary search to determine the index where the new student needs to be inserted
    int i = binsearch(sp,age,&index);
    printf("Please wait. Adding %d, age: %d\n", id, age);
    
    //Shifting so that the array remains sorted
    int j;
    for(j = sp->count; j>i ; j--)
    {
        sp->data[j] = sp->data[j-1];
    }
    
    sp->data[i] = makestu(id,age);
    sp->count++;
}

/*
 * The function removestu removes a student from the list of the age passed in and shifts the list so that it remains sorted
 * BigO runtime: O(n)
 */
void removestu(SET *sp, int age)
{
    assert(sp != NULL);
    bool iffound = false;
    int i = binsearch(sp, age, &iffound);
    
    printf("Removing students of age %d\n", age);
    
    if(iffound)
    {
        int min = i;
        int max = i;
        bool search = true;
        int j;
        //Removing all students to the right of i with matching age
        for(j = i; j < sp->count && search ; j++)
        {
            if(sp->data[j]->age != age)
            {
                search = false;
            }
            else
            {
                printf("Student with id %d\t and age %d has been removed\n", sp->data[j]->id, sp->data[j]->age);
                free(sp->data[j]);
                max++;
            }
        }
        
        //Removing all students to the left of i with matching age
        search = true;
        for(int j = i-1; j > -1 && search ; j--)
        {
            if(sp->data[j]->age != age)
            {
                search = false;
            }
            else
            {
                free(sp->data[j]);
                printf("Student with id %d\t and age %d has been removed\n", sp->data[j]->id, sp->data[j]->age);
                min--;
            }
        }
        int agegap = max - min;
        int k;
        //Shifting to keep the data sorted
        for(k = max; k < sp->count && max < sp->count; k++)
        {
            sp->data[min] = sp->data[k];
            min++;
        }
        sp->count -= agegap;
    }
    else
    {
        printf("No students with age %d is found\n", age);
    }
}

/*
 * The function maxAgeGap calculates the maximum age gap in the list and also prints the maximum and minimum age of students in the list
 * BigO runtime: O(1)
 */
void maxAgeGap(SET *sp)
{
    int min = sp->data[0]->age;
    int max = sp->data[sp->count-1]->age;
    int agegap = max - min +1;
    
    printf("The maximum age is: %d\nThe minimum age is: %d\nThe age gap is: %d\n", max, min, agegap);
}

/*
 * Function printall is only for debugging purposes for the shifting and sorting process. The function prints the index, id, and age of every student in the array pointed by pointer sp.
 * BigO runtime: O(n)
 */
void printall(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i=0;i<sp->count;i++)
    {
        printf("[%d]\t#%d:\t%d \n", i, sp->data[i]->id, sp->data[i]->age);
    }
}

/*
 * The function binsearch uses binary search to determine an index in the data array of SET sp where student with specified age should be placed and returns the index in the data array of SET sp of where the student should be placed
 * BigO runtime: O(logn)
 */
static int binsearch(SET *sp, int age, bool *found)
{
    assert(sp != NULL);
    //Binary search initial conditions
    int hi = sp->count - 1;
    int lo = 0;
    int mid = 0;
    *found = false;
    //search operation
    while(lo <= hi)
    {
        mid = (lo + hi)/2;
        if(sp->data[mid]->age > age)
        {
            hi = mid - 1;
        }
        else if(sp->data[mid]->age < age)
        {
            lo = mid + 1;
        }
        else
        {
            *found = true;
            return mid;
        }
    }
    return lo;
}
