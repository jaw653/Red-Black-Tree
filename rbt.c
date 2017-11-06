/* Author: Jake Wachs
 * Date: 10/29/2017
 *
 * The University of Alabama
 *
 * This file serves as the implementation for the red-black tree interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "rbt.h"
#include "bst.h"
#include "queue.h"

struct rbt {
    struct bst *tree;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);
};

typedef struct RBTNODE RBTNODE;
struct RBTNODE {
  int frequency;
  char color;
  char *value;
};

static void swapRBTNODE(void *, void *);
/***************************** Private Functions ******************************/
/* Compare two bst structs, returns true if the same */
static bool nodesAreEqual(BSTNODE *s1, BSTNODE *s2) {
  if (s1 && s2) {
    if (getBSTNODE(s1) && getBSTNODE(s2)) {
      if (getBSTNODE(s1) == getBSTNODE(s2)) return true;
    }
  }

  return false;
}

static BSTNODE *getBSTNODEUncle(BSTNODE *node) {
  BSTNODE *parent = NULL;
  BSTNODE *grandParent = NULL;
  if (getBSTNODEparent(node)) parent = getBSTNODEparent(node);
  if (getBSTNODEparent(parent)) grandParent = getBSTNODEparent(parent);

  if (grandParent) {
    if (nodesAreEqual(getBSTNODEleft(grandParent), node)) {
      if (getBSTNODEright(grandParent) != NULL) return getBSTNODEright(grandParent);
    }
    else {
      if (getBSTNODEright(grandParent) != NULL) return getBSTNODEleft(grandParent);
    }
  }

  return NULL;
}

static BSTNODE *getGrandParent(BSTNODE *node) {
  if (getBSTNODEparent(node))
    if (getBSTNODEparent(getBSTNODEparent(node))) {
      return getBSTNODEparent(getBSTNODEparent(node));
    }

    return NULL;
}

static BSTNODE *getSibling(BSTNODE *node) {
  if (getBSTNODEparent(node) && getBSTNODEleft(getBSTNODEparent(node))) {
    if (nodesAreEqual(node, getBSTNODEleft(getBSTNODEparent(node)))) {
      if (getBSTNODEright(getBSTNODEparent(node))) return getBSTNODEright(getBSTNODEparent(node));
    }
  }
  else if (getBSTNODEparent(node) && getBSTNODEright(getBSTNODEparent(node))) {
    if (nodesAreEqual(node, getBSTNODEright(getBSTNODEparent(node)))) {
      if (getBSTNODEleft(getBSTNODEparent(node))) return getBSTNODEleft(getBSTNODEparent(node));
    }
  }

  return NULL;
}

static BSTNODE *getNephew(BSTNODE *node) {
  BSTNODE *uncle = getBSTNODEUncle(node);
  if (nodesAreEqual(node, getBSTNODEleft(getBSTNODEparent(node)))) {
    return getBSTNODEright(uncle);
  }
  else {
    return getBSTNODEleft(uncle);
  }
}

static BSTNODE *getNiece(BSTNODE *node) {
  BSTNODE *uncle = getBSTNODEUncle(node);
  if (nodesAreEqual(node, getBSTNODEleft(getBSTNODEparent(node)))) {
    return getBSTNODEleft(uncle);
  }
  else {
    return getBSTNODEright(uncle);
  }
}

static bool nodesAreLinear(BSTNODE *x, BSTNODE *parent) {
  BSTNODE *grandParent = getBSTNODEparent(parent);

  if (nodesAreEqual(x, getBSTNODEleft(parent))) {
    if (nodesAreEqual(parent, getBSTNODEleft(grandParent))) {
      return true;
    }
  }
  if (nodesAreEqual(x, getBSTNODEright(parent))) {
    if (nodesAreEqual(parent, getBSTNODEright(grandParent))) {
      return true;
    }
  }

  return false;
}

static void leftRotate(BST *tree, BSTNODE *x) {
  BSTNODE *y = getBSTNODEright(x);

  setBSTNODEright(x, getBSTNODEleft(y));
  setBSTNODEparent(getBSTNODEleft(y), x);
  setBSTNODEparent(y, getBSTNODEparent(x));

  if (getBSTNODEparent(x) == NULL) {
    setBSTroot(tree, y);
  }
  /* x = x->parent->left */
  else if (nodesAreEqual(x, getBSTNODEleft(getBSTNODEparent(x)))) {
    setBSTNODEleft(getBSTNODEparent(x), y);
  }
  else {
    setBSTNODEright(getBSTNODEparent(x), y);
  }

  setBSTNODEleft(y, x);
  setBSTNODEparent(x, y);
}

static void rightRotate(BST *tree, BSTNODE *x) {
  BSTNODE *y = getBSTNODEleft(x);

  setBSTNODEleft(x, getBSTNODEright(y));
  setBSTNODEparent(getBSTNODEparent(y), x);
  setBSTNODEparent(y, getBSTNODEparent(x));

  if (getBSTNODEparent(x) == NULL) {
    setBSTroot(tree, y);
  }
  else if (nodesAreEqual(x, getBSTNODEright(getBSTNODEparent(x)))) {
    setBSTNODEright(getBSTNODEparent(x), y);
  }
  else {
    setBSTNODEleft(getBSTNODEparent(x), y);
  }

  setBSTNODEright(y, x);
  setBSTNODEparent(x, y);
}

static void rotate(BST *tree, BSTNODE *x, BSTNODE *parent) {
  if (nodesAreEqual(x, getBSTNODEleft(parent))) {
    rightRotate(tree, x);
  }
  else {
    leftRotate(tree, x);
  }
}

static void insertionFixUp(BST *tree, BSTNODE *x) {
  //BSTNODE *node = getBSTNODE(x);
  BSTNODE *parent = NULL;
  BSTNODE *grandParent = NULL;
  BSTNODE *uncle = NULL;

  RBTNODE *rbtParent = NULL;
  RBTNODE *rbtGrandParent = NULL;
  RBTNODE *rbtUncle = NULL;

  if (getBSTNODEparent(x)) {
    parent = getBSTNODEparent(x);
    if (getGrandParent(x)) {
      grandParent = getGrandParent(x);
      if (getBSTNODEUncle(x))
        uncle = getBSTNODEUncle(x);
    }
  }

  bool loop = true;
  while (loop) {
    if (parent) rbtParent = getBSTNODE(parent);
    if (grandParent) rbtGrandParent = getBSTNODE(grandParent);
    if (uncle) rbtUncle = getBSTNODE(uncle);


    if (nodesAreEqual(x, getBSTroot(tree))) break;
    if (rbtParent->color == 'B') break;
    if (rbtUncle->color == 'R' || uncle == NULL) {
      rbtParent->color = 'B';
      rbtUncle->color = 'B';
      rbtGrandParent->color = 'R';
      x = getGrandParent(x);                //FIXME: might need to set() this
    }
    else {
      if (nodesAreLinear(x, getBSTNODEparent(x)) == false) {
        BSTNODE *oldPar = getBSTNODEparent(x);   //These 2 assigns preserve the needed values
        BSTNODE *oldx = x;

        /* Rotate x to parent */
        rotate(tree, x, oldPar);

        x = oldPar;
        parent = oldx;

      }

      rbtParent->color = 'B';
      rbtGrandParent->color = 'R';

      /* Rotate parent to grandparent */
      rotate(tree, parent, grandParent);

      break;
    }
  }

  RBTNODE *rbtRoot = getBSTNODE(getBSTroot(tree));
  rbtRoot->color = 'B';
}

static void deletionFixUp(BST *tree, BSTNODE *x) {
  BSTNODE *parent = NULL;
//  BSTNODE *grandParent = getGrandParent(x);
//  BSTNODE *uncle = getBSTNODEUncle(x);
  BSTNODE *sibling = NULL;
  BSTNODE *nephew = NULL;
  BSTNODE *niece = NULL;

  RBTNODE *rbtParent = NULL;
  RBTNODE *rbtSibling = NULL;
  RBTNODE *rbtNephew = NULL;
  RBTNODE *rbtNiece = NULL;

  if (getBSTNODEparent(x)) {
    parent = getBSTNODEparent(x);
    if (getSibling(x)) {
      sibling = getSibling(x);
      if (getGrandParent(x)) {
        if (getBSTNODEUncle(x)) {
          if (getNephew(x)) nephew = getNephew(x);
          if (getNiece(x)) niece = getNiece(x);
        }
      }
    }
  }

  bool loop = true;
  while (loop) {
    rbtParent = getBSTNODE(parent);
    rbtSibling = getBSTNODE(sibling);
    rbtNephew = getBSTNODE(nephew);
    rbtNiece = getBSTNODE(niece);

    if (nodesAreEqual(getBSTroot(tree), x)) break;
    RBTNODE *rbtX = getBSTNODE(x);
    if (rbtX->color == 'R' || x == NULL) break;
    if (rbtSibling->color == 'R' || sibling == NULL) {
      rbtParent->color = 'R';
      rbtSibling->color = 'B';

      rotate(tree, sibling, getBSTNODEparent(sibling));
    }
    else if (rbtNephew->color == 'R' || nephew == NULL) {
      rbtSibling->color = rbtParent->color;
      rbtParent->color = 'B';
      rbtNephew->color = 'B';

      rotate(tree, sibling, getBSTNODEparent(sibling));

      break;
    }
    else if (rbtNiece->color == 'R' || niece == NULL) {
      rbtNiece->color = 'B';
      rbtSibling->color = 'R';

      rotate(tree, niece, getBSTNODEparent(niece));
    }
    else {
      rbtSibling->color = 'R';
      x = parent;
    }
  }
  //setRBTNODEcolor(getBSTNODE(x), 'B');   //FIXME: this should be outside the loop, there might be a screwed up bracket
  RBTNODE *xx = getBSTNODE(x);
  xx->color = 'B';
}
/******************************************************************************/

RBT *newRBT(
  void (*d)(FILE *, void *),
  int (*c)(void *, void *)
)
{
    RBT *t = malloc(sizeof(struct rbt));
    t->tree = newBST(d, c, swapRBTNODE);           //FIXME: init with swapper function, change other fc's to use swapper function
    t->display = d;
    t->comparator = c;

    return t;
}

void insertRBT(RBT *t, void *value) {
  BSTNODE *x = insertBST(t->tree, value);
  if (x == NULL) {
    BSTNODE *newNode = findBST(t->tree, value);
    //incrementRBTNODEfrequency(newNode);
    RBTNODE *n = getBSTNODE(newNode);
    n->frequency += 1;
  }
  else {
    insertionFixUp(t->tree, x);
    //incrementRBTNODEfrequency(getBSTNODE(x));   //FIXME: idk if this is in the right spot...
    RBTNODE *xx = getBSTNODE(x);
    xx->frequency += 1;
  }
}

int findRBT(RBT *t, void *value) {
  RBTNODE *p = getBSTNODE(findBST(t->tree, value));

  /* Value is not in the tree */
  if (p == NULL) {
    return 0;
  }
  else {
    return p->frequency;
  }
}

void deleteRBT(RBT *t, void *value) {
  BSTNODE *valToDelete = findBST(t->tree, value);

  if (valToDelete != NULL) {
    RBTNODE *rbtToDelete = getBSTNODE(valToDelete);
    rbtToDelete->frequency -= 1;

    if (rbtToDelete->frequency == 0) {        //FIXME: should this remove occur here
      swapToLeafBST(t->tree, valToDelete);
      deletionFixUp(t->tree, valToDelete);
      pruneLeafBST(t->tree, valToDelete);         //FIXME: is this block right?
    }
  }
}

int sizeRBT(RBT *t) {
  return sizeBST(t->tree);
}

int wordsRBT(RBT *t) {
  //returns the number of words, including duplicates, in the tree
}

void statisticsRBT(FILE *fp, RBT *t) {
  //prints statistics to fp
}

void displayRBT(FILE *fp, RBT *t) {
  //just use displalyBST?
  displayBST(fp, t->tree);
}

static void swapRBTNODE(void *n1, void *n2) {
  RBTNODE *ra = getBSTNODE(n1);
  RBTNODE *rb = getBSTNODE(n2);

  void *vtemp = ra->value;
  ra->value = rb->value;
  rb->value = vtemp;

  int ctemp = ra->frequency;
  ra->frequency = rb->frequency;
  rb->frequency = ctemp;
}
