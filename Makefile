all:
	g++ -Wall src/main.cpp src/settings.hpp -o bin/primes
	
clean-bin:
	rm bin/*
	
	
