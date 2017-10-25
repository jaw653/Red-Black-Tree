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
 */
#include <stdio.h>

#include "bst.h"

struct bstnode {
  void *value;
  bstnode *parent;
  bstnode *left;
  bstnode *right;
} BSTNODE;

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
  n->rgiht->right = replacement->right;
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
