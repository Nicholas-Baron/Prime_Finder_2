#include "prime.hpp"
#include "settings.hpp"
#include "starter.hpp"

#include <atomic>
#include <future>
#include <iostream>		// cout
#include <queue>
#include <stdexcept>	// exception
#include <thread>

int main(int arg_count, const char** args){

	const Settings settings = parse_settings(arg_count, args);
	
	using namespace std;
	
	if(settings.debug_mode){
		cout << settings << endl;
	}
	
	queue<future<primality_t>> prime_queue;
	atomic<bool> running(true);
	
	thread starter(fill_prime_queue, 
					ref(prime_queue), ref(settings), ref(running));
	
	// The lower this value, the more time this thread spends in output
	constexpr unsigned short flush_amount = 25;
	
	long long largest_queue_size = 1;
	unsigned short count = 0;
	while(running || !prime_queue.empty()){
		
		// Wait until there is at least one thing in the queue
		// Repeatedly tell the scheduler that we are waiting
		while(prime_queue.empty()){ this_thread::yield(); }
		
		// get() for a future is non-const
		auto& next = prime_queue.front();
		
		try{
			const auto res = next.get();
			
			if(settings.only_primes && res.second){
				cout << res.first << '\n';
				count++;
			}else if(!settings.only_primes){
				cout << res	<< '\n';
				count++;
			}

			prime_queue.pop();
		}catch(const future_error& fut_err){
			cerr << "[Main] Future error: " << fut_err.what() << endl;
		}catch(const exception& e){
			cerr << "[Main] Error: " << e.what() << endl;
		}catch(...){
			cerr << "[Main] Unknown exception caught!" << endl;
		}
		
		if(settings.debug_mode && !settings.single_mode){
			cout << "Queue Size : " << prime_queue.size() << endl;
		}
		
		largest_queue_size = max<long long>(prime_queue.size(), 
											largest_queue_size);
		
		if(count >= flush_amount){
			count = 0;
			cout << flush;
		}
	}
	
	starter.join();

	if(!settings.single_mode && settings.large_queue){
		cout << "Largest queue size: " << largest_queue_size << endl;
	}
	
	return 0;
}
