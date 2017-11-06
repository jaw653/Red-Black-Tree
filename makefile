# Author: Jake Wachs
# Date: 10/26/2017
# The University of Alabama

OPTS = -Wall -Wextra -std=c99
OBJS = bst.o rbt.o string.o queue.o scanner.o cda.o gt.o trees.o real.o
# other objs Below
# TESTOBJS = tests...
TESTEXES = runBSTtest

trees: $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees -lm

test: trees
	#./bstTest
	trees

trees.o: trees.c
	gcc $(OPTS) trees.c -c

bst.o: bst.c bst.h
	gcc $(OPTS) -c bst.c -lm

rbt.o: rbt.c rbt.h
	gcc $(OPTS) rbt.c -c

rbtnode.o: rbtnode.c rbtnode.h
	gcc $(OPTS) rbtnode.c -c

gt.o: gt.c gt.h
	gcc $(OPTS) gt.c -c

queue.o: queue.c queue.h
	gcc $(OPTS) queue.c -c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) scanner.c -c

cda.o: cda.c cda.h
	gcc $(OPTS) cda.c -c

string.o: string.c string.h
	gcc $(OPTS) -c string.c

real.o: real.c real.h
	gcc $(OPTS) -c real.c

clean:
	rm -rf *.o $(TESTEXES) ./a.out trees bstTest

#******************************************************************************#
# *** TEST OBJECTS *** #
#******************************************************************************#
test-bst.o: bst.o
	gcc $(OPTS) $(OBJS) bstTest.c -lm -o bstTest
