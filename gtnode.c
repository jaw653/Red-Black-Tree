#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gtnode.h"

struct GTNODE {
  char *value;
  int frequency;
};

GTNODE *newGTNODE(char *value) {
  GTNODE *n = malloc(sizeof(struct GTNODE));
  n->value = value;
  n->frequency = 1;

  return n;
}

char *getGTNODE(GTNODE *n) {
  return n->value;
}

char *setGTNODE(GTNODE *n, char *s) {
  char *val = s;
  n->value = s;
  return val;
}

void displayGTNODE(FILE *fp, void *n) {
  fprintf(fp, "%s-%c\n", getGTNODE(n), getGTNODEfrequency(n));
}

void freeGTNODE(GTNODE *n) {
  free(n);
}

int getGTNODEfrequency(GTNODE *n) {
  return n->frequency;
}

void setGTNODEfrequency(GTNODE *n, int x) {
  n->frequency = x;
}

int incrementGTNODEfrequency(GTNODE *n) {
  n->frequency += 1;
  return n->frequency;
}

int decrementGTNODEfrequency(GTNODE *n) {
  if (n->frequency == 0) {
    return 0;
  }
  else {
    n->frequency -= 1;
    return n->frequency;
  }
}

int compareGTNODE(void *v1, void *v2) {
  char *val1 = getGTNODE(v1);
  char *val2 = getGTNODE(v2);

  if (strcmp(val1, val2) < 0) return -1;
  else if (strcmp(val1, val2) > 0) return 1;
  else return 0;
}

void swapGTNODE(void *n1, void *n2) {
  char *node1 = getGTNODE(n1);
  char *node2 = getGTNODE(n2);

  int tempFreq = getGTNODEfrequency(n1);
  setGTNODEfrequency(n1, getGTNODEfrequency(n2));
  setGTNODEfrequency(n2, tempFreq);

  char *tempVal = node1;
  setGTNODE(n1, node2);
  setGTNODE(n2, tempVal);
}
