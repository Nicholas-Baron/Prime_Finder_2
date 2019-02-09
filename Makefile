
all: prime.o settings.o starter.o
	g++ -Wall src/main.cpp starter.o settings.o prime.o -lpthread -o bin/primes
		
prime.o:
	g++ -c -Wall src/prime.cpp
	
settings.o:
	g++ -c -Wall src/settings.cpp

starter.o:
	g++ -c -Wall src/starter.cpp -lpthread
	
clear-bin: clean-bin
	clear
	
clear: clean
	clear
		
clean-bin: clean
	rm -f bin/*

clean:
	rm -f *.o
	rm -f src/*\.gch

	
