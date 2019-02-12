#ifndef _SETTINGS_
#define _SETTINGS_

#include "prime.hpp"

#include <iostream>	// cin, cout
#include <sstream>	// stringstream

// Stores the program's settings for the lifetime of the program.
struct Settings{
	prime_t range_end = 0;
	
	// Print on every percent towards completion
	int prog_percent = 1;
	
	// Explicit false for clarity
	bool debug_mode = false, 
	single_mode = false, 
	large_queue = false,
	only_primes = false,
	progress_print = false,
	time_loop = false;
};

namespace std{

	// The to_string override for the Settings struct
	// Written to use a style more native to C++ 
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

// The cout << override for the Settings struct
// Written to use a style more native to C++ 
inline std::ostream& operator<<(std::ostream& lhs, const Settings& rhs){
	lhs << std::to_string(rhs);
	return lhs;
}

// The function that parses the command line input, 
// creates the Settings struct for the particular run.
Settings parse_settings(int arg_count, const char** args);

#endif
