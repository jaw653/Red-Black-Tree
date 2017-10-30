/* Author: Jake Wachs
 * Date: 10/30/2017
 * The University of Alabama
 */

#include <stdio.h>
#include "phrase.h"

struct PHRASE {
  int frequency;
  char color;
  char *value;
};

PHRASE *newPHRASE(char *value) {
  PHRASE *p = malloc(sizeof(struct PHRASE));
  p->frequency = 0;
  p->color = 'r';
  p->value = NULL;
}

char *getPHRASE(PHRASE *p) {
  return p->value;
}

char *setPHRASE(PHRASE *p, char *str) {
  char *returnVal = p->value;
  p->value = str;
  return returnVal;
}

void displayPHRASE(FILE *fp, PHRASE *p) {
  fprintf(fp, "%s\n", p->value);
}

char getPHRASEcolor(PHRASE *p) {
  return p->color;
}

void setPHRASEcolor(PHRASE *p, char c) {
  p->color = c;
}

int getPHRASEfrequency(PHRASE *p) {
  return p->frequency;
}

void setPHRASEfrequency(PHRASE *p, int f) {
  p->frequency = f;
}

void freePHRASE(PHRASE *p) {
  free(p);
}

int comparePHRASE(void *p1, void *p2) {
    char *val1 = getPHRASE(p1);
    char *val2 = getPHRASE(p2);

    if (strcmp(val1, val2) < 0) return -1;
    else if (strcmp(val1, val2) > 0) return 1;
    else return 0;
}
