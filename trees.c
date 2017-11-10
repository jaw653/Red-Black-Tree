/* Author: Jake Wachs
 * Date: 11/5/2017
 * The University of Alabama
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "bst.h"
#include "string.h"
#include "rbt.h"
#include "gt.h"
#include "scanner.h"

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

  printf("corpus name is: %s\n", corpusName);
  printf("commandsName is: %s\n", commandsName);
  printf("outputFileName is: %s\n", outputFileName);

  corpus = fopen(corpusName, "r");
  commands = fopen(commandsName, "r");
  if (outputFileName != NULL) outputFile = fopen(outputFileName, "r");
  else outputFile = NULL;


  if (strcmp(argv[argc - (argc-1)], "-g") == 0) {
    printf("option is -g\n");
    GT *wordsTree = newGT(displaySTRING, compareSTRING);
    populateGT(corpus, wordsTree);

    if (outputFile == NULL)
      executeCommandsGT(commands, stdout, wordsTree);
    else
      executeCommandsGT(commands, outputFile, wordsTree);
  }
  else {
    printf("option is -r\n");
    RBT *wordsTree = newRBT(displaySTRING, compareSTRING);
    populateRBT(corpus, wordsTree);

    if (outputFile == NULL)
      executeCommandsRBT(commands, stdout, wordsTree);
    else
      printf("else\n"); executeCommandsRBT(commands, outputFile, wordsTree);
  }

  if (corpus) fclose(corpus);
  if (commands) fclose(commands);
  if (outputFile) fclose(outputFile);

  return 0;
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
  if (!fileIsEmpty(fp)) {
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
      else if (strcmp(str, "d") == 0) {
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
}

static void executeCommandsRBT(FILE *fp, FILE *outputFile, RBT *tree) {
  if (!fileIsEmpty(fp)) {
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
      else if (strcmp(str, "d") == 0) {
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
}
