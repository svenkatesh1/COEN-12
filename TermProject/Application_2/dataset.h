# ifndef DATASET_H
# define DATASET_H

typedef struct DataSet SET;

extern SET *createSet(int m);

extern void destroySet(SET *sp);

extern void searchid(SET *sp, int id);

extern void insertstu(SET *sp, int id, int age);

extern void removeStu(SET *SP, int id);

# endif /* DATASET_H */
