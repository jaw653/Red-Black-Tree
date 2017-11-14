!#\bin\bash

printf "\nMAKING...\n"
make
printf "\nMADE.\n"

printf "COMPILING...\n"
gcc -Wall -Wextra -std=c99 rbtTest.c rbt.o bst.o real.o cda.o queue.o -lm
printf "COMPILED.\n"

printf "EXECUTING...\n\n"
./a.out
printf "EXECUTED.\n\n"

printf "CLEANING...\n\n"
make clean
