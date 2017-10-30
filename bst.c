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
 *            -when should swapleaf swap with pred and when successor
 *            -do we need to account for equal values in the bst
 *            -when deleting nodes, can I just set them = NULL or do I need to free?
 *            -right now, findbst does not account for if the value is not in the tree, should it?
 *            -insertBST does not account for duplicate values, should it?
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "string.h"
#include "bst.h"

struct bstnode {
  void *value;
  struct bstnode *parent;
  struct bstnode *left;
  struct bstnode *right;
};
/****************************** Private functions *****************************/
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
/******************************************************************************/

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
  int size;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
  void (*swapper)(void *, void *);
};

/***************************** Helper function(s) *****************************/
static BSTNODE *insertHelper(BST *t, BSTNODE* root, BSTNODE *parent, void *value) {
  if (root == NULL) {
    //assert?

    root = newBSTNODE(value, parent);
    t->size += 1;

    return root;
  }
  else if (t->comparator(value, root->value) < 0) {
    root->left = insertHelper(t, root->left, root, value);
  }
  else {
    root->right = insertHelper(t, root->right, root, value);
  }

  return root;
}

static BSTNODE *findHelper(BSTNODE *root, int (*comparator)(void *, void *), void *value) {
  if (root == NULL || comparator(value, root->value) == 0) {
    if (root == NULL) return NULL;
    return root;
  }
  else if (comparator(value, root->value) < 0) {
    return findHelper(root->left, comparator, value);
  }
  else {
    return findHelper(root->right, comparator, value);
  }
}

static void traverseRight(BST *t, BSTNODE *node, bool useSwapper) {
  while (node->right) {
    if (useSwapper == true) {
      t->swapper(node, node->right);
    }
    else {
      void *tmp = node->value;
      node->value = node->right->value;
      node->right->value = tmp;
    }

    node = node->right;
  }
}

static void traverseLeft(BST *t, BSTNODE *node, bool useSwapper) {
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
}

static bool isLeaf(BSTNODE *node) {
  if (!node->left && !node->right) return true;
  else return false;
}


static void displayHelper(FILE *fp, BSTNODE *root, BST *t) {
  if (t->size == 0) {
    fprintf(fp, "[]");
    return;
  }
  else {
    if (root->value) {
      fprintf(fp, "[");
      if (root->left) displayHelper(fp, root->left, t);

      if (root->left) fprintf(fp, " ");
      t->display(fp, root->value);
      if (root->right) fprintf(fp, " ");

      if (root->right) displayHelper(fp, root->right, t);
      fprintf(fp, "]");
    }
  }
}

static bool structsAreEqual(BSTNODE *s1, BSTNODE *s2) {
  if (s1 && s2) {
    if (s1->value && s2->value) {
      if (s1->value == s2->value && s1->left == s2->left) {
        if (s1->right == s2->right && s1->parent == s2->parent) {
          return true;
        }
      }
    }
  }

  return false;
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

    tree->root = newBSTNODE(NULL, NULL);
    tree->size = 0;

    return tree;
}

void setBSTroot(BST *t, BSTNODE *replacement) {
  t->root = replacement;
}

BSTNODE *getBSTroot(BST *t) {
  return t->root;
}

BSTNODE *insertBST(BST *t, void *value) {
  t->root = insertHelper(t, t->root, NULL, value);
  return t->root;
}

BSTNODE *findBST(BST *t, void *value) {
  return findHelper(t->root, t->comparator, value);
}

BSTNODE *deleteBST(BST *t, void *value) {
  BSTNODE *returnNode;

  BSTNODE *node = findBST(t, value);
  node = swapToLeafBST(t, node);
  returnNode = node;

  pruneLeafBST(t, node);

  return returnNode;
}

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {

  /* If swapper is not null */
  if (t->swapper) {
    if (isLeaf(node)) return node;        //FIXME: might need to return NULL
    if (node->left) {
      t->swapper(node->left, node);
      node = node->left;
      traverseRight(t, node, true);         //FIXME: currently doesn't use the swapper function

      return swapToLeafBST(t, node);
    }
    else if (node->right) {
      t->swapper(node->right, node);
      node = node->right;
      traverseLeft(t, node, true);         //FIXME: currently doesn't use swapper function

      return swapToLeafBST(t, node);
    }
  }
  else {
    if (isLeaf(node)) return node;
    if (node->left) {
      void *tmp = node->value;
      node->value = node->left->value;
      node->left->value = tmp;
      node = node->left;
      traverseRight(t, node, false);

      return swapToLeafBST(t, node);
    }
    else if (node->right) {
      void *tmp = node->value;
      node->value = node->right->value;
      node->right->value = tmp;
      node = node->right;
      traverseLeft(t, node, false);

      return swapToLeafBST(t, node);
    }
  }

  return NULL;                        //FIXME: may need to get rid of this...
}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
  /* If left child */
  if (structsAreEqual(leaf->parent->left, leaf)) {
    leaf->parent->left = NULL;
  }
  /* If right child */
  else if (structsAreEqual(leaf->parent->right, leaf)) {
    leaf->parent->right = NULL;
  }

  free(leaf);

  t->size -= 1;
}

int sizeBST(BST *t) {
  return t->size;
}

void statisticsBST(FILE *fp, BST *t) {
  fprintf(fp, "Words/Phrases: %d\n", 5);      //FIXME: should be the actual number of words/Phrases
  fprintf(fp, "Nodes: %d\n", t->size);
  fprintf(fp, "Maximum depth: %d\n", 5);      //FIXME: need correct stat here
  fprintf(fp, "Minimum depth: %d\n", 5);      //FIXME: need correct stat here
}

void displayBST(FILE *fp, BST *t) {
  displayHelper(fp, t->root, t);
}
