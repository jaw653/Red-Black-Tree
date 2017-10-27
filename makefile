# Author: Jake Wachs
# Date: 10/26/2017
# The University of Alabama

OPTS = -Wall -Wextra -std=c99
OBJS = bst.o integer.o string.o real.o
TYPE_OBJS = integer.o real.o string.o
# other objs Below
# TESTOBJS = tests...
TESTEXES = runBSTtest

all: $(OBJS)

# test: $(OBJS) $(TESTOBJS)

bst.o: bst.c bst.h
	gcc $(OPTS) -c bst.c

integer.o: integer.c integer.h
	gcc $(OPTS) -c integer.c

string.o: string.c string.h
	gcc $(OPTS) -c string.c

real.o: real.c real.h
	gcc $(OPTS) -c real.c

clean:
	rm -rf *.o $(TESTEXES) ./a.out
