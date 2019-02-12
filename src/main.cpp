#include "prime.hpp"
#include "settings.hpp"
#include "starter.hpp"

#include <atomic>
#include <chrono>		// high_resolution_clock::now
#include <future>
#include <iostream>		// cout
#include <queue>
#include <stdexcept>	// exception
#include <thread>

/*
	Design: 
		Main thread parses the settings and starts the second (starter) thread.
		Starter thread loads a queue with other threads.
		The threads in the queue each process a number 
			and return both that number and whether it is prime.
		The main thread unloads the queue,
			and handles the result of each thread in the queue.
		Once the queue has been emptied, the starter thread is joined back.
*/

int main(int arg_count, const char** args){

	// The settings to be used for this particular run
	const Settings settings = parse_settings(arg_count, args);
	
	using namespace std;
	
	if(settings.debug_mode){
		cout << settings << endl;
	}
	
	// The queue that holds the threads to process each number
	queue<future<primality_t>> prime_queue;
	// A flag that is set to false when the starter thread finishes
	atomic<bool> running(true);
	
	// The lower this value, the more time this thread spends in output
	constexpr unsigned short flush_amount = 25;
	// Stores the largest size that the queue was for output
	long long largest_queue_size = 1;
	// Count how many elements have added since the last flush
	unsigned short flush_count = 0;
	prime_t total_count = 0;
	
	const auto start_loop = chrono::high_resolution_clock::now();
	
	// The second thread that loads the queue
	thread starter(fill_prime_queue, 
					ref(prime_queue), ref(settings), ref(running));

	// The queue is empty early on 
	// and the second thread could be finished 
	// while there are still items to print
	while(running || !prime_queue.empty()){
		
		// Wait until there is at least one thing in the queue
		// Repeatedly tell the scheduler that we are waiting
		while(prime_queue.empty()){ this_thread::yield(); }
		
		// get() for a future is non-const
		auto& next = prime_queue.front();
		
		// Try-catch is used in case of an error 
		// occuring in getting the result from the queue
		try{
			const auto res = next.get();
			total_count++;
			
			// Use newlines instead of endl in code that is not in a catch block
			// Reason: the flush calls here significantly slow down the program,
			// as the outputs in the loop occur with high frequency
			if(settings.only_primes && res.second){
				cout << res.first << '\n';
				flush_count++;
			}else if(!settings.only_primes){
				cout << res	<< '\n';
				flush_count++;
			}

			prime_queue.pop();
		// future_error is separate as this is most likely to occur error
		}catch(const future_error& fut_err){
			cerr << "[Main] Future error: " << fut_err.what() << endl;
		}catch(const exception& e){
			cerr << "[Main] Error: " << e.what() << endl;
		}catch(...){
			cerr << "[Main] Unknown exception caught!" << endl;
		}
		
		// Prints the percentage towards completion
		if(settings.progress_print){
			// Multiply by 200 b/c we only count the odd numbers
			auto percent = total_count * 200 / settings.range_end;
			if(percent % settings.prog_percent == 0 && percent < 100){
				cout << "Progress: " << percent << '%' << '\n';
			}
		}
		
		// Print the queue size if the setting is on 
		// and there could be multiple things in the queue
		if(settings.debug_mode && !settings.single_mode){
			cout << "Queue Size : " << prime_queue.size() << '\n';
		}
		
		largest_queue_size = max<long long>(prime_queue.size(), 
											largest_queue_size);
		
		if(flush_count >= flush_amount){
			flush_count = 0;
			cout << flush;
		}
	}
	
	starter.join();

	const auto end_loop = chrono::high_resolution_clock::now();
	
	if(!settings.single_mode && settings.large_queue){
		cout << "Largest queue size: " << largest_queue_size << endl;
	}
	
	if(settings.time_loop){
		// Print out the millisecond timing 
		using milliF = chrono::duration<float, std::milli>;
		cout << "Time taken: " 
		<< chrono::duration_cast<milliF>(end_loop - start_loop).count() << " ms"
		<< endl;
	}
	
	return 0;
}
