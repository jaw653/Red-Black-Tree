/* Author: Jake Wachs
 * Date: 10/30/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <string.h>

#include "rbtnode.h"
#include "bst.c"

struct RBTNODE {
  int frequency;
  char color;
  char *value;
};

RBTNODE *newRBTNODE(char *value) {
  RBTNODE *p = malloc(sizeof(struct RBTNODE));
  p->frequency = 0;
  p->color = 'r';
  p->value = value;

  return p;
}

char *getRBTNODE(RBTNODE *p) {
  return p->value;
}

char *setRBTNODE(RBTNODE *p, char *str) {
  char *returnVal = p->value;
  p->value = str;
  return returnVal;
}

void displayRBTNODE(FILE *fp, void *p) {

  fprintf(fp, "%s\n", getRBTNODE(p));
}

char getRBTNODEcolor(RBTNODE *p) {
  return p->color;
}

void setRBTNODEcolor(RBTNODE *p, char c) {
  p->color = c;
}

int getRBTNODEfrequency(RBTNODE *p) {
  return p->frequency;
}

void setRBTNODEfrequency(RBTNODE *p, int f) {
  p->frequency = f;
}

void freeRBTNODE(RBTNODE *p) {
  free(p);
}

int compareRBTNODE(void *p1, void *p2) {
    char *val1 = getRBTNODE(p1);
    char *val2 = getRBTNODE(p2);

    if (strcmp(val1, val2) < 0) return -1;
    else if (strcmp(val1, val2) > 0) return 1;
    else return 0;
}

void swapRBTNODE(BSTNODE *node1, BSTNODE *node2) {
  RBTNODE *n1 = getBSTNODE(node1);
  RBTNODE *n2 = getBSTNODE(node2);

  int tempFreq = n1->frequency;
  n1->frequency = n2->frequency;
  n2->frequency = tempFreq;

  char *tempVal = n1->value;
  n1->value = n2->value;
  n2->value = tempVal;
}
