#ifndef DATASET_H
#define DATASET_H

typedef struct studata SET;

extern SET *createDataSet(int m);

extern void destroyDataSet(SET *sp);

extern void searchAge(SET *sp, int age_ent);

extern void insertstu(SET *sp, int id, int age);

extern void removestu(SET *sp, int age);

extern void maxAgeGap(SET *sp);

extern void printall(SET *sp);

#endif
