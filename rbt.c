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

#include "rbt.h"
#include "bst.h"

struct rbt {
    struct bst *tree;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);
};

/***************************** Private Functions ******************************/
/* Compare two bst structs, returns true if the same */
static bool nodesAreEqual(BSTNODE *s1, BSTNODE *s2) {
  if (s1 && s2) {
    if (getBSTNODE(s1) && getBSTNODE(s2)) {
      if (getBSTNODE(s1) == getBSTNODE(s2) && getBSTNODE(getBSTNODEleft(s1)) == getBSTNODE(getBSTNODEleft(s2))) {
        if (getBSTNODE(getBSTNODEright(s1)) == getBSTNODE(getBSTNODEright(s2)) && getBSTNODE(getBSTNODEparent(s1)) == getBSTNODE(getBSTNODEparent(s2))) {
          return true;
        }
      }
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

static void insertionFixUp(BST *tree, BSTNODE *x) {
  bool loop = true;
  while (loop) {
    if (nodesAreEqual(x, getBSTroot(tree))) break;
    if (getBSTNODE(getBSTNODEparent(x))->color == "black") break;
    if (getBSTNODE(getBSTNODEUncle(x))->color == "red") {
      getBSTNODE(getBSTNODEparent(x))->color = "black";
      getBSTNODE(getBSTNODEUncle(x))->color = "black";
      getBSTNODE(getGrandParent(x))->color = "red";
      x = getGrandParent(x);
    }
    else {
      //If x and parent are not linear
      /* If x is the left child of its parent */
      if (nodesAreLinear(x, getBSTNODEparent(x)) == false) {
        //rotate x to parent
        //x = old parent
        //parent = old x
      }

      //color parent black
      //color grandParent red
      //rotate parent to grandParent
      //exit the loop
    }
  }

  getBSTNODE(getBSTroot(tree))->color = black;
}
/******************************************************************************/
RBT *newRBT(
  void (*d)(FILE *, void *),
  int (*c)(void *, void *)
)
{
    RBT *t = malloc(sizeof(struct rbt));
    t->tree = newBST(d, c, NULL);
    t->display = d;
    t->comparator = c;

    return t;
}

void insertRBT(RBT *t, void *value) {
  BSTNODE *x = insertBST(t->tree, value);
  insertionFixUp(t->tree, x);
}
