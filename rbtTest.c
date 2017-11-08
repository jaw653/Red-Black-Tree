#include <stdio.h>

#include "rbt.h"

int main(void) {
  printf("Attempting to Initialize rbt tree...\n");
  RBT *tree = newRBT(displayRBTNODE, compareRBTNODE);
  printf("rbt tree successfully initiailized\n");

  printf("Attempting to insert...\n");
  insertRBT(tree, newRBTNODE("node"));
  printf("1 insert successful\n");

  insertRBT(tree, newRBTNODE("node1"));
  printf("2 inserts successful\n");

  insertRBT(tree, newRBTNODE("node3"));
  printf("3 inserts successful\n");

  printf("Attempting to display...\n");
  displayRBT(stdout, tree);

  printf("\nAttempting to delete...\n");
  deleteRBT(tree, newRBTNODE("node3"));
  printf("Delete successful\n");

  printf("Attempting to find...\n");
  int count = findRBT(tree, newRBTNODE("node1"));
  printf("find successful, count is: %d\n", count);

  printf("Size is: %d\n", sizeRBT(tree));

  return 0;
}
