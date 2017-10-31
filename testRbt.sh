!#\bin\bash

make

gcc -Wall -Wextra -std=c99 rbtTest.c rbt.o rbtnode.o

./a.out
