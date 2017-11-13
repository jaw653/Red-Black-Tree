#include <stdio.h>
#include "bst.h"
#include "gt.h"
#include "real.h"

int main(void) {
  GT *tree = newGT(displayREAL, compareREAL);
  printf("GT successfully initiailized.\n");

  printf("Attempting to insert 3...\n");
  insertGT(tree, newREAL(3));
  printf("successfully inserted.\n");

  printf("Attempting to display tree...\n");
  displayGT(stdout, tree);
  printf("\n");

  printf("Attempting to insert 5...\n");
  insertGT(tree, newREAL(5));
  printf("successfully inserted.\n");

  printf("tree is:\n");
  displayGT(stdout, tree);
  printf("\n");

  int i;
  for (i = 0; i < 2; i++) {
    printf("Attempting to insert 3...\n");
    insertGT(tree, newREAL(3));
    printf("successfully inserted.\n");
  }

  printf("tree is:\n");
  displayGT(stdout, tree);
  printf("\n");

  printf("Attempting to delete 3...\n");
  deleteGT(tree, newREAL(3));
  printf("Delete successful.\n");

  printf("tree is: \n");
  displayGT(stdout, tree);
  printf("\n");

  printf("\n");

  return 0;
}
