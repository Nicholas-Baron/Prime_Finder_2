#ifndef _PRIME_
#define _PRIME_

#include <ostream>	// ostream
#include <utility>	// pair

using prime_t = unsigned long long;

using primality_t = std::pair<prime_t, bool>;

namespace std{
	inline std::string to_string(const primality_t& rhs){
		return std::to_string(rhs.first) + " : " 
				+ (rhs.second ? "Prime" : "Not Prime");
	}
}

inline std::ostream& operator<<(std::ostream& lhs, const primality_t& rhs){
	lhs << std::to_string(rhs);
	return lhs;
}

constexpr primality_t is_prime(const prime_t val) noexcept {
	
	// This macro simplifies the typing for a return statement in this function.
#define ret(x) return std::make_pair(val, x)

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
	for(prime_t i = 7; i <= val / 7; i += 2){
		if(val % i == 0){ ret(false); }
	}
	
	ret(true);
	
#undef ret

}

#endif
