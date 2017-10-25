/*
 * Author: Jake Wachs
 * Date: 10/25/2017
 * The University of Alabama
 *
 * This is Dr. Lusth's interface, copied and pasted
 */

#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

#include <stdio.h>

typedef struct bstnode BSTNODE;

extern void    *getBSTNODE(BSTNODE *n);
extern void    setBSTNODE(BSTNODE *n,void *value);
extern BSTNODE *getBSTNODEleft(BSTNODE *n);
extern void    setBSTNODEleft(BSTNODE *n,BSTNODE *replacement);
extern BSTNODE *getBSTNODEright(BSTNODE *n);
extern void    setBSTNODEright(BSTNODE *n,BSTNODE *replacement);
extern BSTNODE *getBSTNODEparent(BSTNODE *n);
extern void    setBSTNODEparent(BSTNODE *n,BSTNODE *replacement);

typedef struct bst BST;

extern BST *newBST(
    void (*)(FILE *,void *),           //display
    int (*)(void *,void *),            //comparator
    void (*)(void *,void *));          //swapper
extern void    setBSTroot(BST *t,BSTNODE *replacement);
extern BSTNODE *getBSTroot(BST *t);
extern BSTNODE *insertBST(BST *t,void *value);
extern BSTNODE *findBST(BST *t,void *value);
extern BSTNODE *deleteBST(BST *t,void *value);
extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node);
extern void    pruneLeafBST(BST *t,BSTNODE *leaf);
extern int     sizeBST(BST *t);
extern void    statisticsBST(FILE *fp,BST *t);
extern void    displayBST(FILE *fp,BST *t);

#endif
