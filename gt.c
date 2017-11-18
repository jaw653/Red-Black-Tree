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
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};

typedef struct GTNODE GTNODE;
struct GTNODE {
  void *value;      //holds the actual value, STRING or INTEGER or whatever
  int frequency;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};

static GTNODE *newGTNODE(void *value, void (*)(FILE *, void *), int (*)(void *, void *));
static void displayGTNODE(FILE *, void *);
static void swapGTNODE(BSTNODE *, BSTNODE *);
static int compareGTNODE(void *, void *);
static int findMinDepthGT(BSTNODE *);
static int findMaxDepthGT(BSTNODE *);

GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  GT *t = malloc(sizeof(struct gt));
  t->tree = newBST(displayGTNODE, compareGTNODE, swapGTNODE);
  t->display = d;
  t->comparator = c;
  t->totalWords = 0;

  return t;
}

void insertGT(GT *t, void *value) {
  GTNODE *valueNode = newGTNODE(value, t->display, t->comparator);

  BSTNODE *valueToFind = findBST(t->tree, valueNode);

  /* If value is in the tree, just increment it */
  if (valueToFind != NULL) {
    GTNODE *nodeToIncrement = getBSTNODE(valueToFind);
    nodeToIncrement->frequency += 1;
  }
  else {
    insertBST(t->tree, valueNode);
  }

  t->totalWords += 1;
//  printf("totalWords is: %d\n", t->totalWords);
}

int findGT(GT *t, void *value) {
  GTNODE *valueNode = newGTNODE(value, t->display, t->comparator);
  GTNODE *p = getBSTNODE(findBST(t->tree, valueNode));

  /* Value is not in the tree */
  if (p == NULL)
    return 0;
  else
    return p->frequency;
}

void deleteGT(GT *t, void *value) {
  GTNODE *valueNode = newGTNODE(value, t->display, t->comparator);
  //printf("value node to find is: %s\n", getSTRING(valueNode->value));
//  printf("delete value is: %s\n", getSTRING(valueNode->value));


  BSTNODE *valueToDelete = findBST(t->tree, valueNode);
  //if (valueToDelete == NULL) printf("value is null\n");

  if (valueToDelete != NULL) {
    GTNODE *gtToDelete = getBSTNODE(valueToDelete);
    gtToDelete->frequency -= 1;
//printf("%s decremented to: %d\n", getSTRING(gtToDelete->value), gtToDelete->frequency);
    if (gtToDelete->frequency <= 0) {
//printf("deleteBST(%s)\n", getSTRING(gtToDelete->value));
      deleteBST(t->tree, valueNode);
    }

    t->totalWords -= 1;
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
  fprintf(fp, "Nodes: %d\n", sizeBST(t->tree));
  fprintf(fp, "Minimum depth: %d\n", findMinDepthGT(getBSTroot(t->tree)));
  fprintf(fp, "Maximum depth: %d\n", findMaxDepthGT(getBSTroot(t->tree)));
}

void displayGT(FILE *fp, GT *t) {
  displayBST(fp, t->tree);
  fprintf(fp, "\n");
}

/******************************************************************************/
/***                          Helper Functions                              ***/
/******************************************************************************/
static GTNODE *newGTNODE(void *value, void (*d)(FILE *, void *), int (*c)(void *, void*)) {
  GTNODE *node = malloc(sizeof(struct GTNODE));
  node->value = value;
  node->frequency = 1;
  node->display = d;
  node->comparator = c;

  return node;
}

static void displayGTNODE(FILE *fp, void *value) {
  GTNODE *node = value;
  node->display(fp, node->value);
  if (node->frequency > 1) {
    fprintf(fp, "-");
    fprintf(fp, "%d", node->frequency);
  }
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

static int compareGTNODE(void *n1, void *n2) {
  GTNODE *node1 = n1;
  GTNODE *node2 = n2;

  if (node1 == NULL) {
    if (node2 == NULL)
      return 0;
    else
      return -1;
  }
  if (node2 == NULL) {
    return 1;
  }

  return node1->comparator(node1->value, node2->value);
}

static int findMinDepthGT(BSTNODE *root) {
  if (root == NULL)
    return 0;

  int Lmin = findMinDepthGT(getBSTNODEleft(root));
  int Rmin = findMinDepthGT(getBSTNODEright(root));

  return (Lmin<Rmin?Lmin:Rmin) + 1;
}

static int findMaxDepthGT(BSTNODE *root) {
  if (root == NULL)
    return 0;

  int Ldepth = findMaxDepthGT(getBSTNODEleft(root));
  int Rdepth = findMaxDepthGT(getBSTNODEright(root));

  return (Ldepth>Rdepth?Ldepth:Rdepth) + 1;
}
