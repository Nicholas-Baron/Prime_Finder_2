#ifndef _STARTER_
#define _STARTER_

#include "prime.hpp"
#include "settings.hpp"

#include <queue>

void fill_prime_queue(std::queue<primality_t>& results, 
						const Settings& settings);

#endif
