#include "starter.hpp"

void fill_prime_queue(std::queue<primality_t>& results, 
						const Settings& settings){
	
	if(settings.single_mode){
	
		results.push(is_prime(settings.range_end));
	
	}else{
	
		results.push(is_prime(2));
		
		for(prime_t i = 3; i <= settings.range_end; i += 2){
			results.push(is_prime(i));
		}
	}
}

