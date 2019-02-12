
all: prime.o settings.o starter.o
	g++ -Wall src/main.cpp starter.o settings.o prime.o -lpthread -o bin/primes
	rm *.o
	
prime.o:
	g++ -c -Wall src/prime.cpp
	
settings.o:
	g++ -c -Wall src/settings.cpp

starter.o:
	g++ -c -Wall src/starter.cpp -lpthread
	
# Requires its own command for the -g option
debug:
	g++ -c -g -Wall src/prime.cpp
	g++ -c -g -Wall src/settings.cpp
	g++ -c -g -Wall src/starter.cpp -lpthread
	g++ -g -Wall src/main.cpp starter.o settings.o prime.o -lpthread -o bin/primes
	rm *.o
	
# All below	this are cleaning/clearing options

clear-bin: clean-bin
	clear
	
clear: clean
	clear
		
clean-bin: clean
	rm -f bin/*

clean:
	rm -f *.o
	rm -f src/*\.gch

	
