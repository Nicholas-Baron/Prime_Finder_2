
all: prime.o settings.o
	g++ -Wall src/main.cpp src/settings.hpp settings.o src/prime.hpp prime.o -o bin/primes
		
prime.o:
	g++ -c -Wall src/prime.cpp src/prime.hpp
	
settings.o:
	g++ -c -Wall src/settings.hpp src/settings.cpp
		
clean:
	rm -f bin/*
	rm -f *.o
	rm -f src/*\.gch
	clear
	
