#ifndef _PRIME_
#define _PRIME_

#include <iostream>
#include <utility>

using prime_t = unsigned long long;

using primality_t = std::pair<prime_t, bool>;

primality_t is_prime(const prime_t val);

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

#endif
