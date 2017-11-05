/* Author: Jake Wachs
 * Wrapper for GTNODE data typedef
 */

#ifndef __GTNODE_INCLUDED__
#define __GTNODE_INCLUDED__

#include <stdio.h>
#include "bst.h"

typedef struct GTNODE GTNODE;

extern GTNODE *newGTNODE(char *);
extern char *getGTNODE(GTNODE *);
extern char *setGTNODE(GTNODE *, char *);
extern void displayGTNODE(FILE *, void *);
extern void freeGTNODE(GTNODE *);
extern int getGTNODEfrequency(GTNODE *);
extern void setGTNODEfrequency(GTNODE *, int);
extern int incrementGTNODEfrequency(GTNODE *);
extern int decrementGTNODEfrequency(GTNODE *);
extern int compareGTNODE(void *, void *);
extern void swapGTNODE(void *, void *);
//swapGTNODE

#endif
