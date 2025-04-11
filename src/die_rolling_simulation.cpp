#include <chrono>
#include <random>
#include <iostream>
#include <future>
using namespace std::chrono;

// Function to simulate rolling a six-sided die 'times' times.
// Returns a vector<int> where index i represents the frequency of die face i.
// Note: frequency[0] will be unused for convenience (so face 1 maps to index 1).
std::vector<int> roll_random_die(int times) {
	// Step 1: Set up a random number generator (seed, random enginer, uniform distribution etc)
	std::random_device seed_rd;	//Not ideally random but good enough for simulation purposes
	std::mt19937 gen(seed_rd());
	std::uniform_int_distribution<int> dist(1, 6);	//Configure range of RNG output
	// Step 2: Initialize frequency vector of size 7 (index 0 unused)
	std::vector<int> freq(7);	 
	// Step 3: Roll the die 'times' times
	for (int i = 0; i < times; i++) freq[dist(gen)]++;
	// Step 4: Return the frequency vector
	return freq;
}

// Function to calculate elapsed time in seconds between two-time points
// Parameters:
//   - start: the starting time point
//   - end: the ending time point
// Returns:
//   - the duration in seconds as a double
double get_time(steady_clock::time_point start, steady_clock::time_point end) {
	// Step 1: Calculate the duration between 'end' and 'start' in milliseconds
	// milliseconds gives higher precision since directly computing seconds will truncate fractional
	duration<double, std::milli> time_diff = end - start;
	// Step 2: Convert the duration to seconds (milliseconds to seconds)
	double d_time_diff = duration<double>(time_diff).count();
	// Step 3: Return the duration in seconds
	return d_time_diff;
}

// Function to print the frequency of die rolls and the time taken to compute them
 // Parameters:
 //   - freq: a vector containing the frequency of each die face (index 1 to 6)
 //   - time: the time duration in seconds (as a double) it took to perform the simulation

void print(std::vector<int> freq, double time) {
	// Loop through the frequency vector starting from index 1 (index 0 is unused)
	for (int i{1}; i < freq.size(); i++)
		std::cout << freq[i] << " ";  // Print each frequency separated by a space
	// Print the total time taken after the frequencies
	std::cout << ": " << time << " seconds \n";
}

int main() {
	// -----------------------------------------------
	// 1. SINGLE-THREADED VERSION
	// -----------------------------------------------
 
	auto start = std::chrono::steady_clock::now();
	auto freq = roll_random_die(60'000'000);
	auto end = std::chrono::steady_clock::now();

	std::cout << "Single-threaded version:\n";
	print(freq, get_time(start, end));

   	// -----------------------------------------------
   	// 2. MULTI-THREADED with std::launch::async
   	// -----------------------------------------------
	auto nCores = std::thread::hardware_concurrency(); // Get number of CPU cores
	int rollsPerThread = 60'000'000 / (int)nCores;     // Divide workload per thread
	
	auto async_start = steady_clock::now();
	
	// Launch each task immediately in a new thread
	std::vector<std::future<std::vector<int>>> async_futures;
	for (int i = 0; i < nCores; i++) {
		auto future_vector = std::async(
			std::launch::async,
			roll_random_die,
			rollsPerThread
		);	//Run a single roll_random_die call in each thread, and run one thread per core on the system
		async_futures.emplace_back(std::move(future_vector));
	}

	// Combine results from async futures
	std::vector<int> async_freq(7);
	for (auto &future : async_futures) {
		std::vector<int> calculated_vector = future.get();
		for (int i = 1; i <= 6; i++) async_freq[i] += calculated_vector[i];
	}
	auto async_end = steady_clock::now();
 	
	std::cout << "\nMulti-threaded with std::launch::async:\n";
	print(async_freq, get_time(async_start, async_end));
	
   	// -----------------------------------------------
	// 3. MULTI-THREADED with std::launch::deferred
	// -----------------------------------------------
	auto deferred_start = steady_clock::now();
	
	// Launch each task in a new thread to be deferred
	std::vector<std::future<std::vector<int>>> deferred_futures;
	for (int i = 0; i < nCores; i++) {
		auto future_vector = std::async(
			std::launch::deferred,
			roll_random_die,
			rollsPerThread
		);	//Run a single roll_random_die call in each thread, and run one thread per core on the system
		deferred_futures.emplace_back(std::move(future_vector));
	}

	// Combine results from async futures
	std::vector<int> deferred_freq(7);
	for (auto &future : deferred_futures) {
		std::vector<int> calculated_vector = future.get();
		for (int i = 1; i <= 6; i++) deferred_freq[i] += calculated_vector[i];
	}

	auto deferred_end = steady_clock::now();
	
	std::cout << "\nMulti-threaded with std::launch::deferred:\n";
	print(deferred_freq, get_time(deferred_start, deferred_end));
}

// -----------------------------------------------
// Summary (Paste your actual output as comment) in the code:
// -----------------------------------------------
/*
	Single-threaded version:
	10001625 9996433 10006020 10000699 9995686 9999537 : 0.901414 seconds

	Multi-threaded with std::launch::async:
	9999455 9995644 10004544 9995346 10001198 10003813 : 0.125689 seconds

	Multi-threaded with std::launch::deferred:
	10006613 9997685 9996484 10001954 9999158 9998106 : 0.89578 seconds
*/
