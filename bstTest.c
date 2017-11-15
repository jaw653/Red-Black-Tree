/* Author: Jake Wachs
 * Date: November 13, 2017
 *
 * The University of Alabama
 */

#include <stdio.h>
#include "bst.h"
#include "real.h"

static void displayTree(BST *);

int main(void) {
    BST *tree = newBST(displayREAL, compareREAL, NULL);
    printf("\nTree successfully initiailized\n");

    displayTree(tree);

    insertBST(tree, newREAL(4));
    printf("4 insert successful\n");

    insertBST(tree, newREAL(5));
    printf("5 inserts successful\n");

    insertBST(tree, newREAL(7));
    printf("7 inserts successful\n");

    insertBST(tree, newREAL(3));
    printf("3 inserts successful\n");

    insertBST(tree, newREAL(2));
    printf("2 inserts successful\n");

    insertBST(tree, newREAL(8));
    printf("8 inserts successful\n");

    insertBST(tree, newREAL(6));
    printf("6 inserts successful\n");

    insertBST(tree, newREAL(9));
    printf("9 inserts successful\n");

    insertBST(tree, newREAL(1));
    printf("1 inserts successful\n");

    insertBST(tree, newREAL(0));
    printf("0 inserts successful\n");

    displayTree(tree);

    printf("print statistics...\n");
    statisticsBST(stdout, tree);
    printf("\n");

    printf("deleting the root via getBSTroot method...\n");
    deleteBST(tree, getBSTNODE(getBSTroot(tree)));

    displayTree(tree);

    printf("printing statistics...\n");
    statisticsBST(stdout, tree);
    printf("\n");

    printf("attempting to find value 2...\n");
    BSTNODE *foundNode = findBST(tree, newREAL(2));
    if (foundNode)
      printf("node found! accessed value is: %lf\n", getREAL(getBSTNODE(foundNode)));
    else
      printf("node not found :(\n");

    printf("\n");

    printf("Attempting to delete all values in tree, then make it display EMPTY\n");
    printf("original size is: %d\n", sizeBST(tree));
    while (sizeBST(tree) > 0) {
      printf("deleting: %lf\n", getREAL(getBSTNODE(getBSTroot(tree))));
      deleteBST(tree, getBSTNODE(getBSTroot(tree)));
      printf("size is: %d\n", sizeBST(tree));
      displayTree(tree);
    }
    deleteBST(tree, getBSTNODE(getBSTroot(tree)));

    displayTree(tree);

    printf("attempting to add nodes back to bst after removing to empty...\n");
    insertBST(tree, newREAL(55));
    printf("insert successful.\n");

    displayTree(tree);


    return 0;
}

static void displayTree(BST *tree) {
  printf("tree is:\n");
  displayBST(stdout, tree);
  printf("\n\n");
}
