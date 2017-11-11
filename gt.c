/* Author: Jake Wachs
 * Date: 10/31/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "gt.h"

struct gt {
  struct bst *tree;
  int totalWords;
  int numNodes;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};

typedef struct GTNODE GTNODE;
struct GTNODE {
  void *value;
  int frequency;
};
static GTNODE *newGTNODE(void *value);
static void displayGTNODE(FILE *, void *x);
static void swapGTNODE(BSTNODE *, BSTNODE *);
static int findMinDepthGT(BSTNODE *);
static int findMaxDepthGT(BSTNODE *);
static int min(int, int);

static GTNODE *newGTNODE(void *value) {
  GTNODE *node = malloc(sizeof(struct GTNODE));
  node->value = value;
  node->frequency = 1;

  return node;
}
GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  GT *t = malloc(sizeof(struct gt));
  t->tree = newBST(displayGTNODE, c, swapGTNODE);
  t->display = d;
  t->comparator = c;
  t->totalWords = 0;
  t->numNodes = 0;

  return t;
}

void insertGT(GT *t, void *value) {
  BSTNODE *valueToFind = findBST(t->tree, value);
  /* If value is in the tree, just increment it */
  if (valueToFind != NULL) {
    getBSTNODE(valueToFind)->frequency += 1;
  }
  else {
    GTNODE *valueObject = newGTNODE(value);
    insertBST(t->tree, valueObject);
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
  t->totalWords -= 1;
  BSTNODE *valueToDelete = findBST(t->tree, value);

  if (valueToDelete != NULL) {
    GTNODE *gtToDelete = getBSTNODE(valueToDelete);
    gtToDelete->frequency -= 1;

    if (gtToDelete->frequency == 0) {
      deleteBST(t->tree, value);
      t->numNodes -= 1;
    }
  }
}

int sizeGT(GT *t) {
  return sizeBST(t->tree);
}

int wordsGT(GT *t) {
  return t->totalWords;
}

void statisticsGT(FILE *fp, GT *t) {
  fprintf(fp, "Words/Phrases: %d\n", t->totalWords);
  fprintf(fp, "Nodes: %d\n", t->numNodes);
  fprintf(fp, "Minimum Depth: %d\n", findMinDepthGT(getBSTroot(t->tree)));    //FIXME: figure it out
  fprintf(fp, "Maximum Depth: %d\n", findMaxDepthGT(getBSTroot(t->tree)));    //FIXME: figure it out
}

void displayGT(FILE *fp, GT *t) {
  displayBST(fp, t->tree);
}

static void displayGTNODE(FILE *fp, void *x) {
  GTNODE *node = x;
  fprintf(fp, "%s-%d", node->value, node->frequency);
}
static void swapGTNODE(BSTNODE *n1, BSTNODE *n2) {
  GTNODE *ra = getBSTNODE(n1);
  GTNODE *rb = getBSTNODE(n2);

  void *vtemp = ra->value;
  ra->value = rb->value;
  rb->value = vtemp;

  int ctemp = ra->frequency;
  ra->frequency = rb->frequency;
  rb->frequency = ctemp;
}

static int findMinDepthGT(BSTNODE *root) {
  if (root == NULL) {
    return 0;
  }
  if (getBSTNODEleft(root) == NULL && getBSTNODEright(root) == NULL) {
    return 1;
  }
  if (!getBSTNODEleft(root)) {
    return findMinDepthGT(getBSTNODEright(root)) + 1;
  }
  if (!getBSTNODEright(root)) {
    return findMinDepthGT(getBSTNODEleft(root)) + 1;
  }

  return min(findMinDepthGT(getBSTNODEleft(root)), findMinDepthGT(getBSTNODEright(root))) + 1;
}

static int findMaxDepthGT(BSTNODE *root) {
  if (root == NULL) return 0;
  else {
    int L_depth = findMaxDepthGT(getBSTNODEleft(root));
    int R_depth = findMaxDepthGT(getBSTNODEright(root));

    if (L_depth > R_depth) {
      return L_depth + 1;
    }
    else return R_depth + 1;
  }
}

static int min(int a, int b) {
    if (a < b) return a;
    else if (a > b) return b;
    else {
      return a;
    }
}
