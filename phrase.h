/* Author: Jake Wachs
 * Wrapper for PHRASE data typedef
 */

#ifndef __PHRASE_INCLUDED__
#define __PHRASE_INCLUDED__

#include <stdio.h>

typedef struct PHRASE PHRASE;

extern PHRASE *newPHRASE(char *);
extern char *getPHRASE(PHRASE *);
extern char *setPHRASE(PHRASE *, char *);
extern void displayPHRASE(FILE *, void *);
extern void freePHRASE(PHRASE *);
extern char getPHRASEcolor(PHRASE *);
extern void setPHRASEcolor(PHRASE *, char);
extern int comparePHRASE(void *, void *);
//swapPHRASE

#endif
