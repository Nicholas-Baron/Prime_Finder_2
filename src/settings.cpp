#include "settings.hpp"

#include "assert.hpp"
#include <string>	// string::npos

#include <cctype>	// isdigit
#include <cstdlib>	// atoi

long long user_input(){
	long long toRet = 0;
	
	using std::cout; using std::cin; using std::flush;
		
	cout << "Enter the largest number that will be checked: " << flush;	
	cin.ignore();
	cin >> toRet;

	while(!cin || toRet <= 3){
		cout << "Please enter a positive integer greater than 3: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> toRet;
	}
	
	return toRet;
}

Settings parse_settings(int arg_count, const char** args){

	using std::cout; using std::endl; using std::string;
	
	// This variable is used to prevent overflows
	long long range_end = 0;
	Settings toRet;

	//Read all user inputed arguments
	for(int i = 0; i < arg_count; i++){
	
		const auto* option = args[i];
		
		// If the first character of an argument is a number, 
		// use it as the end of the scan range 
		if(isdigit(option[0]) != 0){
			range_end = atoi(option);
		// If the first character is a dash, it is an option.
		}else if(option[0] == '-'){
			
			string opt_line(option);
			if(opt_line == "-v" || opt_line == "-d"){ toRet.debug_mode = true; }
			else if(opt_line == "-lq"){ toRet.large_queue = true; }
			else if(opt_line.find("-prog") == 0){ 
				toRet.progress_print = true; 
				
				auto number_pos = opt_line.find_first_of("0123456789");
				if(number_pos != string::npos){
					toRet.prog_percent = stoi(opt_line.substr(number_pos));
				}
			} else if(opt_line == "-p"){ 
				toRet.only_primes = true; 
			} else if(opt_line == "-t") {
				toRet.time_loop = true;
			} else { 
				cout << "Option " << opt_line << " is not supported!" << endl;
			}
		}
	}
	
	if(toRet.debug_mode){
		
		for(int i = 0; i < arg_count; i++){
			cout << i << " : " << args[i] << endl;
		}
	
		cout << range_end << endl;
		
		if(toRet.progress_print){
			cout << "Print at every " << toRet.prog_percent << '%' << endl;
		}
	}
	
	if(toRet.large_queue && toRet.single_mode){
		cout << "Will not print largest size as it will be 1." << endl;
	}
	
	// Any range smaller than 4 is not worth the program checking
	if(range_end <= 3){
		range_end = user_input();
	}
	
	// Be sure that we do not walk backwards
	assert(range_end > 0);
	toRet.range_end = static_cast<prime_t>(range_end);
	
	return toRet;
}
