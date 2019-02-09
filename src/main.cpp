#include "prime.hpp"
#include "settings.hpp"
#include "starter.hpp"

#include <iostream>	// cout
#include <queue>

int main(int arg_count, const char** args){

	const auto settings = parse_settings(arg_count, args);
	
	if(settings.debug_mode){
		std::cout << settings << std::endl;
	}
	
	std::queue<primality_t> prime_queue;
	fill_prime_queue(prime_queue, settings);
	
	while(!prime_queue.empty()){
		const auto prime_state = prime_queue.front();
		prime_queue.pop();
		
		std::cout << prime_state << std::endl;
	}
}
