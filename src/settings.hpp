#ifndef _SETTINGS_
#define _SETTINGS_

#include "prime.hpp"

#include <iostream>	// cin, cout
#include <sstream>	// stringstream

struct Settings{
	prime_t range_end = 0;
	
	int prog_percent = 1;
	
	bool debug_mode = false, 
	single_mode = false, 
	large_queue = false,
	only_primes = false,
	progress_print = false,
	time_loop = false;
};

namespace std{

	inline std::string to_string(bool val){
		return (val?"true":"false");
	}

	inline std::string to_string(const Settings& rhs){
		std::stringstream stream;
		stream << "Settings( " << rhs.range_end;
		if(rhs.debug_mode){
			stream << " | Debug";
		}
		if(rhs.single_mode){
			stream << " | Single";
		}
		if(rhs.large_queue){
			stream << " | Show Max Queue Size";
		}
		if(rhs.only_primes){
			stream << " | Print Only Primes";
		}
		if(rhs.progress_print){
			stream << " | Print Progress @ " << rhs.prog_percent << '%';
		}
		if(rhs.time_loop){
			stream << " | Time Main Loop";
		}
		stream << " )";
		return stream.str();
	}
}

inline std::ostream& operator<<(std::ostream& lhs, const Settings& rhs){
	lhs << std::to_string(rhs);
	return lhs;
}

Settings parse_settings(int arg_count, const char** args);

#endif
