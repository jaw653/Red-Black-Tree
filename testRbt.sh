!#\bin\bash

make

gcc -Wall -Wextra -std=c99 rbtTest.c rbt.o cda.o queue.o rbtnode.o -lm

./a.out
