#!/bin/bash

# Testing script

make clear

make -j

make clean

echo -e "\nFirst test \n"
time ./bin/primes 2999

echo -e "\nSecond test \n"
time ./bin/primes 29 -d

echo -e "\nThird test \n"
time ./bin/primes 9999 -s

