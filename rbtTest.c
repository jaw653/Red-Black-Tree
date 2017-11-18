#include <stdio.h>

#include "bst.h"
#include "rbt.h"
#include "real.h"

static void displayTree(RBT *);
static void insertValue(RBT *, int);
static void deleteValue(RBT *, int);
static void findValue(RBT *, int);

int main(void) {
  printf("Attempting to Initialize rbt tree...\n");
  RBT *tree = newRBT(displayREAL, compareREAL);
  printf("rbt tree successfully initiailized\n\n");
/*
  insertValue(tree, 11);  //the
  insertValue(tree, 10);  //quickity quick
  insertValue(tree, 2);   //brown

  printf("size of tree is: %d\n", sizeRBT(tree));
  displayTree(tree);

  insertValue(tree, 4);   //fox
  displayTree(tree);
  insertValue(tree, 7);   //jumped
  displayTree(tree);

  insertValue(tree, 9);   //over
  displayTree(tree);

  insertValue(tree, 11);  //the
  displayTree(tree);

  insertValue(tree, 5);   //girl
  displayTree(tree);

  insertValue(tree, 1);   //and
  displayTree(tree);

  insertValue(tree, 6);   //her
  displayTree(tree);

  insertValue(tree, 8);   //lazy
  displayTree(tree);

  insertValue(tree, 8);   //lazy
  displayTree(tree);

  insertValue(tree, 3);   //dog
  displayTree(tree);


  displayTree(tree);
*/
  insertValue(tree, 5);
  insertValue(tree, 10);
  displayTree(tree);
  deleteValue(tree, 10);
  displayTree(tree);

/*
  insertValue(tree, 6);
  insertValue(tree, 8);
  insertValue(tree, 3);
  insertValue(tree, 10);
  insertValue(tree, 1);
  insertValue(tree, 4);
  insertValue(tree, 5);
  insertValue(tree, 15);
  insertValue(tree, 8);

  displayTree(tree);

  deleteValue(tree, 6);
  printf("size of tree is: %d\n", sizeRBT(tree));
  displayTree(tree);

  findValue(tree, 8);

  printf("Size is: %d\n", sizeRBT(tree));
*/
  return 0;
}

static void displayTree(RBT *tree) {
  printf("Tree is:\n");
  displayRBT(stdout, tree);
  printf("\n\n");
}

static void insertValue(RBT *tree, int n) {
  printf("Attempting to insert %d...\n", n);
  insertRBT(tree, newREAL(n));
  printf("%d insert successful.\n\n", n);
}

static void deleteValue(RBT *tree, int n) {
  printf("Attempting to delete value %d...\n", n);
  deleteRBT(tree, newREAL(n));
  printf("Delete of %d successful.\n", n);
}
static void findValue(RBT *tree, int n) {
  printf("Attempting to find %d...\n", n);
  int count = findRBT(tree, newREAL(n));
  printf("find successful, count is: %d\n", count);
}
