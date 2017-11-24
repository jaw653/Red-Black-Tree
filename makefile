# Author: Jake Wachs
# Date: 10/26/2017
#
# The University of Alabama

OPTS = -Wall -Wextra -std=c99
TYPE_OBJS = string.o real.o
UTIL_OBJS = scanner.o trees.o
STRUCT_OBJS = cda.o queue.o bst.o rbt.o gt.o
#TEST_OBJS = test-bst.o test-rbt.o
TEST_EXES = bstTest rbtTest
OBJECT_BUNDLE = $(TYPE_OBJS) $(STRUCT_OBJS) $(UTIL_OBJS)
# other objs Below
# TESTOBJS = tests...

trees: $(OBJECT_BUNDLE)
	gcc $(OPTS) $(OBJECT_BUNDLE) -o ./trees

test: trees
	@./trees -g assign2Tests/trees.0 assign2Tests/trees.1 outputs/1
	@diff assign2Tests/trees.0-g.expected outputs/1
	@./trees -r assign2Tests/trees.0 assign2Tests/trees.1 outputs/2
	@diff assign2Tests/trees.0-r.expected outputs/2


	@./trees -g assign2Tests/test-1-0.corpus assign2Tests/test-1-0.go outputs/3
	@diff assign2Tests/test-1-0.corpus-g.expected outputs/3
	@./trees -r assign2Tests/test-1-0.corpus assign2Tests/test-1-0.go outputs/4
	@diff assign2Tests/test-1-0.corpus-r.expected outputs/4


	@./trees -g assign2Tests/test-1-1.corpus assign2Tests/test-1-1.go outputs/5
	@diff assign2Tests/test-1-1.corpus-g.expected outputs/5
	@./trees -r assign2Tests/test-1-1.corpus assign2Tests/test-1-1.go outputs/6
	@diff assign2Tests/test-1-1.corpus-r.expected outputs/6

	@./trees -g assign2Tests/test-1-2.corpus assign2Tests/test-1-2.go outputs/7
	@diff assign2Tests/test-1-2.corpus-g.expected outputs/7
	@./trees -r assign2Tests/test-1-2.corpus assign2Tests/test-1-2.go outputs/8
	@diff assign2Tests/test-1-2.corpus-r.expected outputs/8

	@./trees -g assign2Tests/test-1-3.corpus assign2Tests/test-1-3.go outputs/9
	@diff assign2Tests/test-1-3.corpus-g.expected outputs/9
	@./trees -r assign2Tests/test-1-3.corpus assign2Tests/test-1-3.go outputs/10
	@diff assign2Tests/test-1-3.corpus-r.expected outputs/10

	@./trees -g assign2Tests/test-1-4.corpus assign2Tests/test-1-4.go outputs/11
	@diff assign2Tests/test-1-4.corpus-g.expected outputs/11
	@./trees -r assign2Tests/test-1-4.corpus assign2Tests/test-1-4.go outputs/12
	@diff assign2Tests/test-1-4.corpus-r.expected outputs/12

# New Stuff

	@./trees -g assign2Tests/test-1-5.corpus assign2Tests/test-1-5.go outputs/13
	@diff assign2Tests/test-1-5.corpus-g.expected outputs/13
	@./trees -r assign2Tests/test-1-5.corpus assign2Tests/test-1-5.go outputs/14
	@diff assign2Tests/test-1-5.corpus-r.expected outputs/14

	@./trees -g assign2Tests/test-1-6.corpus assign2Tests/test-1-6.go outputs/15
	@diff assign2Tests/test-1-6.corpus-g.expected outputs/15
	@./trees -r assign2Tests/test-1-6.corpus assign2Tests/test-1-6.go outputs/16
	@diff assign2Tests/test-1-6.corpus-r.expected outputs/16

	@./trees -g assign2Tests/test-1-7.corpus assign2Tests/test-1-7.go outputs/17
	@diff assign2Tests/test-1-7.corpus-g.expected outputs/17
	@./trees -r assign2Tests/test-1-7.corpus assign2Tests/test-1-7.go outputs/18
	@diff assign2Tests/test-1-7.corpus-r.expected outputs/18

	@./trees -g assign2Tests/test-1-8.corpus assign2Tests/test-1-8.go outputs/19
	@diff assign2Tests/test-1-8.corpus-g.expected outputs/19
	@./trees -r assign2Tests/test-1-8.corpus assign2Tests/test-1-8.go outputs/20
	@diff assign2Tests/test-1-8.corpus-r.expected outputs/20

	@./trees -g assign2Tests/test-1-9.corpus assign2Tests/test-1-9.go outputs/21
	@diff assign2Tests/test-1-9.corpus-g.expected outputs/21
	@./trees -r assign2Tests/test-1-9.corpus assign2Tests/test-1-9.go outputs/22
	@diff assign2Tests/test-1-9.corpus-r.expected outputs/22

	@./trees -g assign2Tests/test-1-10.corpus assign2Tests/test-1-10.go outputs/23
	@diff assign2Tests/test-1-10.corpus-g.expected outputs/23
	@./trees -r assign2Tests/test-1-10.corpus assign2Tests/test-1-10.go outputs/24
	@diff assign2Tests/test-1-10.corpus-r.expected outputs/24

	@./trees -g assign2Tests/test-1-11.corpus assign2Tests/test-1-11.go outputs/25
	@diff assign2Tests/test-1-11.corpus-g.expected outputs/25
	@./trees -r assign2Tests/test-1-11.corpus assign2Tests/test-1-11.go outputs/26
	@diff assign2Tests/test-1-11.corpus-r.expected outputs/26

	@./trees -g assign2Tests/test-1-12.corpus assign2Tests/test-1-12.go outputs/27
	@diff assign2Tests/test-1-12.corpus-g.expected outputs/27
	@./trees -r assign2Tests/test-1-12.corpus assign2Tests/test-1-12.go outputs/28
	@diff assign2Tests/test-1-12.corpus-r.expected outputs/28

	@./trees -g assign2Tests/test-1-13.corpus assign2Tests/test-1-13.go outputs/29
	@diff assign2Tests/test-1-13.corpus-g.expected outputs/29
	@./trees -r assign2Tests/test-1-13.corpus assign2Tests/test-1-13.go outputs/30
	@diff assign2Tests/test-1-13.corpus-r.expected outputs/30

	@./trees -g assign2Tests/test-1-14.corpus assign2Tests/test-1-14.go outputs/31
	@diff assign2Tests/test-1-14.corpus-g.expected outputs/31
	@./trees -r assign2Tests/test-1-14.corpus assign2Tests/test-1-14.go outputs/32
	@diff assign2Tests/test-1-14.corpus-r.expected outputs/32

#---------------------

	@./trees -g assign2Tests/beowulf.txt assign2Tests/beowulf.go1 outputs/32
	@diff assign2Tests/beowulf.txt-g.expected outputs/32
	@./trees -r assign2Tests/beowulf.txt assign2Tests/beowulf.go1 outputs/33
	@diff assign2Tests/beowulf.txt-r.expected outputs/33

	@./trees -g assign2Tests/beowulf.txt assign2Tests/beowulf.go2 outputs/g-beowulf
	@diff assign2Tests/beowulf-g.expected outputs/g-beowulf
	@./trees -r assign2Tests/beowulf.txt assign2Tests/beowulf.go2 outputs/r-beowulf
	@diff assign2Tests/beowulf-r.expected outputs/r-beowulf

	@./trees -g assign2Tests/shakespeare.txt assign2Tests/shakespeare.go1 outputs/34
	@diff assign2Tests/shakespeare.txt-g.expected outputs/34
	@./trees -r assign2Tests/shakespeare.txt assign2Tests/shakespeare.go1 outputs/35
	@diff assign2Tests/shakespeare.txt-r.expected outputs/35

	@./trees -g assign2Tests/shakespeare.txt assign2Tests/shakespeare.go2 outputs/g-shakespeare
	@diff assign2Tests/shakespeare-g.expected outputs/g-shakespeare
	@./trees -r assign2Tests/shakespeare.txt assign2Tests/shakespeare.go2 outputs/r-shakespeare
	@diff assign2Tests/shakespeare-r.expected outputs/r-shakespeare


trees.o: trees.c
	gcc $(OPTS) trees.c -c

bst.o: bst.c bst.h
	gcc $(OPTS) bst.c -c

rbt.o: rbt.c rbt.h
	gcc $(OPTS) rbt.c -c

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
	rm -rf *.o $(TEST_EXES) ./a.out trees

#******************************************************************************#
# *** TEST OBJECTS *** #
#******************************************************************************#
#test-bst.o: $(OBJECT_BUNDLE)
#	gcc $(OPTS) bst.o real.o queue.o cda.o bstTest.c  -o bstTest

#test-rbt.o: $(OBJECT_BUNDLE)
#	gcc $(OPTS) rbtTest.c rbt.o bst.o real.o cda.o queue.o  -o rbtTest

#test-0.o: $(OBJECT_BUNDLE)
