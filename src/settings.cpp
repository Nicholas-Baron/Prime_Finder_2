#include "settings.hpp"

#include <cassert>	// assert
#include <cctype>	// isdigit
#include <cstdlib>	// atoi, abs
#include <cstring>	// strcmp

Settings parse_settings(int arg_count, const char** args){

	using std::cout; using std::endl;
	long long range_end = 0;
	bool debug = false;

	//Read all user inputed arguments
	for(int i = 0; i < arg_count; i++){
	
		const auto* option = args[i];
		
		// If the first character of an argument is a number, 
		// use it as the end of the scan range 
		if(isdigit(option[0])){
			range_end = atoi(option);
		}else if(option[0] == '-'){
			if(strcmp(option, "-v") == 0 || strcmp(option, "-d") == 0){
				debug = true;
			} else {
				cout << "Option " << option << " is not supported!" << endl;
			}	
		}
	}
	
	if(debug){
		
		for(int i = 0; i < arg_count; i++){
			cout << std::to_string(i) << ':' << args[i] << endl;
		}
	
		cout << range_end << endl;
	}
	
	// Any range smaller than 4 is not worth the program checking
	if(range_end <= 3){
		using std::cin; using std::flush;
		
		cout << "Enter the largest number that will be checked: " << flush;	
		cin.ignore();
		cin >> range_end;
	
		while(!cin || range_end <= 3){
			cout << "Please enter a positive integer greater than 3: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> range_end;
		}
	}
	
	// Be sure that we do not walk backwards
	assert(range_end > 0);
	
	return Settings{static_cast<prime_t>(range_end), debug};
}
