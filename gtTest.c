#include <stdio.h>
#include "bst.h"
#include "gt.h"
#include "real.h"

static void displayTree(GT *);

int main(void) {
  GT *tree = newGT(displayREAL, compareREAL);
  printf("GT successfully initiailized.\n");

  printf("Attempting to insert 3...\n");
  insertGT(tree, newREAL(3));
  printf("successfully inserted.\n");

  displayTree(tree);

  printf("Attempting to insert 5...\n");
  insertGT(tree, newREAL(5));
  printf("successfully inserted.\n");

  displayTree(tree);

  int i;
  for (i = 0; i < 2; i++) {
    printf("Attempting to insert 3...\n");
    insertGT(tree, newREAL(3));
    printf("successfully inserted.\n");
  }

  displayTree(tree);

  printf("Attempting to delete 3...\n");
  deleteGT(tree, newREAL(3));
  printf("Delete successful.\n");

  displayTree(tree);

  for (i = 0; i < 3; i++) {
    printf("Attempting to delete 3...\n");
    deleteGT(tree, newREAL(3));
    printf("Delete successful.\n");
  }

  displayTree(tree);

  printf("Attempting to delete 5...\n");
  deleteGT(tree, newREAL(5));
  printf("Delete successful.\n");

  displayTree(tree);

  printf("Attempting to insert 10...\n");
  insertGT(tree, newREAL(15));
  printf("successfully inserted.\n");

  displayTree(tree);

  printf("Statistics:\n");
  statisticsGT(stdout, tree);
  printf("\n\n");

  return 0;
}

static void displayTree(GT *tree) {
  printf("tree is: \n");
  displayGT(stdout, tree);
  printf("\n\n");
}
