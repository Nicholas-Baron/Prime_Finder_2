#include "prime.hpp"
#include "settings.hpp"

#include <iostream>	// cout

int main(int arg_count, const char** args){

	const auto settings = parse_settings(arg_count, args);
	
	if(settings.debug_mode){
		std::cout << settings << std::endl;
	}
	
	std::cout << is_prime(settings.range_end) << std::endl;
	
}
