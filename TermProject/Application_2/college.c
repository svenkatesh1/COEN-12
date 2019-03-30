# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>
# include "dataset.h"

# define MAX_STUDENTS 3000

int ran(int min, int max)
{
    return ((rand() % (max - min + 1)) + min);
}

int main(void){
    srand (time(NULL));
    SET *sp = createSet(MAX_STUDENTS);
    
    int id = ran(1, 2);
    
    for(int i = 0; i < 1000; i++)
    {
        int age = ran(18, 30);
        insertstu(sp, id, age);
        id += ran(1,2);
    }
    
    searchid(sp, ran(1,2000));
    int a = ran(1, 2000);
    removeStu(sp, a);
    searchid(sp, a);
    destroySet(sp);
    return 0;
}

