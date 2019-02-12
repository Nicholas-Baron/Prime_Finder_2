#include "starter.hpp"

#include <iostream>		// cerr
#include <stdexcept>	// exception

// Helper to start the thread
inline std::future<primality_t> start_prime(prime_t val){
	return std::async(is_prime, val);
}

void fill_prime_queue(std::queue<std::future<primality_t>>& results, 
						const Settings& settings, std::atomic<bool>& running){
	
	running = true;
	
	if(settings.single_mode) {
		// Move the range end value that was specified as the only value to check
		results.push(start_prime(settings.range_end));
	
	} else {
		// Two is the only even prime number
		results.push(start_prime(2));
		try{
			// Check every odd number for primality
			for(prime_t i = 3; i <= settings.range_end; i += 2){
				results.push(start_prime(i));
			}
		}catch(const std::exception& e){
			std::cerr << "[Starter] Error: " << e.what() << std::endl;
		}
	}
	
	// Signal that the starter is finish 
	running = false;
}

