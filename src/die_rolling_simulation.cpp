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
	unsigned seed = 420;	//TODO: Seed with actual system entropy
	std::mt19937 gen(seed);
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
	
	std::vector<int> freqCounter_async(7);
	auto async_start = steady_clock::now();
	// Launch each task immediately in a new thread
		//TODO
	// Combine results from async futures
 		//TODO
	auto async_end = steady_clock::now();
 	
	std::cout << "----NOT IMPLEMENTED YET----\n";
	std::cout << "\nMulti-threaded with std::launch::async:\n";
	print(freqCounter_async, get_time(async_start, async_end));
	
   	// -----------------------------------------------
	// 3. MULTI-THREADED with std::launch::deferred
	// -----------------------------------------------
	std::vector<int> freqCounter_deferred;
	auto deferred_start = steady_clock::now();
		//TODO
	auto deferred_end = steady_clock::now();
	
	std::cout << "----NOT IMPLEMENTED YET----\n";
	std::cout << "\nMulti-threaded with std::launch::deferred:\n";
	print(freqCounter_deferred, get_time(deferred_start, deferred_end));
}

// -----------------------------------------------
// Summary (Paste your actual output as comment) in the code:
// -----------------------------------------------
/*


*/
