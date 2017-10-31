/* Author: Jake Wachs
 * Wrapper for RBTNODE data typedef
 */

#ifndef __RBTNODE_INCLUDED__
#define __RBTNODE_INCLUDED__

#include <stdio.h>
#include "bst.h"

typedef struct RBTNODE RBTNODE;

extern RBTNODE *newRBTNODE(char *);
extern char *getRBTNODE(RBTNODE *);
extern char *setRBTNODE(RBTNODE *, char *);
extern void displayRBTNODE(FILE *, void *);
extern void freeRBTNODE(RBTNODE *);
extern char getRBTNODEcolor(RBTNODE *);
extern void setRBTNODEcolor(RBTNODE *, char);
extern int getRBTNODEfrequency(RBTNODE *);
extern void setRBTNODEfrequency(RBTNODE *, int);
extern int incrementRBTNODEfrequency(RBTNODE *);
extern int decrementRBTNODEfrequency(RBTNODE *);
extern int compareRBTNODE(void *, void *);
extern void swapRBTNODE(BSTNODE *, BSTNODE *);
//swapRBTNODE

#endif
