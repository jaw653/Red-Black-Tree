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
 *            -do we need to account for equal values in the bst
 *            -when deleting nodes, can I just set them = NULL or do I need to free?
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bst.h"

struct bstnode {

  void *value;
  struct bstnode *parent;
  struct bstnode *left;
  struct bstnode *right;

};
/****************************** Private functions *****************************/
static BSTNODE *newBSTNODE(void *value) {
  BSTNODE *node = malloc(sizeof(struct bstnode));
  node->value = value;
  node->parent = node->left = node->right = NULL;

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
  int size;
  struct bstnode *root;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
  void (*swapper)(void *, void *);
};

/***************************** Helper function(s) *****************************/
static BSTNODE *insertHelper(BST *t, BSTNODE *parent, void *value) {
  if (t->root == NULL) {
    //assert?

    t->root = (struct bstnode *)malloc(sizeof(struct bstnode));
    t->root->value = value;
    t->root->parent = parent;
    t->root->left = NULL;
    t->root->right = NULL;
    t->size += 1;

  }
  else if (t->comparator(value, t->root->value) < 0) {
    t->root->left = insertHelper(t, t->root, value);
  }
  else {
    t->root->right = insertHelper(t, t->root, value);
  }

  return t->root;
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

static BSTNODE *traverseRight(BSTNODE *node) {
  while (node->right) {
    void *tmp = node->value;
    node->value = node->right->value;
    node->right->value = tmp;

    node = node->right;
  }

  return node;
}

static BSTNODE *traverseLeft(BSTNODE *node) {
  while (node->left) {
    void *tmp = node->value;
    node->value = node->left->value;
    node->left->value = tmp;

    node = node->left;
  }

  return node;
}

static bool isLeaf(BSTNODE *node) {
  if (!node->left && !node->right) return true;
  else return false;
}


static void displayHelper(FILE *fp, BSTNODE *root, BST *t) {
  if (t->size == 0) {
    printf("[]");
    return;
  }

  else {
    printf("[");
    if (root->left) displayHelper(fp, root->left, t);

    if (root->left) printf(" ");
    t->display(fp, root->value);
    if (root->right) printf(" ");

    if (root->right) displayHelper(fp, root->right, t);
    printf("]");
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
  return insertHelper(t, NULL, value);
}

BSTNODE *findBST(BST *t, void *value) {
  return findHelper(t->root, t->comparator, value);
}

BSTNODE *deleteBST(BST *t, void *value) {
  //pass
}

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node) {
  BSTNODE *ptr = node;
  /* If swapper is not null */
  if (t->swapper) {
    if (isLeaf(ptr)) return NULL;
    if (ptr->left) {
      t->swapper(ptr->left, node);
      ptr = ptr->left;
      ptr = traverseRight(ptr);         //FIXME: currently doesn't use the swapper function
      ptr = swapToLeafBST(t, ptr);
    }
    else if (ptr->right) {
      t->swapper(ptr->right, node);
      ptr = ptr->right;
      ptr = traverseLeft(ptr);         //FIXME: currently doesn't use swapper function
      ptr = swapToLeafBST(t, ptr);
    }
  }
  else {
    if (isLeaf(ptr)) return NULL;
    if (ptr->left) {
      void *tmp = ptr->value;
      ptr->value = ptr->left->value;
      ptr->left->value = tmp;
      ptr = ptr->left;
      ptr = traverseRight(ptr);
      return swapToLeafBST(t, ptr);
    }
    else if (ptr->right) {
      void *tmp = ptr->value;
      ptr->value = ptr->right->value;
      ptr->right->value = tmp;
      ptr = ptr->right;
      ptr = traverseLeft(ptr);
      return swapToLeafBST(t, ptr);
    }
  }

  return NULL;                        //FIXME: may need to get rid of this...
}

void pruneLeafBST(BST *t, BSTNODE *leaf) {
  if (t->comparator(leaf->parent->value, leaf->value) < 0) {
    /* If right child */
    leaf->parent->right = NULL;
    leaf = NULL;
  }
  else {
    leaf->parent->left = NULL;
    leaf = NULL;
  }
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
