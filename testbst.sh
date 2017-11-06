#! \bin\bash
printf "MAKING...\n"
make
printf "MADE.\n"

printf "COMPILING...\n"
gcc -Wall -Wextra -std=c99 bst.o real.o queue.o cda.o bstTest.c -lm
printf "COMPILED.\n"

printf "EXECUTING...\n"
./a.out
printf "EXECUTED.\n"

printf "MAKING CLEAN...\n"
make clean
printf "CLEAN\n"
