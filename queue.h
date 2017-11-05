/*Author: Jake Wachs (Credit: Dr. J. Lusth)
 *Date: 08/26/17
 *University of Alabama
 *
 *This file serves as the header for the queue.c file
 */

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>

typedef struct queue QUEUE;

extern QUEUE *newQUEUE(void (*d)(FILE *,void *));
extern void enqueue(QUEUE *items,void *value);
extern void *dequeue(QUEUE *items);
extern void *peekQUEUE(QUEUE *items);
extern int sizeQUEUE(QUEUE *items);
extern void displayQUEUE(FILE *,QUEUE *items);
extern void visualizeQUEUE(FILE *,QUEUE *items);

#endif
