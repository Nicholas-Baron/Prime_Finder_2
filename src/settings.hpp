#ifndef _SETTINGS_
#define _SETTINGS_

#include <iostream>	// cin, cout

#include <cassert>	// assert
#include <cctype>	// isdigit
#include <cstdlib>	// atoi, abs

struct Settings{
	unsigned long range_end;
};

std::ostream& operator<<(std::ostream& lhs, const Settings& rhs){
	lhs << "Settings: " << rhs.range_end;
	return lhs;
}

Settings parse_settings(int arg_count, const char** args){

	using std::cout; 
	long range_end = 0;

	for(int i = 0; i < arg_count; i++){
		cout << i << ':' << args[i] << std::endl;
		if(isdigit(args[i][0])){
			range_end = atoi(args[i]);
		}
	}
	
	if(range_end <= 3){
		using std::cin;
		
		cout << "Enter the largest number that will be check: ";		
		cin >> range_end;
	
		while(cin.fail() || range_end <= 3){
			cout << "Please enter a positive integer greater than 3: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> range_end;
		}
	}
	
	assert(range_end > 0);
	
	return Settings{static_cast<unsigned long>(range_end)};
}

#endif
