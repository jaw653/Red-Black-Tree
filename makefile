# Author: Jake Wachs
# Date: 10/26/2017
# The University of Alabama

OPTS = -Wall -Wextra -std=c99
OBJS = bst.o rbt.o integer.o string.o real.o rbtnode.o queue.o scanner.o cda.o gt.o gtnode.o
TYPE_OBJS = integer.o real.o string.o
# other objs Below
# TESTOBJS = tests...
TESTEXES = runBSTtest

all: $(OBJS)

# test: $(OBJS) $(TESTOBJS)

bst.o: bst.c bst.h
	gcc $(OPTS) -c bst.c

rbt.o: rbt.c rbt.h
	gcc $(OPTS) rbt.c -c

rbtnode.o: rbtnode.c rbtnode.h
	gcc $(OPTS) rbtnode.c -c

gt.o: gt.c gt.h
	gcc $(OPTS) gt.c -c

gtnode.o: gtnode.c gtnode.h
	gcc $(OPTS) gtnode.c -c

queue.o: queue.c queue.h
	gcc $(OPTS) queue.c -c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) scanner.c -c

cda.o: cda.c cda.h
	gcc $(OPTS) cda.c -c

integer.o: integer.c integer.h
	gcc $(OPTS) -c integer.c

string.o: string.c string.h
	gcc $(OPTS) -c string.c

real.o: real.c real.h
	gcc $(OPTS) -c real.c

clean:
	rm -rf *.o $(TESTEXES) ./a.out
