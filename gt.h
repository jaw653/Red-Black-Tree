/* Author: Jake Wachs
 * Date: 10/31/2017
 * The University of Alabama
 */

#ifndef __GT_INCLUDED__
#define __GT_INCLUDED__

#include <stdio.h>

typedef struct gt GT;

extern GT *newGT(
    void (*)(FILE *,void *),           //display
    int (*)(void *,void *));           //comparator
extern void insertGT(GT *,void *);
extern int findGT(GT *,void *);
extern void deleteGT(GT *,void *);
extern int sizeGT(GT *);
extern int wordsGT(GT *);
extern void statisticsGT(FILE *,GT *);
extern void displayGT(FILE *,GT *);

#endif
