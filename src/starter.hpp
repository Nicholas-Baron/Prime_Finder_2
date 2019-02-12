#ifndef _STARTER_
#define _STARTER_

#include "prime.hpp"
#include "settings.hpp"

#include <atomic>
#include <future>
#include <queue>

// This function runs in the second thread 
// and fills the queue with threads that process potential prime numbers
void fill_prime_queue(std::queue<std::future<primality_t>>& results, 
						const Settings& settings, std::atomic<bool>& running);

#endif
