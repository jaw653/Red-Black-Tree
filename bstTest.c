#include <stdio.h>
#include "bst.h"
#include "real.h"

int main(void) {
    BST *tree = newBST(displayREAL, compareREAL, NULL);
    printf("tree successfully initiailized\n");

    insertBST(tree, newREAL(7));
    printf("1 insert successful\n");

    insertBST(tree, newREAL(6));
    printf("2 inserts successful\n");

    insertBST(tree, newREAL(5));
    printf("3 inserts successful\n");

    insertBST(tree, newREAL(8));
    printf("4 inserts successful\n");

    printf("Attempting to display tree...\n");
    displayBST(stdout, tree);
    printf("\n");
/*
    printf("Attempting to find node w/ value 6\n");
    BSTNODE *node = findBST(tree, newREAL(6));
    if (node) printf("node found\n");
    else printf("node NOT found\n");

    printf("Attempting to remove node with value 6...\n");
    deleteBST(tree, newREAL(6));
    printf("value successfully deleted\n");

    displayBST(stdout, tree);
    printf("\n");

    printf("tree size is: %d\n", sizeBST(tree));
    //printf("node value is: %s\n", getSTRING(node->value));
    //printf("node->left is: %p\n", node->left);
    //printf("node->right is: %p\n", node->right);
    //printf("node->parent->value is: %s\n", getSTRING(node->parent->value));
*/
    return 0;
}
