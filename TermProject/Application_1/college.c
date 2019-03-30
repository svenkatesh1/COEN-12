#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "dataset.h"
#define MAX_STUDENTS 3000

int randomized(int min,int max)
{
	return((rand() % (max - min + 1)) + min);
}

int main(void)
{
    srand(time(NULL));
    SET *sp = createDataSet(MAX_STUDENTS);
    int id = randomized(1,2);
    int i;
    for(i = 0; i < 1000; i++)
    {
        int age = randomized(18,30);
        insertstu(sp,id,age);
        id += randomized(1,2);
    }
    
    searchAge(sp, randomized(18,30));
    int ran = randomized(18,30);
    removestu(sp,ran);
    searchAge(sp,ran);
    maxAgeGap(sp);
    destroyDataSet(sp);
    return 0;
}
