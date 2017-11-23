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
	@#./trees -g assign2Tests/trees.0 assign2Tests/trees.1
	@#./trees -r assign2Tests/trees.0 assign2Tests/trees.1
	@#./trees -g assign2Tests/test-0-0.corpus assign2Tests/test-0-0.go
	@#./trees -r assign2Tests/test-0-0.corpus assign2Tests/test-0-0.go
	@#./trees -g assign2Tests/test-0-1.corpus assign2Tests/test-0-1.go
	@#./trees -r assign2Tests/test-0-1.corpus assign2Tests/test-0-1.go
	@#./trees -g assign2Tests/test-0-2.corpus assign2Tests/test-0-2.go
	@#./trees -r assign2Tests/test-0-2.corpus assign2Tests/test-0-2.go
	@#./trees -g assign2Tests/test-0-3.corpus assign2Tests/test-0-3.go
	@#./trees -r assign2Tests/test-0-3.corpus assign2Tests/test-0-3.go
	@#./trees -g assign2Tests/test-0-4.corpus assign2Tests/test-0-4.go
	@#./trees -r assign2Tests/test-0-4.corpus assign2Tests/test-0-4.go

	@#./trees -g assign2Tests/test-0-5.corpus assign2Tests/test-0-5.go
	@#./trees -r assign2Tests/test-0-5.corpus assign2Tests/test-0-5.go

	@#./trees -g assign2Tests/test-0-6.corpus assign2Tests/test-0-6.go
	@#./trees -r assign2Tests/test-0-6.corpus assign2Tests/test-0-6.go problem files

	@#./trees -g assign2Tests/test-0-7.corpus assign2Tests/test-0-7.go
	@#./trees -r assign2Tests/test-0-7.corpus assign2Tests/test-0-7.go
	@#./trees -g assign2Tests/test-0-8.corpus assign2Tests/test-0-8.go
	@#./trees -r assign2Tests/test-0-8.corpus assign2Tests/test-0-8.go
	@#./trees -g assign2Tests/test-0-9.corpus assign2Tests/test-0-9.go
	@#./trees -r assign2Tests/test-0-9.corpus assign2Tests/test-0-9.go
	@#./trees -g assign2Tests/test-0-10.corpus assign2Tests/test-0-10.go
	@#./trees -r assign2Tests/test-0-10.corpus assign2Tests/test-0-10.go
	@#./trees -g assign2Tests/test-0-11.corpus assign2Tests/test-0-11.go
	@./trees -r assign2Tests/test-0-11.corpus assign2Tests/test-0-11.go
	@#./trees -g assign2Tests/test-0-12.corpus assign2Tests/test-0-12.go
	@#./trees -r assign2Tests/test-0-12.corpus assign2Tests/test-0-12.go
	@#./trees -g assign2Tests/test-0-13.corpus assign2Tests/test-0-13.go
	@#./trees -r assign2Tests/test-0-13.corpus assign2Tests/test-0-13.go
	@#./trees -g assign2Tests/test-0-14.corpus assign2Tests/test-0-14.go
	@#./trees -r assign2Tests/test-0-14.corpus assign2Tests/test-0-14.go

	@#./trees -g assign2Tests/beowulf.txt assign2Tests/beowulf.go1
	@#./trees -r assign2Tests/beowulf.txt assign2Tests/beowulf.go1

	@#./trees -g assign2Tests/beowulf.txt assign2Tests/beowulf.go2 outputs/g-beowulf
	@#./trees -r assign2Tests/beowulf.txt assign2Tests/beowulf.go2 outputs/r-beowulf

	@#./trees -g assign2Tests/shakespeare.txt assign2Tests/shakespeare.go1
	@#./trees -r assign2Tests/shakespeare.txt assign2Tests/shakespeare.go1

	@#./trees -g assign2Tests/shakespeare.txt assign2Tests/shakespeare.go2
	@#./trees -r assign2Tests/shakespeare.txt assign2Tests/shakespeare.go2 outputs/r-shake2


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
