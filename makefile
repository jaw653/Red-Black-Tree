# Author: Jake Wachs
# Date: 10/26/2017
# The University of Alabama

OPTS = -Wall -Wextra -std=c99
TYPE_OBJS = real.o string.o
UTIL_OBJS = scanner.o trees.o
STRUCT_OBJS = cda.o queue.o bst.o rbt.o gt.o
TEST_OBJS = test-bst.o test-rbt.o
TEST_EXES = bstTest rbtTest
OBJECT_BUNDLE = $(TYPE_OBJS) $(STRUCT_OBJS) $(UTIL_OBJS)
# other objs Below
# TESTOBJS = tests...

trees: $(OBJECT_BUNDLE)
	gcc $(OPTS) $(OBJECT_BUNDLE) -o trees -lm

test: trees $(TEST_OBJS)
	#./bstTest
	./rbtTest
	#./trees

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
	rm -rf *.o $(TEST_EXES) ./a.out trees

#******************************************************************************#
# *** TEST OBJECTS *** #
#******************************************************************************#
test-bst.o: $(OBJECT_BUNDLE)
	gcc $(OPTS) bst.o real.o queue.o cda.o bstTest.c -lm -o bstTest

test-rbt.o: $(OBJECT_BUNDLE)
	gcc $(OPTS) rbtTest.c rbt.o bst.o real.o cda.o queue.o -lm -o rbtTest
