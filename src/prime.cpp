#include "prime.hpp"

primality_t is_prime(const prime_t val){

	using std::make_pair;

	// This lambda is a helper to make the code more expressive.
	const auto prime_pair = [val](bool primal) -> primality_t {
		return make_pair(val, primal);
	};
	
	// This macro simplifies the typing for a return statement in this function.
#define ret(x) return prime_pair(x)

	// The prime numbers smaller than 15 are as follows:
	// 2, 3, 5, 7, 11, 13
	// All evens except 2 are not prime
	// All odds less than 15 except 1 and 9 are prime
	if(val <= 14){
		switch(val){
			case 2: ret(true);
			case 1:
			case 9: ret(false);
			default: ret(val%2 == 1);
		}
	}
	
	// Common multiples: 2, 3, 5 
	// The last digit of a number divisible by 5 is either 0 or 5
	// NOTE: The assembly generated for % 3 and % 5 are unoptimal.
	if(val % 2 == 0 || val % 3 == 0 || val % 10 == 5){
		ret(false);
	}
	
	// Checks every odd number upto the lowest possible option 
	// from the if statement
	// NOTE: The % i causes interesting assembly.
	for(prime_t i = 7; i <= val / 5; i += 2){
		if(val % i == 0){ ret(false); }
	}
	
	ret(true);
	
}
#undef ret
