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

typedef struct GTNODE GTNODE;
struct GTNODE {
  char *value;
  int frequency;
};

GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  GT *t = malloc(sizeof(struct gt));
  t->tree = newBST(d, c, NULL);
  t->display = d;
  t->comparator = c;

  return t;
}

void insertGT(GT *t, void *value) {
  BSTNODE *x = insertBST(t->tree, value);

  if (x == NULL) {
    BSTNODE *newNode = findBST(t->tree, value);
    GTNODE *n = getBSTNODE(newNode);
    n->frequency += 1;
  }
  else {
    //incrementGTNODEfrequency(getBSTNODE(x));
    GTNODE *xx = getBSTNODE(x);
    xx->frequency += 1;
  }
}

int findGT(GT *t, void *value) {
  GTNODE *p = getBSTNODE(findBST(t->tree, value));

  /* Value is not in the tree */
  if (p == NULL) {
    return 0;
  }
  else {
    return p->frequency;
  }
}

void deleteGT(GT *t, void *value) {
  BSTNODE *valueToDelete = findBST(t->tree, value);

  if (valueToDelete != NULL) {
    GTNODE *gtToDelete = getBSTNODE(valueToDelete);
    gtToDelete->frequency -= 1;

    if (gtToDelete->frequency == 0) {
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
  displayBST(fp, t->tree);
}
