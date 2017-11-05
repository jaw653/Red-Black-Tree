/*Author: Jake Wachs
 *Date: 08/26/17
 *University of Alabama
 *This file serves as method implementations for the
 *circular dynamic array object
 */

/*
 *Notes on how to fix:
 *-after each remove, print the visualizeCDA to see exactly what's happening, along with the front, back, size and filledIndices
 *-retest extract and remove to make sure you didn't f anything up
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "cda.h"

struct cda {
  void (*display)(FILE *, void*);
  int frontIndex;
  int backIndex;
  int size;
  int filledIndices;
  void **array;
};

CDA *newCDA(void (*d)(FILE *, void *)) {
    assert(sizeof(CDA) != 0);

    CDA *arr = malloc( sizeof(CDA) );

    arr->array = malloc( 1 * sizeof(void*) );
    arr->display = d;
    arr->size = 1;
    arr->filledIndices = 0;
    arr->frontIndex = 0;
    arr->backIndex = 0;

    return arr;
}

void insertCDAfront(CDA *items, void *value) {
  assert( items->size * 2 * sizeof(void*) != 0 );

  if (items->filledIndices == 0) {
    items->array[items->filledIndices] = value;
    items->frontIndex = 0;
    items->backIndex = 0;
  }
  else {
    if (items->filledIndices < items->size) {
      if (items->frontIndex == 0) {
        items->frontIndex = items->size - 1;
        items->array[items->size - 1] = value;
      }
      else {
        items->array[items->frontIndex - 1] = value;
        items->frontIndex -= 1;
      }
    }
    else {
      //If there is no room in the array
      void **tmp = malloc(items->size * 2 * sizeof(void*));

      int i;
      int origIndex = items->frontIndex;
      for (i = 0; i < items->filledIndices; i++) {
        tmp[i] = items->array[origIndex];
        if (origIndex == items->size - 1) { origIndex = 0; }
        else { origIndex += 1; }
      }

      items->backIndex = i - 1;
      items->array = realloc( items->array, 2 * items->size * sizeof(void*));
      items->array = tmp;
      items->size *= 2;

      items->array[items->size - 1] = value;
      items->frontIndex = items->size - 1;
    }
  }

  items->filledIndices += 1;
}

void insertCDAback(CDA *items, void *value) {
  assert( items->size * 2 * sizeof(void*) != 0 );

//  printf("items->filledIndices is: %d\n", items->filledIndices);
  if (items->filledIndices == 0) {
/******************************************************************************/
    items->array[0] = value;
/******************************************************************************/
    items->backIndex = 0;
    items->frontIndex = 0;
  }
  else {
    if (items->filledIndices < items->size) {
      //If there is room in the array
      if (items->backIndex == items->size - 1) {
        items->backIndex = 0;
        items->array[items->backIndex] = value;
      }
      else {
        items->array[items->backIndex + 1] = value;
        items->backIndex += 1;
      }
    }
    else {
      //Following code doubles size and then copies values w/ frontIndex = 0
      void **tmp = malloc(items->size * 2 * sizeof(void*));

      int i;
      int origIndex = items->frontIndex;
      for (i = 0; i < items->filledIndices; i++) {
        tmp[i] = items->array[origIndex];
        if (origIndex == items->size - 1) { origIndex = 0; }
        else { origIndex += 1; }
      }

      items->backIndex = items->filledIndices;
      items->frontIndex = 0;
      items->array = realloc( items->array, 2 * items->size * sizeof(void*));
      items->array = tmp;
      items->size *= 2;

      items->array[items->filledIndices] = value;
    }
  }

  items->filledIndices += 1;
}

void *removeCDAfront(CDA *items) {
  assert( items->filledIndices > 0 );

  void *valToReturn = NULL;

  if (items->filledIndices == 0) {
    items->backIndex = 0;
    items->frontIndex = 0;
    valToReturn = NULL;
  }
  else {
    if (items->filledIndices - 1 < .25 * items->size) {
      /*
       *The following code creates a new tmpArray and fills it with all the non NULL
       *values in the original array. It then cuts the size of the items->array (the
       *actual object) by /2. It then repopulates the resized array with tmpArray, so
       *every resized array will have a frontIndex of 0 and a backIndex of filledIndices
       *minus one. Removing the requested value happens after this "if" code block.
       */
      void **tmp = malloc ( items->size/2 * sizeof(void*) );

      int i;
      int origIndex = items->frontIndex;
      for (i = 0; i < items->filledIndices; i++) {
        tmp[i] = items->array[origIndex];
        if (origIndex == items->size - 1) { origIndex = 0; }
        else { origIndex += 1; }
      }

      items->size /= 2;
      items->array = realloc( items->array, items->size * sizeof(void*) );
      items->array = tmp;
      items->frontIndex = 0;
      items->backIndex = items->filledIndices - 2;
    }

    valToReturn = items->array[items->frontIndex];
    items->array[items->frontIndex] = NULL;
    items->filledIndices -= 1;

    if (items->frontIndex + 1 == items->size) { items->frontIndex = 0; }
    else { items->frontIndex += 1; }
  }

  return valToReturn;
}
void *removeCDAback(CDA *items) {
  assert(items->filledIndices > 0);

  void *valToReturn = NULL;

  if (items->filledIndices == 0) {
    items->backIndex = 0;
    items->frontIndex = 0;
    return NULL;
  }

  else {
    if (items->filledIndices - 1 < .25 * items->size) {
      /*
       *The following code creates a new tmpArray and fills it with all the non NULL
       *values in the original array. It then cuts the size of the items->array (the
       *actual object) by /2. It then repopulates the resized array with tmpArray, so
       *every resized array will have a frontIndex of 0 and a backIndex of filledIndices
       *minus one. Removing the requested value happens after this "if" code block.
       */

      void **tmp = malloc ( items->size/2 * sizeof(void*) );

      int i;
      int origIndex = items->frontIndex;
      for (i = 0; i < items->filledIndices; i++) {
        tmp[i] = items->array[origIndex];
        if (origIndex == items->size - 1) { origIndex = 0; }
        else { origIndex += 1; }
      }

      items->size /= 2;
      items->array = realloc( items->array, items->size * sizeof(void*) );
      items->array = tmp;
      items->frontIndex = 0;
      items->backIndex = items->filledIndices - 1;
    }

    valToReturn = items->array[items->backIndex];
    items->array[items->backIndex] = NULL;

    if (items->backIndex - 1 < 0) { items->backIndex = items->size - 1; }
    else { items->backIndex -= 1; }
  }

  items->filledIndices -= 1;
/************************************************************************************/
/*
  printf("After removeCDAback(), the following: \n");
  printf("items->filledIndices = %d\n", items->filledIndices);
  printf("items->size = %d\n", items->size);
  printf("frontIndex = %d\n", items->frontIndex);
  printf("backIndex = %d\n", items->backIndex);
*/
/************************************************************************************/
  return valToReturn;
}

void unionCDA(CDA *recipient,CDA *donor) {

  if (donor->filledIndices == 0) {
    donor->frontIndex = 0;
    donor->backIndex = 0;
    donor->filledIndices = 0;
    donor->size = 1;

    return;
  }

  int index = donor->frontIndex;

//  printf("index is: %d\n", index);
//  printf("element is: %d\n", donor->array[index]);

  int i;

//  printf("donor is: \n");
//  visualizeCDA(stdout, donor);

//  printf("\nrecip is: \n");
//  visualizeCDA(stdout, recipient);
//  printf("\n");

  for (i = 0; i < donor->filledIndices; i++) {
//    printf("run %d\n", i);
    insertCDAback(recipient, donor->array[index]);
//    printf("after insert %d\n", i);
    if (index + 1 == donor->size) { index = 0; }
    else { index += 1; }
  }

  donor->array = extractCDA(donor);
}

void *getCDA(CDA *items,int index) {
  assert(index >= 0 && index < items->filledIndices);
  return items->array[items->frontIndex + index];
}

void *setCDA(CDA *items,int index,void *value) {
  assert(index >= -1 && index <= items->filledIndices);

  void *valToReturn = 0;

  if (index == items->filledIndices) {
    insertCDAback(items, value);
  }
  else if (index == -1) {
    insertCDAfront(items, value);
  }
  else {
    valToReturn = items->array[index];
    items->array[index] = value;
  }

  return valToReturn;
}

void **extractCDA(CDA *items) {
  int numIterations = items->filledIndices;

  if (items->filledIndices == 0) {
    return 0;
  }

  assert( items->filledIndices * sizeof(void*) != 0 );

  void **tmp = malloc ( items->filledIndices * sizeof(void*) );

  int i;
  int origIndex = items->frontIndex;
  for (i = 0; i < items->filledIndices; i++) {
    tmp[i] = items->array[origIndex];
    if (origIndex == items->size - 1) { origIndex = 0; }
    else { origIndex += 1; }
  }

  for (i = 0; i < numIterations; i++) {
    removeCDAback(items);
  }

//  items->array = realloc( items->array, sizeof(void*) );

  items->size = 1;
  items->frontIndex = 0;
  items->backIndex = 0;
  items->filledIndices = 0;

  return tmp;
}

int sizeCDA(CDA *items) {
  return items->filledIndices;
}

void visualizeCDA(FILE *fp,CDA *items) {
  fprintf(fp, "(");

  if (items->filledIndices != 0) {
    int index = 0;
    int i = items->frontIndex;
    while (index < items->filledIndices) {
      items->display(fp, items->array[i]);
      if (index != items->filledIndices - 1) { fprintf(fp, ","); }
      i += 1;
      index += 1;
      if (i == items->size) { i = 0; }
    }
  }
  fprintf(fp, ")");

  int remainder = items->size - items->filledIndices;

  fprintf(fp, "(%d)", remainder);
}

void displayCDA(FILE *fp,CDA *items) {
  fprintf(fp, "(");

  if (items->filledIndices != 0) {
    int index = 0;
    int i = items->frontIndex;
    while (index < items->filledIndices) {
      items->display(fp, items->array[i]);
      if (index != items->filledIndices - 1) { fprintf(fp, ","); }
      i += 1;
      index += 1;
      if (i == items->size) { i = 0; }
    }
  }

  fprintf(fp, ")");
}
