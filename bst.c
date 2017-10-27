/*
 * Author: Jake Wachs
 * Date: 10/25/2017
 * The University of Alabama
 *
 * This is the implementation file for the bst.h inteface
 */

/*
 * Questions:
 *            -setBSTNODE, should it just set n->value = value?
 *            -setBSTNODEleft, copies all replacement stuff to n->left, is this ok?
 *            -when should swap leaf swap with pred and when successor
 */
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct bstnode {

  void *value;
  struct bstnode *parent;
  struct bstnode *left;
  struct bstnode *right;

};

static BSTNODE *newBSTNODE(void *value) {
  BSTNODE *node = malloc(sizeof(struct bstnode));
  node->value = value;
  node->parent = node->left = node->right = NULL;

  return node;
}

void *getBSTNODE(BSTNODE *n) {
  return n->value;
}

void setBSTNODE(BSTNODE *n, void *value) {
  n->value = value;
}

BSTNODE *getBSTNODEleft(BSTNODE *n) {
  return n->left;
}

void setBSTNODEleft(BSTNODE *n, BSTNODE *replacement) {
  n->left->value = replacement->value;
  n->left->parent = replacement->parent;
  n->left->left = replacement->left;
  n->left->right = replacement->right;
}

BSTNODE *getBSTNODEright(BSTNODE *n) {
  return n->right;
}

void setBSTNODEright(BSTNODE *n, BSTNODE *replacement) {
  n->right->value = replacement->value;
  n->right->parent = replacement->parent;
  n->right->left = replacement->left;
  n->right->right = replacement->right;
}

BSTNODE *getBSTNODEparent(BSTNODE *n) {
  return n->parent;
}

void setBSTNODEparent(BSTNODE *n, BSTNODE *replacement) {
  n->parent->value = replacement->value;
  n->parent->parent = replacement->parent;
  n->parent->left = replacement->left;
  n->parent->right = replacement->right;
}

struct bst {
  struct bstnode *root;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
  void (*swapper)(void *, void *);
};

/***************************** Helper function(s) *****************************/
static BSTNODE *insertHelper(BSTNODE *root, int (*comparator)(void *, void *), void *value) {
  if (root == NULL) {
    //assert?

    root = (struct bstnode *)malloc(sizeof(struct bstnode));
    root->value = value;
    //root->parent = ??
    root->left = NULL;
    root->right = NULL;
  }
  else if (comparator(value, root->value) < 0) {
    root->left = insertHelper(root->left, comparator, value);
  }
  else {
    root->right = insertHelper(root->right, comparator, value);
  }

  return root;
}

static BSTNODE *findHelper(BSTNODE *root, int (*comparator)(void *, void *), void *value) {
  if (root == NULL || comparator(value, root->value) == 0) {
    if (root == NULL) return NULL;
    return root->value;
  }
  else if (comparator(value, root->value) < 0) {
    return findHelper(root->left, comparator, value);
  }
  else {
    return findHelper(root->right, comparator, value);
  }
}
/******************************************************************************/

BST *newBST(
  void (*d)(FILE *, void *),
  int (*c)(void *, void *),
  void (*s)(void *, void *))
{

    BST *tree = malloc(sizeof(struct bst));
    tree->display = d;
    tree->comparator = c;
    tree->swapper = s;
    tree->root = newBSTNODE(NULL);          //FIXME: what to pass through here?

    return tree;
}

void setBSTroot(BST *t, BSTNODE *replacement) {
  t->root = replacement;
}

BSTNODE *getBSTroot(BST *t) {
  return t->root;
}

BSTNODE *insertBST(BST *t, void *value) {
  return insertHelper(t->root, t->comparator, value);
}

BSTNODE *findBST(BST *t, void *value) {
  return findHelper(t->root, t->comparator, value);
}

BSTNODE *deleteBST(BST *t, void *value) {
  //pass
}

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {

}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
  //pass
}

int sizeBST(BST *t) {
  //pass
}

void statisticsBST(FILE *fp, BST *t) {
  //pass
}

void displayBST(FILE *fp, BST *t) {
  //pass
}
