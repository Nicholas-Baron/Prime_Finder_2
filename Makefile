
all: settings.o starter.o
	g++ -Wall -Wextra src/main.cpp starter.o settings.o -lpthread -o bin/primes
	rm *.o
	
settings.o:
	g++ -c -Wall -Wextra src/settings.cpp

starter.o:
	g++ -c -Wall -Wextra src/starter.cpp -lpthread

optimize:
	g++ -o bin/optimized -Wall -Wextra -march=native -O3 src/*.cpp -lpthread
	
# Requires its own command for the -g option
debug:
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

	
