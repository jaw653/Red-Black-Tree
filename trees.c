/* Author: Jake Wachs
 * Date: 11/5/2017
 * The University of Alabama
 */

/*
 * Questions:
            -should i print an error message if there are no cmdln args? or should I do something anyway
            -need to check to handle empty files
 */

#include <stdio.h>
#include <string.h>

#include "bst.h"
#include "rbt.h"
#include "gt.h"

static void populateGT(FILE *fp, GT *tree);
static void populateRBT(FILE *fp, RBT *tree);
static void executeCommandsGT(FILE *fp, FILE *outputFile, GT *tree);
static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree);

int main(int argc, char *argv[]) {
  /* If no command line arguments */
  if (argc == 1) {
    //print error message?
    return 0;
  }

  char *corpusName, *commandsName, *outputFileName;
  FILE *corpus, *commands, *outputFile;
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

  //read corpus text into bst
  BST *wordsTree;

  if (strcmp(argv[argc - (argc-1)], "-g") == 0) {
    wordsTree = newGT(displaySTRING, compareSTRING);
    populateGT(corpus, wordsTree);
    executeCommandsGT(commands, outputFile, wordsTree);
    //read in and complete commands
  }
  else {
    wordsTree = newRBT(displaySTRING, compareSTRING);
    populateRBT(corpus, wordsTree);
    executeCommandsRBT(commands, outputFile, wordsTree);
  }

  if (corpus) fclose(corpus);
  if (commands) fclose(commands);

  return 0;
}

static void populateGT(FILE *fp, GT *tree) {
  char *str = readToken(fp);

  while (str) {
    if (strcmp(str, "var") == 0) {
      char *s = readToken(fp);
      STRING *value = newSTRING(s);

      insertGT(tree, value);
    }

    str = readToken(fp);
  }
}

static void populateRBT(FILE *fp, RBT *tree) {
  char *str = readToken(fp);

  while (str) {
    if (strcmp(str, "var") == 0) {
      char *s = readToken(fp);
      STRING *value = newSTRING(s);

      insertRBT(tree, value);
    }

    str = readToken(fp);
  }
}

static void executeCommandsGT(FILE *fp, FILE *outputFile, GT *tree) {
  char *str = readToken(fp);

  while (str) {
    /* Insert to tree */
    if (strcmp(str, "i") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      insertGT(tree, newSTRING(obj));
    }
    /* Delete from tree */
    else if (strmpc(str, "d") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      deleteGT(tree, newSTRING(obj));
    }
    /* Report frequency */
    else if (strcmp(str, "f") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      int freq = findGT(tree, newSTRING(obj));
      fprintf(outputFile, "Frequency of %s is: %d\n", obj, freq);
    }
    /* Show the tree */
    else if (strcmp(str, "s") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      displayGT(outputFile, tree);
    }
    /* Report statistics */
    else if (strcmp(str, "r") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      statisticsGT(outputFile, tree);
    }

    str = readToken(fp);
  }
}

static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree) {
  char *str = readToken(fp);

  while (str) {
    /* Insert to tree */
    if (strcmp(str, "i") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      insertRBT(tree, newSTRING(obj));
    }
    /* Delete from tree */
    else if (strmpc(str, "d") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      deleteRBT(tree, newSTRING(obj));
    }
    /* Report frequency */
    else if (strcmp(str, "f") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      int freq = findRBT(tree, newSTRING(obj));
      fprintf(outputFile, "Frequency of %s is: %d\n", obj, freq);
    }
    /* Show the tree */
    else if (strcmp(str, "s") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      displayRBT(outputFile, tree);
    }
    /* Report statistics */
    else if (strcmp(str, "r") == 0) {
      char *obj = readToken(fp);
      if (obj[0] == '"') {
        strcat(obj, readToken(fp));
      }
      statisticsRBT(outputFile, tree);
    }

    str = readToken(fp);
  }
}
