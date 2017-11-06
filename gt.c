/* Author: Jake Wachs
 * Date: 10/31/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "gt.h"
#include "gtnode.h"

struct gt {
  struct bst *tree;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};

GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  GT *t = malloc(sizeof(struct gt));
  t->tree = newBST(displayGTNODE, compareGTNODE, swapGTNODE);
  t->display = d;
  t->comparator = c;

  return t;
}

void insertGT(GT *t, void *value) {
  BSTNODE *x = insertBST(t->tree, value);

  if (x == NULL) {
    BSTNODE *newNode = findBST(t->tree, value);
    incrementGTNODEfrequency(newNode);
  }
  else {
    incrementGTNODEfrequency(x);
  }
}

int findGT(GT *t, void *value) {
  GTNODE *p = getGTNODE(findBST(t->tree, value));

  /* Value is not in the tree */
  if (p == NULL) {
    return 0;
  }
  else {
    return getGTNODEfrequency(p);
  }
}

void deleteGT(GT *t, void *value) {
  BSTNODE *valueToDelete = findBST(t->tree, value);

  if (valueToDelete != NULL) {
    int newFreq = decrementGTNODEfrequency(getGTNODE(valueToDelete));
    if (newFreq == 0) {
      deleteBST(t->tree, value);
    }
  }
}

int sizeGT(GT *t) {
  return sizeBST(t->tree);
}

int wordsGT(GT *t) {
  //return the number of words (?)
}

void statisticsGT(FILE *fp, GT *t) {
  //need to figure this out
}

void displayGT(FILE *fp, GT *t) {
  displaBST(fp, t->tree);
}
