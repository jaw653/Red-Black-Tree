#include <stdio.h>
#include "bst.h"
#include "real.h"

int main(void) {
    BST *tree = newBST(displayREAL, compareREAL, NULL);
    printf("\nTree successfully initiailized\n");

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

    printf("\nDisplaying the tree...\n");
    displayBST(stdout, tree);
    printf("\n");

    printf("print statistics...\n");
    statisticsBST(stdout, tree);
    printf("\n");

    printf("deleting the root via getBSTroot method...\n");
    deleteBST(tree, getBSTNODE(getBSTroot(tree)));

    printf("displaying the tree...\n");
    displayBST(stdout, tree);
    printf("\n");

    printf("printing statistics...\n");
    statisticsBST(stdout, tree);
    printf("\n");

    return 0;
}
