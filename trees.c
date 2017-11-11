/* Author: Jake Wachs
 * Date: 11/5/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bst.h"
#include "string.h"
#include "rbt.h"
#include "gt.h"
#include "scanner.h"

static char *removeQuotes(char *);
static bool fileIsEmpty(FILE *fp);
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

  printf("corpus name is: %s\n", corpusName);
  printf("commandsName is: %s\n", commandsName);
  printf("outputFileName is: %s\n", outputFileName);

  corpus = fopen(corpusName, "r");
  commands = fopen(commandsName, "r");
  if (outputFileName != NULL) outputFile = fopen(outputFileName, "r");
  else outputFile = NULL;


  if (strcmp(argv[argc - (argc-1)], "-g") == 0) {
    GT *wordsTree = newGT(displaySTRING, compareSTRING);
    populateGT(corpus, wordsTree);
    if (outputFile == NULL)
      executeCommandsGT(commands, stdout, wordsTree);
    else
      executeCommandsGT(commands, outputFile, wordsTree);
  }
  else {
    RBT *wordsTree = newRBT(displaySTRING, compareSTRING);
    populateRBT(corpus, wordsTree);

    if (outputFile == NULL)
      executeCommandsRBT(commands, stdout, wordsTree);
    else
      executeCommandsRBT(commands, outputFile, wordsTree);
  }

  if (corpus) fclose(corpus);
  if (commands) fclose(commands);
  if (outputFile) fclose(outputFile);

  return 0;
}

static char *getEntirePhrase(FILE *fp, char *str) {
  if (str[0] == '"') {
    while (str[strlen(str) - 1] != '"') {
      strcat(str, " ");
      strcat(str, readToken(fp));
    }
    str = removeQuotes(str);
  }

  return str;
}
static char *removeQuotes(char *str) {
  int len = strlen(str);
  int i;
  char *newStr = malloc(sizeof(char) * 1000);

  for (i = 1; i < len-1; i++) {
    newStr[i-1] = str[i];
  }

  return newStr;
}

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

  rewind(fp);
  return true;
}

static void populateGT(FILE *fp, GT *tree) {
  if (!fileIsEmpty(fp)) {
    char *str = readToken(fp);

    while (str) {
      char *s = readToken(fp);
      STRING *value = newSTRING(s);

      insertGT(tree, value);

      str = readToken(fp);
    }
  }
}

static void populateRBT(FILE *fp, RBT *tree) {
  if (!fileIsEmpty(fp)) {
    char *str = readToken(fp);

    while (str) {
      if (str) break;
      char *s = readToken(fp);
      STRING *value = newSTRING(s);

      insertRBT(tree, value);

      str = readToken(fp);
    }
  }
}

static void executeCommandsGT(FILE *fp, FILE *outputFile, GT *tree) {
  //if (!fileIsEmpty(fp)) {
    char *str = readToken(fp);

    while (str) {
      /* Insert to tree */
      if (strcmp(str, "i") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);
        insertGT(tree, newSTRING(str));
      }
      /* Delete from tree */
      else if (strcmp(str, "d") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);
        deleteGT(tree, newSTRING(str));
      }
      /* Report frequency */
      else if (strcmp(str, "f") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);
        int freq = findGT(tree, newSTRING(str));
        fprintf(outputFile, "Frequency of %s is: %d\n", str, freq);
      }
      /* Show the tree */
      else if (strcmp(str, "s") == 0) {
        displayGT(outputFile, tree);
      }
      /* Report statistics */
      else if (strcmp(str, "r") == 0) {
        statisticsGT(outputFile, tree);
      }

      str = readToken(fp);
    }
  //}
}

static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree) {
  //if (!fileIsEmpty(fp)) {
    char *str = readToken(fp);

    while (str) {
      /* Insert to tree */
      if (strcmp(str, "i") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);

        insertRBT(tree, newSTRING(str));
      }
      /* Delete from tree */
      else if (strcmp(str, "d") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);

        deleteRBT(tree, newSTRING(str));
      }
      /* Report frequency */
      else if (strcmp(str, "f") == 0) {
        str = readToken(fp);
        str = getEntirePhrase(fp, str);

        int freq = findRBT(tree, newSTRING(str));
        fprintf(outputFile, "Frequency of %s is: %d\n", str, freq);
      }
      /* Show the tree */
      else if (strcmp(str, "s") == 0) {
        displayRBT(outputFile, tree);
      }
      /* Report statistics */
      else if (strcmp(str, "r") == 0) {
        statisticsRBT(outputFile, tree);
      }

      str = readToken(fp);
    }
//  }
}
