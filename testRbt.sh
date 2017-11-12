!#\bin\bash

printf "MAKING...\n"
make
printf "MADE.\n"

printf "COMPILING...\n"
gcc -Wall -Wextra -std=c99 rbtTest.c rbt.o bst.o real.o cda.o queue.o -lm
printf "COMPILED.\n"

printf "EXECUTING...\n"
./a.out
printf "EXECUTED.\n"

printf "CLEANING...\n"
make clean

