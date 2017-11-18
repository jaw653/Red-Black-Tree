/* Author: Jake Wachs
 * Date: 11/5/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "bst.h"
#include "string.h"
#include "rbt.h"
#include "gt.h"
#include "scanner.h"

//static bool stringIsEmpty(char *);
static char *read(FILE *);
static char *cleanString(char *);
//static bool fileIsEmpty(FILE *fp);
static void populateGT(FILE *fp, GT *tree);
static void populateRBT(FILE *fp, RBT *tree);
static void executeCommandsGT(FILE *fp, FILE *outputFile, GT *tree);
static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree);

int main(int argc, char *argv[]) {
  /* If no command line arguments */
  if (argc <= 1) {
    //print error message?
    return 0;
  }

  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) {
      printf("Jake A. Wachs\n");
      return 0;
    }
  }

  /* Reading in file names to file pointers */
  char *corpusName, *commandsName, *outputFileName;
  FILE *corpus;
  FILE *commands;
  FILE *outputFile;

  if (argc == 4) {
    if (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "-r") == 0) {
      corpusName = argv[2];
      commandsName = argv[3];
      outputFileName = NULL;
    }
    else {
      corpusName = argv[1];
      commandsName = argv[2];
      outputFileName = argv[3];
    }
  }
  else if (argc == 3) {
    corpusName = argv[1];
    commandsName = argv[2];
    outputFileName = NULL;
  }
  else if (argc == 5) {
    corpusName = argv[2];
    commandsName = argv[3];
    outputFileName = argv[4];
  }
  corpus = fopen(corpusName, "r");
  commands = fopen(commandsName, "r");
  if (outputFileName != NULL) outputFile = fopen(outputFileName, "r");
  else outputFile = NULL;

  /* Determing if rbt or gt, populating BST, and executing commands file */
  if (strcmp(argv[argc - (argc-1)], "-g") == 0) {
    GT *wordsTree = newGT(displaySTRING, compareSTRING);
    populateGT(corpus, wordsTree);
    if (outputFile == NULL) {
      executeCommandsGT(commands, stdout, wordsTree);
//      fprintf(stdout, "\n");
    }
    else {
      executeCommandsGT(commands, outputFile, wordsTree);
//      fprintf(outputFile, "\n");
    }
  }
  else {
    RBT *wordsTree = newRBT(displaySTRING, compareSTRING);
    populateRBT(corpus, wordsTree);

    if (outputFile == NULL) {
      executeCommandsRBT(commands, stdout, wordsTree);
//      fprintf(stdout, "\n");
    }
    else {
      executeCommandsRBT(commands, outputFile, wordsTree);
//      fprintf(outputFile, "\n");
    }
  }

  if (corpus) fclose(corpus);
  if (commands) fclose(commands);
  if (outputFile) fclose(outputFile);

  return 0;
}

/******************************************************************************/
/***                          Helper Functions                              ***/
/******************************************************************************/
static char *read(FILE *fp) {
  char *str;
  if (stringPending(fp))
    str = readString(fp);
  else str = readToken(fp);

  return str;
}

static char *cleanString(char *str) {
  int i;
  int j = 0;
  int len = strlen(str);

  bool isEmpty = true;

  for (i = 0; i < len; i++) {
    if (isalpha(str[i])) {
      str[j] = str[i];
      str[j] = tolower(str[j]);
      j += 1;
      isEmpty = false;
    }

    if (isspace(str[i])) {
      if (isEmpty == false) {
        if (str[j-1] != ' ') {
            str[j] = ' ';
            j += 1;
        }
      }
    }
  }

  if (isEmpty)
    return NULL;

  if (str[j-1] == ' ')
    str[j-1] = '\0';
  else
    str[j] = '\0';

  return str;
}

static char *getEntirePhrase(FILE *fp, char *str) {
  if (str[0] == '\"') {
    strcat(str, " ");
    strcat(str, readToken(fp));
    while (str[strlen(str)-1] != '\"') {
      strcat(str, " ");
      strcat(str, readToken(fp));
    }
  }

  return str;
}

/*
static bool fileIsEmpty(FILE *fp) {
  int size;
  if (fp != NULL) {
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    if (size == 0)
      return true;
    else
      return false;
  }

  //rewind(fp);
  return true;
}
*/

static void populateGT(FILE *fp, GT *tree) {
//  if (!fileIsEmpty(fp)) {
    char *str = read(fp);

    while (str) {
//printf("pre-clean str is: %s\n", str);
      str = cleanString(str);
//printf("string to be inerted is: %s\n", str);
      if (str != NULL)
        insertGT(tree, newSTRING(str));

      str = read(fp);
    }
//  }
}

static void populateRBT(FILE *fp, RBT *tree) {
  //if (!fileIsEmpty(fp)) {
    char *str = read(fp);

    while (str) {
      str = cleanString(str);
      if (str != NULL)
        insertRBT(tree, newSTRING(str));

      str = read(fp);
    }
  //}
}

/***************************** Execute Commands *******************************/
static void executeCommandsGT(FILE *fp, FILE *outputFile, GT *tree) {
  //if (!fileIsEmpty(fp)) {
    char *str = read(fp);

    while (str) {
      /* Insert to tree */
      if (strcmp(str, "i") == 0) {
        str = read(fp);
        str = cleanString(str);
        if (str != NULL)
          insertGT(tree, newSTRING(str));
      }
      /* Delete from tree */
      else if (strcmp(str, "d") == 0) {
        str = read(fp);
        str = cleanString(str);
        deleteGT(tree, newSTRING(str));
      }
      /* Report frequency */
      else if (strcmp(str, "f") == 0) {
        str = read(fp);
        str = cleanString(str);
        int freq = findGT(tree, newSTRING(str));
        fprintf(outputFile, "Frequency of %s: %d\n", str, freq);
      }
      /* Show the tree */
      else if (strcmp(str, "s") == 0) {
        displayGT(outputFile, tree);
        fprintf(outputFile, "\n");
      }
      /* Report statistics */
      else if (strcmp(str, "r") == 0) {
        statisticsGT(outputFile, tree);
        fprintf(outputFile, "\n");
      }

      str = read(fp);
    }
  //}
}

static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree) {
  //if (!fileIsEmpty(fp)) {
    char *str = read(fp);

    while (str) {
      /* Insert to tree */
      if (strcmp(str, "i") == 0) {
        str = read(fp);
        str = cleanString(str);
        if (str != NULL)
          insertRBT(tree, newSTRING(str));
      }
      /* Delete from tree */
      else if (strcmp(str, "d") == 0) {
        str = read(fp);
        str = cleanString(str);
        deleteRBT(tree, newSTRING(str));
      }
      /* Report frequency */
      else if (strcmp(str, "f") == 0) {
        str = read(fp);
        str = cleanString(str);
        int freq = findRBT(tree, newSTRING(str));
        fprintf(outputFile, "Frequency of %s: %d\n", str, freq);
      }
      /* Show the tree */
      else if (strcmp(str, "s") == 0) {
        displayRBT(outputFile, tree);
        fprintf(outputFile, "\n");
      }
      /* Report statistics */
      else if (strcmp(str, "r") == 0) {
        statisticsRBT(outputFile, tree);
        fprintf(outputFile, "\n");
      }

      str = read(fp);
    }
//  }
}
