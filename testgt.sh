!#\bin\bash

printf "\nMAKING...\n"
make
printf "MADE.\n"

printf "COMPILING...\n"
gcc -Wall -Wextra -std=c99 gtTest.c gt.o bst.o real.o cda.o queue.o -lm
printf "COMPILED.\n"

printf "\nEXECUTING...\n"
./a.out
printf "EXECUTED.\n"

printf "CLEANING...\n\n"
make clean
