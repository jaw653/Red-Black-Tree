#include <stdio.h>

#include "bst.h"
#include "rbt.h"
#include "real.h"

int main(void) {
  printf("Attempting to Initialize rbt tree...\n");
  RBT *tree = newRBT(displayREAL, compareREAL);
  printf("rbt tree successfully initiailized\n");

  printf("Attempting to insert...\n");
  insertRBT(tree, newREAL(6));
  printf("6 insert successful\n");

  insertRBT(tree, newREAL(8));
  printf("8 inserts successful\n");

  insertRBT(tree, newREAL(3));
  printf("3 inserts successful\n");

  printf("Attempting to display...\n");
  displayRBT(stdout, tree);

  printf("\nAttempting to delete...\n");
  deleteRBT(tree, newREAL(6));
  printf("Delete successful\n");

  printf("\n Tree is now: \n");
  displayRBT(stdout, tree);
  printf("\n");
  
  printf("Attempting to find...\n");
  int count = findRBT(tree, newREAL(8));
  printf("find successful, count is: %d\n", count);

  printf("Size is: %d\n", sizeRBT(tree));

  return 0;
}
