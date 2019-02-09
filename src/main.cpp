#include "prime.hpp"
#include "settings.hpp"
#include "starter.hpp"

#include <atomic>
#include <chrono>
#include <future>
#include <iostream>		// cout
#include <queue>
#include <stdexcept>	// exception
#include <thread>

int main(int arg_count, const char** args){

	const auto settings = parse_settings(arg_count, args);
	
	using namespace std;
	
	if(settings.debug_mode){
		cout << settings << endl;
	}
	
	queue<future<primality_t>> prime_queue;
	atomic<bool> running(true);
	
	thread starter(fill_prime_queue, 
					ref(prime_queue), ref(settings), ref(running));
	
	long long largest_queue_size = 1;
	
	while(running || !prime_queue.empty()){
		
		// Wait until there is at least one thing in the queue
		while(prime_queue.empty()){
			//this_thread::yield();
		}
		
		auto& next = prime_queue.front();
		
		try{
			const auto res = next.get();
			
			cout << res << endl;
				
			prime_queue.pop();
		}catch(const future_error& fut_err){
			cerr << "[Main] Future error: " << fut_err.what() << endl;
		}catch(const exception& e){
			cerr << "[Main] Error: " << e.what() << endl;
		}
		
		if(settings.debug_mode){
			cout << prime_queue.size() << endl;
		}
		
		largest_queue_size = std::max<long long>(prime_queue.size(), largest_queue_size);
	}
	
	starter.join();

	if(settings.debug_mode && !settings.single_mode){
		cout << "Largest queue size: " << largest_queue_size << endl;
	}
}
