#include "prime.hpp"
#include "settings.hpp"
#include "starter.hpp"

#include <iostream>	// cout
#include <queue>
#include <thread>

int main(int arg_count, const char** args){

	const auto settings = parse_settings(arg_count, args);
	
	using namespace std;
	
	if(settings.debug_mode){
		cout << settings << endl;
	}
	
	queue<primality_t> prime_queue;
	
	thread starter(fill_prime_queue, 
					ref(prime_queue), ref(settings));
	
	// Wait until there is at least one thing in the queue
	while(prime_queue.empty()){
		this_thread::yield();
	}
	
	while(!prime_queue.empty()){
		const auto prime_state = prime_queue.front();
		prime_queue.pop();
		
		cout << prime_state << endl;
	}
	
	starter.join();
}
