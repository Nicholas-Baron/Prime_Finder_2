#ifndef _SETTINGS_
#define _SETTINGS_

#include "prime.hpp"

#include <iostream>	// cin, cout

struct Settings{
	prime_t range_end;
	bool debug_mode = false;
};

namespace std{
	inline std::string to_string(const Settings& rhs){
		return "Settings: " + std::to_string(rhs.range_end);
	}
}

inline std::ostream& operator<<(std::ostream& lhs, const Settings& rhs){
	lhs << std::to_string(rhs);
	return lhs;
}

Settings parse_settings(int arg_count, const char** args);

#endif
