/* Author: Jake Wachs
 * Implementation of STRING data typedef
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "string.h"

struct STRING {
  char *value;
};

STRING *newSTRING(char *str) {
  STRING *ptr = malloc( sizeof(STRING) );
  assert(ptr != 0);
  ptr->value = str;
  return ptr;
}

char *getSTRING(STRING *s) {
  return s->value;
}

char *setSTRING(STRING *s, char *val) {
  char *replacedVal = s->value;
  s->value = val;
  return replacedVal;
}

void displaySTRING(FILE *fp, void *v) {
  fprintf(fp, "%s", getSTRING((STRING *) v));
}

void freeSTRING(STRING *s) {
  free(s);
}

int compareSTRING(void *s1, void *s2) {
  char *rawVal1 = getSTRING(s1);
  char *rawVal2 = getSTRING(s2);

  return strcmp(rawVal1, rawVal2);
}
