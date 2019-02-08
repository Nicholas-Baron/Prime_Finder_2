#include "settings.hpp"

#include <iostream>	//cout

int main(int arg_count, const char** args){

	const auto settings = parse_settings(arg_count, args);
	std::cout << settings << std::endl;
}
