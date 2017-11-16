/*
 * Author: Jake Wachs
 * Date: 10/25/2017
 * The University of Alabama
 *
 * This is the implementation file for the bst.h inteface
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "real.h"
#include "string.h"
#include "bst.h"
#include "queue.h"

struct bstnode {
  bool isLeftChild;
  void *value;      //points to a gtnode or rbtnode
  struct bstnode *parent;
  struct bstnode *left;
  struct bstnode *right;
};

/******************* Helper function signatures *******************************/
static void displayNODE(BST *, FILE *, BSTNODE *, bool);
static BSTNODE *insertHelper(BST *, BSTNODE *, BSTNODE *, void *, bool);
static BSTNODE *findHelper(BSTNODE *, int (*)(void *, void *), void *);
//static BSTNODE *traverseRight(BST *, BSTNODE *, bool);
//static BSTNODE *traverseLeft(BST *, BSTNODE *, bool);
static bool isLeaf(BSTNODE *);
static void displayHelper(FILE *fp, BSTNODE *root, BST *t);
static BSTNODE *copyNODE(BSTNODE *giver);
static int findMinDepthBST(BSTNODE *root);
static int findMaxDepthBST(BSTNODE *root);
//static int min(int, int);


/******************************************************************************/
/***                           BSTNODE Functions                            ***/
/******************************************************************************/
static BSTNODE *newBSTNODE(void *value, BSTNODE *parent) {
  BSTNODE *node;
  if (value == NULL) node = NULL;
  else {
    node = (struct bstnode *)malloc(sizeof(struct bstnode));
    node->value = value;
    node->parent = parent;
    node->left = node->right = NULL;
  }

  return node;
}

void *getBSTNODE(BSTNODE *n) {
  if (!n) return NULL;
  return n->value;
}

void setBSTNODE(BSTNODE *n, void *value) {
  n->value = value;
}

BSTNODE *getBSTNODEleft(BSTNODE *n) {
  if (n == NULL) return NULL;
  if (!n->left) return NULL;
  return n->left;
}

void setBSTNODEleft(BSTNODE *n, BSTNODE *replacement) {
  n->left = replacement;
/*
  if (n) printf("n is good\n");
  if (n->left) printf("n->left is good\n");
  if (replacement != NULL) {
    n->left->value = replacement->value;
    n->left->parent = replacement->parent;
    n->left->left = replacement->left;
    n->left->right = replacement->right;
  }
  else {
    n = NULL;
  }
*/
}

BSTNODE *getBSTNODEright(BSTNODE *n) {
  if (n == NULL) return NULL;
  if (!n->right) return NULL;
  return n->right;
}

void setBSTNODEright(BSTNODE *n, BSTNODE *replacement) {
  n->right = replacement;
/*
  if (replacement != NULL) {
    n->right->value = replacement->value;
    n->right->parent = replacement->parent;
    n->right->left = replacement->left;
    n->right->right = replacement->right;
  }
  else {
    n = NULL;
  }
*/
}

BSTNODE *getBSTNODEparent(BSTNODE *n) {
  if (n == NULL) return NULL;
  if (!n->parent) return NULL;
  return n->parent;
}

void setBSTNODEparent(BSTNODE *n, BSTNODE *replacement) {
  n->parent = replacement;
/*
  n->parent->value = replacement->value;
  n->parent->parent = replacement->parent;
  n->parent->left = replacement->left;
  n->parent->right = replacement->right;
*/
}


/******************************************************************************/
/***                           BST Functions                                ***/
/******************************************************************************/
struct bst {
  struct bstnode *root;
  int size;
  int numWords;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
  void (*swapper)(BSTNODE *, BSTNODE *);
};

BST *newBST(
  void (*d)(FILE *, void *),
  int (*c)(void *, void *),
  void (*s)(BSTNODE *, BSTNODE *))
{

    BST *tree = malloc(sizeof(struct bst));
    tree->display = d;
    tree->comparator = c;
    tree->swapper = s;

    tree->root = newBSTNODE(NULL, tree->root);
    tree->size = 0;

    return tree;
}

void setBSTroot(BST *t, BSTNODE *replacement) {
  t->root->value = replacement->value;
  t->root->parent = replacement->parent;
  t->root->left = replacement->left;
  t->root->right = replacement->right;
}

BSTNODE *getBSTroot(BST *t) {
  if (!t) return NULL;
  if (!t->root) return NULL;

  return t->root;
}

BSTNODE *insertBST(BST *t, void *value) {
  t->numWords += 1;
  t->root = insertHelper(t, t->root, NULL, value, false);
  return t->root;
}

BSTNODE *findBST(BST *t, void *value) {
  if (t->size == 0) {
    return NULL;
  }
  else {
    return findHelper(t->root, t->comparator, value);
  }
}

BSTNODE *deleteBST(BST *t, void *value) {
  if (t->size == 0) {
    return NULL;
  }

  /* Must be root */
  if (t->size == 1) {
    BSTNODE *node1 = findBST(t, value);

    if (node1 == NULL) {
      printf("Value ");
      t->display(stdout, value);
      printf(" not found.\n");
    }

    BSTNODE *returnVal = copyNODE(node1);

    t->root = NULL;
    t->size -= 1;

    return returnVal;
  }

  BSTNODE *node = findBST(t, value);

  if (node == NULL) {
    printf("Value ");
    t->display(stdout, value);
    printf(" not found.\n");
  }

  node = swapToLeafBST(t, node);

  BSTNODE *returnNODE = copyNODE(node);

  pruneLeafBST(t, node);

  return returnNODE;
}

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {
  if (node == NULL)
    return NULL;

  if (t->swapper) {
    if (node->left) {
      t->swapper(node, node->left);
      node = swapToLeafBST(t, node->left);
    }
    else if (node->right) {
      t->swapper(node, node->right);
      node = swapToLeafBST(t, node->right);
    }
  }
  else {
    if (node->left) {
      void *tmp = node->value;
      node->value = node->left->value;
      node->left->value = tmp;
      node = swapToLeafBST(t, node->left);
    }
    else if (node->right) {
      void *tmp = node->value;
      node->value = node->right->value;
      node->right->value = tmp;
      node = swapToLeafBST(t, node->right);
    }
  }

  return node;
}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
  if (sizeBST(t) == 1) {
    t->root = NULL;
  }
  /* If left child */
  if (leaf->isLeftChild) {
    leaf->parent->left = NULL;
  }
  /* If right child */
  else {
    leaf->parent->right = NULL;
  }
  //setBSTNODE(leaf, NULL);
  //setBSTroot(t, newBSTNODE(NULL, NULL));

  t->size -= 1;
}

int sizeBST(BST *t) {
  return t->size;
}

void statisticsBST(FILE *fp, BST *t) {
  fprintf(fp, "Nodes: %d\n", t->size);
  fprintf(fp, "Minimum depth: %d\n", findMinDepthBST(t->root));
  fprintf(fp, "Maximum depth: %d\n", findMaxDepthBST(t->root));
}

void displayBST(FILE *fp, BST *t) {
  displayHelper(fp, t->root, t);
}


/******************************************************************************/
/***                           Helper Functions                             ***/
/******************************************************************************/
static void displayNODE(BST *t, FILE *fp, BSTNODE *node, bool isRoot) {
  t->display(fp, node->value);
  fprintf(fp, "(");
  t->display(fp, getBSTNODEparent(node)->value);
  fprintf(fp, ")-");

  if (!isRoot) {
    BSTNODE *parent = getBSTNODEparent(node);
    BSTNODE *parLeft = getBSTNODEleft(parent);
    void *nodeVal;
    void *parLeftVal;

    if(node)
      nodeVal = node->value;
    else
      nodeVal = NULL;

    if (parLeft)
      parLeftVal = parLeft->value;
    else
      parLeftVal = NULL;

    if (nodeVal == NULL) {
      if (parLeftVal == NULL) {
        fprintf(fp, "l");
        return;
      }
      else {
        fprintf(fp, "r");
        return;
      }
    }
    else {
      if (parLeftVal == NULL) {
        fprintf(fp, "r");
        return;
      }
    }

    if (t->comparator(nodeVal, parLeftVal) == 0)
      fprintf(fp, "l");
    else
      fprintf(fp, "r");
  }
}

static BSTNODE *insertHelper(BST *t, BSTNODE* root, BSTNODE *parent, void *value, bool isLeftChild) {
  if (root == NULL) {
    root = newBSTNODE(value, parent);
    root->isLeftChild = isLeftChild;

    if (parent == NULL)
      root->parent = root;

    t->size += 1;

    return root;
  }
  else if (t->comparator(value, root->value) < 0) {
    root->left = insertHelper(t, root->left, root, value, true);
  }
  else {
    root->right = insertHelper(t, root->right, root, value, false);
  }

  return root;
}

static BSTNODE *findHelper(BSTNODE *root, int (*comparator)(void *, void *), void *value) {
  //if (value->value) printf("FIND VALUE->VALUE IS NOT GOOD\n");
  if (root == NULL)
    return NULL;

  if (comparator(value, root->value) == 0) {
    return root;
  }
  else if (comparator(value, root->value) < 0) {
    if (getBSTNODEleft(root))
      return findHelper(getBSTNODEleft(root), comparator, value);
    else
      return NULL;
  }
  else {
    if (getBSTNODEright(root))
      return findHelper(getBSTNODEright(root), comparator, value);
    else
      return NULL;
  }
}

/*
static BSTNODE *traverseRight(BST *t, BSTNODE *node, bool useSwapper) {
  while (node->right) {
    if (useSwapper == true) {
      t->swapper(node, node->right);
    }
    else {
      //printf("swapping values %lf and %lf\n", getREAL(node->value), getREAL(node->right->value));
      void *tmp = node->value;
      node->value = node->right->value;
      node->right->value = tmp;
    }

    node = node->right;
  }

  return node;
}


static BSTNODE *traverseLeft(BST *t, BSTNODE *node, bool useSwapper) {
  while (node->left) {
    if (useSwapper == true) {
      t->swapper(node, node->left);
    }
    else {
      void *tmp = node->value;
      node->value = node->left->value;
      node->left->value = tmp;
    }

    node = node->left;
  }

  return node;
}
*/
static bool isLeaf(BSTNODE *node) {
  if (node == NULL) return false;
  if (!node->left && !node->right) return true;
  else return false;
}

static void displayHelper(FILE *fp, BSTNODE *root, BST *t) {

  //if t->size == 0...
  if (root == NULL) {
    fprintf(fp, "EMPTY\n");
    return;
  }
  else {
    QUEUE *nodesQueue = newQUEUE(NULL);
    int nodesInCurrLevel = 1;
    int nodesInNextLevel = 0;
    int printLevel = 1;

    enqueue(nodesQueue, root);

    bool isRoot = true;
    int height = findMaxDepthBST(root);

    int i = 0;
    while (i <= height) {
      BSTNODE *currNode = dequeue(nodesQueue);
      nodesInCurrLevel -= 1;

//      if (currNode) printf("CURR NODE!!!\n");
      if (currNode && i <= height) {
//        printf("FLAG\n");

        if (isRoot) {
          fprintf(fp, "%d: ", 0);
          if (isLeaf(currNode))
            fprintf(fp, "=");
          displayNODE(t, fp, currNode, true);
          isRoot = false;
        }
        else {
          if (isLeaf(currNode))
            fprintf(fp, "=");
          displayNODE(t, fp, currNode, false);
          if (nodesInCurrLevel != 0) fprintf(fp, " ");
        }
      }
      enqueue(nodesQueue, getBSTNODEleft(currNode));
      enqueue(nodesQueue, getBSTNODEright(currNode));
      nodesInNextLevel += 2;
      if (nodesInCurrLevel == 0) {
        i += 1;
        if (i == height) break;
        fprintf(fp, "\n");
        fprintf(fp, "%d: ", printLevel);

        nodesInCurrLevel = nodesInNextLevel;
        nodesInNextLevel = 0;
        printLevel += 1;
      }
    }
  }
}

static BSTNODE *copyNODE(BSTNODE *giver) {
  if (giver == NULL) return NULL;

  BSTNODE *newNode = malloc(sizeof(struct bst));

  if (giver->value)
    newNode->value = giver->value;
  else newNode->value = NULL;

  if (giver->parent)
    newNode->parent = giver->parent;
  else newNode->parent = NULL;

  if (giver->left)
    newNode->left = giver->left;
  else newNode->left = NULL;

  if (giver->right)
    newNode->right = giver->right;
  else newNode->right = NULL;

  if (giver->isLeftChild)
    newNode->isLeftChild = giver->isLeftChild;
  else newNode->isLeftChild = NULL;

  return newNode;
}

static int findMinDepthBST(BSTNODE *root) {
  if (root == NULL)
    return 0;

  int Lmin = findMinDepthBST(root->left);
  int Rmin = findMinDepthBST(root->right);

  return (Lmin<Rmin?Lmin:Rmin) + 1;
}

static int findMaxDepthBST(BSTNODE *root) {
  if (root == NULL) return 0;
  else {
    int L_depth, R_depth;
    L_depth = findMaxDepthBST(getBSTNODEleft(root));
    R_depth = findMaxDepthBST(getBSTNODEright(root));

    return (L_depth>R_depth?L_depth:R_depth) + 1;
  }
}

/*
static int min(int a, int b) {
  if (a < b) return a;
  else if (a > b) return b;
  else {
    return a;
  }
}
*/
