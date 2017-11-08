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
	./trees

trees.o: trees.c
	gcc $(OPTS) trees.c -c -lm

bst.o: bst.c bst.h
	gcc $(OPTS) -c bst.c -lm

rbt.o: rbt.c rbt.h
	gcc $(OPTS) rbt.c -c -lm

rbtnode.o: rbtnode.c rbtnode.h
	gcc $(OPTS) rbtnode.c -c -lm

gt.o: gt.c gt.h
	gcc $(OPTS) gt.c -c -lm

queue.o: queue.c queue.h
	gcc $(OPTS) queue.c -c -lm

scanner.o: scanner.c scanner.h
	gcc $(OPTS) scanner.c -c -lm

cda.o: cda.c cda.h
	gcc $(OPTS) cda.c -c -lm

string.o: string.c string.h
	gcc $(OPTS) -c string.c -lm

real.o: real.c real.h
	gcc $(OPTS) -c real.c -lm

clean:
	rm -rf *.o $(TESTEXES) ./a.out trees bstTest

#******************************************************************************#
# *** TEST OBJECTS *** #
#******************************************************************************#
test-bst.o: bst.o
	gcc $(OPTS) $(OBJS) bstTest.c -lm -o bstTest -lm
