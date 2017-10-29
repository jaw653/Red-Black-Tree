/* Author: Jake Wachs
 * Wrapper for REAL data typedef
 */

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

#include <stdio.h>

typedef struct REAL REAL;

extern REAL *newREAL(double);
extern double getREAL(REAL *);
extern double setREAL(REAL *, double);
extern void displayREAL(FILE *, void *);
extern void freeREAL(REAL *);
extern int compareREAL(void *, void *);

#endif
