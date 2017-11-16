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

#include "real.h"
#include "rbt.h"
#include "bst.h"
#include "queue.h"



typedef struct RBTNODE RBTNODE;



/*** RBTNODE Functions ***/
static RBTNODE *newRBTNODE(void *, void (*)(FILE *, void *), int (*)(void *, void *));
static void displayRBTNODE(FILE *, void *);
static void swapRBTNODE(BSTNODE *, BSTNODE *);
static int compareRBTNODE(void *, void *);
static char getColor(BSTNODE *);
static void setColor(BSTNODE *, char);

/*** Min/Max Functions ***/
static int min(int, int);
static int findMinDepthRBT(BSTNODE *);
static int findMaxDepthRBT(BSTNODE *);

/*** Rotate Functions ***/
static bool nodesAreEqual(BSTNODE *, BSTNODE *);
static bool isLeftChild(BSTNODE *);
static bool nodesAreLinear(BSTNODE *, BSTNODE *);
static void leftRotate(BST *, BSTNODE *);
static void rightRotate(BST *, BSTNODE *);
static void rotate(BST *, BSTNODE *, BSTNODE *);

/*** Relationship Functions ***/
static BSTNODE *getSibling(BSTNODE *);
static BSTNODE *getUncle(BSTNODE *);
static BSTNODE *getGrandParent(BSTNODE *);
static BSTNODE *getNephew(BSTNODE *);
static BSTNODE *getNiece(BSTNODE *);

/*** Fixup Routine Functions ***/
static void insertionFixUp(BST *, BSTNODE *);
static void deletionFixUp(BST *, BSTNODE *);




struct rbt {
    struct bst *tree;
    int totalWords;
    void (*display)(FILE *, void *);
    int (*comparator)(void *, void *);
};

struct RBTNODE {
  int frequency;
  char color;
  void *value;    // Holds STRING/REAL/INTEGER
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};




/******************************************************************************/
/***                              Public Chunk                              ***/
/******************************************************************************/
RBT *newRBT(
  void (*d)(FILE *, void *),
  int (*c)(void *, void *)
)
{
    RBT *t = malloc(sizeof(struct rbt));
    t->tree = newBST(displayRBTNODE, compareRBTNODE, swapRBTNODE);
    t->display = d;
    t->comparator = c;
    t->totalWords = 0;

    return t;
}

void insertRBT(RBT *t, void *value) {
  RBTNODE *nodeToInsert = newRBTNODE(value, t->display, t->comparator);

  BSTNODE *find = findBST(t->tree, nodeToInsert);

  /* If already in the tree, just increment it */
  if (find) {
    RBTNODE *foundNode = getBSTNODE(find);
    foundNode->frequency += 1;
  }
  else {
    insertBST(t->tree, nodeToInsert);
    BSTNODE *insertedNode = findBST(t->tree, nodeToInsert);
    insertionFixUp(t->tree, insertedNode);

  }
  t->totalWords += 1;
}

int findRBT(RBT *t, void *value) {
  RBTNODE *valueNode = newRBTNODE(value, t->display, t->comparator);
  RBTNODE *p = getBSTNODE(findBST(t->tree, valueNode));

  /* Value is not in the tree */
  if (p == NULL) {
    return 0;
  }
  else {
    return p->frequency;
  }
}


void deleteRBT(RBT *t, void *value) {
  RBTNODE *nodeToDelete = newRBTNODE(value, t->display, t->comparator);

  BSTNODE *find = findBST(t->tree, nodeToDelete);

  /* As long as it's in the tree, delete value */
  if (find != NULL) {
    RBTNODE *decrementNode = getBSTNODE(find);
    decrementNode->frequency -= 1;

    if (decrementNode->frequency <= 0) {
      BSTNODE *leaf = swapToLeafBST(t->tree, find);
      deletionFixUp(t->tree, leaf);
      pruneLeafBST(t->tree, leaf);
    }
    t->totalWords -= 1;
  }
}

int sizeRBT(RBT *t) {
  return sizeBST(t->tree);
}

int wordsRBT(RBT *t) {
  return t->totalWords;     //returns the number of words, including duplicates, in the tree
}

void statisticsRBT(FILE *fp, RBT *t) {
  fprintf(fp, "Words/Phrases: %d\n", t->totalWords);
  fprintf(fp, "Nodes: %d\n", sizeBST(t->tree));
  fprintf(fp, "Minimum Depth: %d\n", findMinDepthRBT(getBSTroot(t->tree)));    //FIXME: figure it out
  fprintf(fp, "Maximum Depth: %d", findMaxDepthRBT(getBSTroot(t->tree)));    //FIXME: figure it out

}

void displayRBT(FILE *fp, RBT *t) {
  displayBST(fp, t->tree);
}
/******************************************************************************/
/***                          End Public Chunk                              ***/
/******************************************************************************/










/******************************************************************************/
/***                          RBTNODE Functions                             ***/
/******************************************************************************/
static RBTNODE *newRBTNODE(void *value, void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  RBTNODE *node = malloc(sizeof(struct RBTNODE));
  node->frequency = 1;
  node->color = 'R';
  node->value = value;
  node->display = d;
  node->comparator = c;

  return node;
}

static void displayRBTNODE(FILE *fp, void *value) {
  RBTNODE *node = value;
  node->display(fp, node->value);

  if (node->frequency > 1) {
    fprintf(fp, "-%d", node->frequency);
  }
  fprintf(fp, "-");
  fprintf(fp, "%c", node->color);
  //if (getBSTNODEleft(node)) printf(" has left child");
  //if (getBSTNODEright(node)) printf(" has right child");
}

static void swapRBTNODE(BSTNODE *n1, BSTNODE *n2) {
  RBTNODE *ra = getBSTNODE(n1);
  RBTNODE *rb = getBSTNODE(n2);

  void *vtemp = ra->value;
  ra->value = rb->value;
  rb->value = vtemp;

  int ctemp = ra->frequency;
  ra->frequency = rb->frequency;
  rb->frequency = ctemp;
}

static int compareRBTNODE(void *v1, void *v2) {
  RBTNODE *node1 = v1;
  RBTNODE *node2 = v2;

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

static char getColor(BSTNODE *node) {
  if (node == NULL)
    return 'B';
  else {
    RBTNODE *valNode = getBSTNODE(node);
    return valNode->color;
  }

}

static void setColor(BSTNODE *node, char color) {
  if (node == NULL)
    return;

  RBTNODE *valNode = getBSTNODE(node);

  valNode->color = color;
}


/******************************************************************************/
/***                          Min/Max Functions                             ***/
/******************************************************************************/
static int min(int a, int b) {
    if (a < b) return a;
    else if (a > b) return b;
    else {
      return a;
    }
}

static int findMinDepthRBT(BSTNODE *root) {
  if (root == NULL) {
    return 0;
  }
  if (getBSTNODEleft(root) == NULL && getBSTNODEright(root) == NULL) {
    return 1;
  }
  if (!getBSTNODEleft(root)) {
    return findMinDepthRBT(getBSTNODEright(root)) + 1;
  }
  if (!getBSTNODEright(root)) {
    return findMinDepthRBT(getBSTNODEleft(root)) + 1;
  }

  return min(findMinDepthRBT(getBSTNODEleft(root)), findMinDepthRBT(getBSTNODEright(root))) + 1;
}

static int findMaxDepthRBT(BSTNODE *root) {
  if (root == NULL) return 0;
  else {
    int L_depth = findMaxDepthRBT(getBSTNODEleft(root));
    int R_depth = findMaxDepthRBT(getBSTNODEright(root));

    if (L_depth > R_depth) {
      return L_depth + 1;
    }
    else return R_depth + 1;
  }
}



/******************************************************************************/
/***                          Rotate Functions                              ***/
/******************************************************************************/
static bool nodesAreEqual(BSTNODE *n1, BSTNODE *n2) {
  if (n1 == NULL) {
    if (n2 == NULL)
      return true;
    else
      return false;
  }
  if (n2 == NULL)
    return false;

  RBTNODE *node1 = getBSTNODE(n1);
  RBTNODE *node2 = getBSTNODE(n2);

  if (node1->comparator(node1->value, node2->value) == 0)
    return true;
  else
    return false;
}

static bool isLeftChild(BSTNODE *x) {
  BSTNODE *parent = getBSTNODEparent(x);

  if (nodesAreEqual(getBSTNODEleft(parent), x))
    return true;
  else
    return false;
}

static bool nodesAreLinear(BSTNODE *x, BSTNODE *parent) {
  if (isLeftChild(parent) && isLeftChild(x))
    return true;
  else if (!isLeftChild(parent) && !isLeftChild(x))
    return true;
  else
    return false;
}

static void leftRotate(BST *tree, BSTNODE *x) {
  BSTNODE *y = getBSTNODEright(x);
  BSTNODE *root = getBSTroot(tree);

  if (nodesAreEqual(x, root)) {
    //printf("root rotate\n");
    setBSTNODEparent(y, y);
    setBSTNODEparent(getBSTNODEleft(y), x);
    setBSTNODEright(x, getBSTNODEleft(y));
    setBSTNODEleft(y, x);
    setBSTNODEparent(x, y);
    setBSTroot(tree, y);
  }
  else if (nodesAreEqual(x, getBSTNODEright(getBSTNODEparent(x)))) {
    setBSTNODEright(getBSTNODEparent(x), y);
    setBSTNODEparent(y, getBSTNODEparent(x));
    setBSTNODEright(x, getBSTNODEleft(y));
    setBSTNODEparent(getBSTNODEleft(y), x);
    setBSTNODEleft(y, x);
    setBSTNODEparent(x, y);
  }
  else {
    setBSTNODEleft(getBSTNODEparent(x), y);
    setBSTNODEparent(y, getBSTNODEparent(x));
    setBSTNODEright(x, getBSTNODEleft(y));
    setBSTNODEparent(getBSTNODEleft(y), x);
    setBSTNODEleft(y, x);
    setBSTNODEparent(x, y);
  }
/*
  BSTNODE *y = getBSTNODEright(x);
  setBSTNODEright(x, getBSTNODEleft(y));

  if (getBSTNODEleft(y) != NULL) {
    //y->left->parent = x
    setBSTNODEparent(getBSTNODEleft(y), x);
  }

  //y->parent = x->parent
  setBSTNODEparent(y, getBSTNODEparent(x));

  if (nodesAreEqual(x, getBSTNODEparent(x))) {
    // root = y
    setBSTroot(tree, y);
  }
  else if (nodesAreEqual(x, getBSTNODEleft(getBSTNODEparent(x)))) {
    //x->parent->left = y
    setBSTNODEleft(getBSTNODEparent(x), y);
  }
  else {
    // x->parent->right = y
    setBSTNODEright(getBSTNODEparent(x), y);
  }

  setBSTNODEleft(y, x);


  setBSTNODEparent(x, y);
*/
}

static void rightRotate(BST *tree, BSTNODE *x) {
  BSTNODE *y = getBSTNODEleft(x);
  BSTNODE *root = getBSTroot(tree);

  if (nodesAreEqual(x, root)) {
    setBSTNODEparent(y, y);
    setBSTNODEparent(getBSTNODEright(y), x);
    setBSTNODEleft(x, getBSTNODEright(y));
    setBSTNODEright(y, x);
    setBSTNODEparent(x, y);
    setBSTroot(tree, y);
  }
  else if (nodesAreEqual(x, getBSTNODEleft(getBSTNODEparent(x)))) {
    setBSTNODEleft(getBSTNODEparent(x), y);
    setBSTNODEparent(y, getBSTNODEparent(x));
    setBSTNODEleft(x, getBSTNODEright(y));
    setBSTNODEparent(getBSTNODEright(y), x);
    setBSTNODEright(y, x);
    setBSTNODEparent(x, y);
  }
  else {
    setBSTNODEright(getBSTNODEparent(x), y);
    setBSTNODEparent(y, getBSTNODEparent(x));
    setBSTNODEleft(x, getBSTNODEright(y));
    setBSTNODEparent(getBSTNODEright(y), x);
    setBSTNODEright(y, x);
    setBSTNODEparent(x, y);
  }
/*
  BSTNODE *y = getBSTNODEleft(x);
  setBSTNODEleft(x, getBSTNODEright(y));

  if (getBSTNODEright(y) != NULL) {
    setBSTNODEparent(getBSTNODEright(y), x);
  }

  setBSTNODEparent(y, getBSTNODEparent(x));

  if (nodesAreEqual(x, getBSTNODEparent(x))) {
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
*/
}


static void rotate(BST *tree, BSTNODE *x, BSTNODE *parent) {
  if (nodesAreEqual(x, getBSTNODEleft(parent))) {
    rightRotate(tree, parent);
  }
  else {
    leftRotate(tree, parent);
  }
}




/******************************************************************************/
/***                        Relationship Functions                          ***/
/******************************************************************************/
static BSTNODE *getSibling(BSTNODE *node) {
  if (node == NULL)
    return NULL;

  BSTNODE *parent = getBSTNODEparent(node);

  // If node is root
  if (nodesAreEqual(parent, node))
    return NULL;

  // If node is right child
  if (nodesAreEqual(node, getBSTNODEright(parent)))
    return getBSTNODEleft(parent);
  else
    return getBSTNODEright(parent);
}

static BSTNODE *getUncle(BSTNODE *node) {
  if (node == NULL)
    return NULL;

  BSTNODE *parent = getBSTNODEparent(node);

  // If node is root
  if (nodesAreEqual(parent, node))
    return NULL;

  return getSibling(parent);
}

static BSTNODE *getGrandParent(BSTNODE *node) {
  if (node == NULL)
    return NULL;

  BSTNODE *parent = getBSTNODEparent(node);

  // Node is root
  if (nodesAreEqual(parent, node))
    return NULL;
  // Parent is root
  if (nodesAreEqual(parent, getBSTNODEparent(parent)))
    return NULL;

  return getBSTNODEparent(parent);
}

static BSTNODE *getNephew(BSTNODE *node) {
  if (node == NULL)
    return NULL;

  if (isLeftChild(node))
    return getBSTNODEright(getSibling(node));
  else
    return getBSTNODEleft(getSibling(node));
}

static BSTNODE *getNiece(BSTNODE *node) {
  if (node == NULL)
    return NULL;

  if (isLeftChild(node))
    return getBSTNODEleft(getSibling(node));
  else
    return getBSTNODEright(getSibling(node));
}



/******************************************************************************/
/***                        Fixup Routine Functions                         ***/
/******************************************************************************/
static void insertionFixUp(BST *t, BSTNODE *x) {
  while (1) {
    BSTNODE *parent = getBSTNODEparent(x);
    BSTNODE *uncle = getUncle(x);
    BSTNODE *grandParent = getGrandParent(x);

    // If x is the root, break
    if (nodesAreEqual(x, parent))
      break;
    if (getColor(parent) == 'B')
      break;

    if (getColor(uncle) == 'R') {
      setColor(parent, 'B');
      setColor(uncle, 'B');
      setColor(grandParent, 'R');

      x = grandParent;
      //setBSTNODE(x, getBSTNODE(grandParent));
    }
    else {

      //if x and parent are not linear
      if (!nodesAreLinear(x, parent)) {
        BSTNODE *oldparent = parent;
        //BSTNODE *oldparent;
        //setBSTNODE(oldparent, getBSTNODE(parent));
        BSTNODE *oldx = x;
        //setBSTNODE(oldx, getBSTNODE(x));

        rotate(t, x, parent);           //FIXME: this rotate is where it's segfaulting

        //setBSTNODE(x, getBSTNODE(oldparent));
        //setBSTNODE(parent, getBSTNODE(oldx));
        x = oldparent;
        parent = oldx;
      }

      setColor(parent, 'B');
      setColor(grandParent, 'R');

      rotate(t, parent, grandParent);

      break;
    }
  }
  //color root black
  BSTNODE *root = getBSTroot(t);
  setColor(root, 'B');
}

static void deletionFixUp(BST *t, BSTNODE *x) {
  while (1) {
    BSTNODE *parent = getBSTNODEparent(x);
    BSTNODE *sibling = getSibling(x);
    BSTNODE *niece = getNiece(x);
    BSTNODE *nephew = getNephew(x);

    // If x is the root, break
    if (nodesAreEqual(x, parent))
      break;

    if (getColor(x) == 'R')
      break;

    if (getColor(sibling) == 'R') {
      setColor(parent, 'R');
      setColor(sibling, 'B');
      rotate(t, sibling, parent);
    }
    else if (getColor(nephew) == 'R') {
      setColor(sibling, getColor(parent));
      setColor(parent, 'B');
      setColor(nephew, 'B');
      rotate(t, sibling, parent);
      break;
    }
    else if (getColor(niece) == 'R') {
      setColor(niece, 'B');
      setColor(sibling, 'R');
      rotate(t, niece, sibling);
    }
    else {
      setColor(sibling, 'R');
      x = parent;
    }
  }
  setColor(x, 'B');
}
