#ifndef __INTEGER_INCLUDED__
#define __INTEGER_INCLUDED__

#include <stdio.h>

typedef struct INTEGER INTEGER;

extern INTEGER *newINTEGER(int);
extern int getINTEGER(INTEGER *);
extern int setINTEGER(INTEGER *,int);
extern void displayINTEGER(FILE *,void *);
extern void freeINTEGER(INTEGER *);

#endif
