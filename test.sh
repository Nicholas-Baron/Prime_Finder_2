#!/bin/bash

# Testing script

make clean

make -j

echo -e "\nFirst test \n"
./bin/primes 29

echo -e "\nSecond test \n"
time ./bin/primes 299 -d
