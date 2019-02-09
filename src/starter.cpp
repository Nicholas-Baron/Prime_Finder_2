#include "starter.hpp"

#include <iostream>	// cerr
#include <stdexcept>

inline std::future<primality_t> start_prime(prime_t val){
	return std::async(is_prime, val);
}

void fill_prime_queue(std::queue<std::future<primality_t>>& results, 
						const Settings& settings, std::atomic<bool>& running){
	
	running = true;
	
	if(settings.single_mode){
	
		results.push(start_prime(settings.range_end));
	
	}else{
	
		results.push(start_prime(2));
		try{
			for(prime_t i = 3; i <= settings.range_end; i += 2){
				results.push(start_prime(i));
			}
		}catch(const std::exception& e){
			std::cerr << "[Starter] Error: " << e.what() << std::endl;
		}
	}
	
	running = false;
}

