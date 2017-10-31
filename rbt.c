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
#include "phrase.h"

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

static void insertionFixUp(BST *tree, BSTNODE *x) {
  //BSTNODE *node = getBSTNODE(x);
  BSTNODE *parent = getBSTNODEparent(x);
  BSTNODE *grandParent = getGrandParent(x);
  BSTNODE *uncle = getBSTNODEUncle(x);

  bool loop = true;
  while (loop) {

    if (nodesAreEqual(x, getBSTroot(tree))) break;
    if (getPHRASEcolor(getBSTNODE(parent)) == 'b') break;
    if (getPHRASEcolor(getBSTNODE(uncle)) == 'r' || uncle == NULL) {
      setPHRASEcolor(getBSTNODE(parent), 'b');
      setPHRASEcolor(getBSTNODE(uncle), 'b');
      setPHRASEcolor(getBSTNODE(grandParent), 'r');
      x = getGrandParent(x);                //FIXME: might need to set() this
    }
    else {
      if (nodesAreLinear(x, getBSTNODEparent(x)) == false) {
        BSTNODE *oldPar = parent;   //These 2 assigns preserve the needed values
        BSTNODE *oldx = x;
        /* Rotate x to parent */
        if (nodesAreEqual(x, getBSTNODEleft(oldPar))) {
          rightRotate(tree, x);
        }
        else {
          leftRotate(tree, x);
        }
        x = oldPar;
        parent = oldx;

      }

      setPHRASEcolor(getBSTNODE(parent), 'b');
      setPHRASEcolor(getBSTNODE(grandParent), 'r');

      /* Rotate parent to grandparent */
      if (nodesAreEqual(parent, getBSTNODEleft(grandParent))) {
        rightRotate(tree, parent);
      }
      else {
        leftRotate(tree, parent);
      }

      break;
    }
  }

  setPHRASEcolor(getBSTNODE(getBSTroot(tree)), 'b');
}

static void deletionFixUp(BST *tree, BSTNODE *x) {
  BSTNODE *parent = getBSTNODEparent(x);
  BSTNODE *grandParent = getGrandParent(x);
  BSTNODE *uncle = getBSTNODEUncle(x);
  BSTNODE *sibling = getSibling(x);
  BSTNODE *nephew = getNephew(x);
  BSTNODE *niece = getNiece(x);

  bool loop = true;
  while (loop) {
    if (nodesAreEqual(getBSTroot(tree), x)) break;
    if (getPHRASEcolor(getBSTNODE(x)) == 'r') break;
    if (getPHRASEcolor(getBSTNODE(sibling)) == 'r' || sibling == NULL) {
      setPHRASEcolor(getBSTNODE(parent), 'r');
      setPHRASEcolor(getBSTNODE(sibling), 'b');
      if (nodesAreEqual(sibling, getBSTNODEleft(parent))) {
        rightRotate(tree, sibling);
      }
      else {
        leftRotate(tree, sibling);
      }
    }
    else if (getPHRASEcolor(getBSTNODE(nephew)) == 'r') {
      setPHRASEcolor(getBSTNODE(sibling), getPHRASEcolor(getBSTNODE(parent)));
      //color parent black
      setPHRASEcolor(getBSTNODE(parent), 'b');
      //color nephew black
      setPHRASEcolor(getBSTNODE(nephew), 'b');
      //rotate sibling to parent
      if (nodesAreEqual(sibling, getBSTNODEleft(parent))) {
        rightRotate(tree, sibling);
      }
      else {
        leftRotate(tree, sibling);
      }

      break;
    }
    else if (getPHRASEcolor(getBSTNODE(niece)) == 'r') {
      //color niece black
      setPHRASEcolor(getBSTNODE(niece), 'b');
      //color sibling red
      setPHRASEcolor(getBSTNODE(sibling), 'r');
      //rotate niece to sibling
      if (nodesAreEqual(niece, getBSTNODEleft(sibling))) {
        rightRotate(tree, niece);
      }
      else {
        leftRotate(tree, niece);
      }
    }
    else {
      //color sibling red
      setPHRASEcolor(getBSTNODE(sibling), 'r');
      x = parent;
    }
  }
  setPHRASEcolor(getBSTNODE(x), 'b');   //FIXME: this should be outside the loop, there might be a screwed up bracket
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

int findRBT(RBT *t, void *value) {
  PHRASE *p = getBSTNODE(findBST(t->tree, value));

  /* Value is not in the tree */
  if (p == NULL) {
    return 0;
  }
  else {
    return getPHRASEfrequency(p);
  }
}

void deleteRBT(RBT *t, void *value) {
  BSTNODE *valToDelete = findBST(t->tree, value);
  if (valToDelete == NULL) {
    //what to do? the value to be deleted is not here?
  }
  swapToLeafBST(t->tree, valToDelete);
  deletionFixUp(t->tree, valToDelete);

}
