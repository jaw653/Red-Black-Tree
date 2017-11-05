/* Author: Jake Wachs
 * Date: 10/31/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "gt.h"
#include "gtnode.h"

struct gt {
  struct bst *tree;
  void (*display)(FILE *, void *);
  int (*comparator)(void *, void *);
};

GT *newGT(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
  GT *t = malloc(sizeof(struct gt));
  t->tree = newBST(displayGTNODE, compareGTNODE, swapGTNODE);
  t->display = d;
  t->comparator = c;

  return t;
}
