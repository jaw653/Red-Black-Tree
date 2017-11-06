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

int main(int argc, char *argv[]) {

  /* If no command line arguments */
  if (argc == 1) {
    //print error message?
    return 0;
  }

  char *corpusName, *commandsName;
  FILE *corpus, *commands;
  if (argc == 4) {
    corpusName = argv[argc-2];
    commandsName = argv[argc-1];
  }
  else if (argc == 5) {
    corpusName = argv[argc - 3];
    commandsName = argv[argc-2];
  }

  corpus = fopen(corpusName, "r");
  commands = fopen(commandsName, "r");

  //read info in, populate tree(s)?

  if (corpus) fclose(corpus);
  if (commands) fclose(commands);

  if (strcmp(argv[argc - (argc-1)], "-g") == 0) {
    //green tree opts
  }
  else {
    //red/black tree opts
  }

  return 0;
}
