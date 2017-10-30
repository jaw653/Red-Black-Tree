#ifndef __RBT_INCLUDED__
#define __RBT_INCLUDED__

#include <stdio.h>

typedef struct rbt RBT;

extern RBT *newRBT(
    void (*)(FILE *,void *),           //display
    int (*)(void *,void *));           //comparator
extern void insertRBT(RBT *,void *);
extern int findRBT(RBT *,void *);
extern void deleteRBT(RBT *,void *);
extern int sizeRBT(RBT *);
extern int wordsRBT(RBT *);
extern void statisticsRBT(FILE *,RBT *);
extern void displayRBT(FILE *,RBT *);

#endif
