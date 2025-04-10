// Function to simulate rolling a six-sided die 'times' times.
// Returns a vector<int> where index i represents the frequency of die face i.
// Note: frequency[0] will be unused for convenience (so face 1 maps to index 1).
std::vector<int> roll_random_die(int times) {
	 // Step 1: Set up a random number generator (seed, random enginer, uniform distribution etc)
	 // Step 2: Initialize frequency vector of size 7 (index 0 unused)
	 // Step 3: Roll the die 'times' times
	 // Step 4: Return the frequency vector
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
	// Step 2: Convert the duration to seconds (milliseconds to seconds)
	// Step 3: Return the duration in seconds
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
// Sample output:
// Each number corresponds to the frequency of die faces 1 to 6
// Time is shown after the colon
/*
 10003111 10005348 10000549 10001391 9994485 9995116 : 2.034 seconds
 9999281 10000895 9999485 9999850 9998419 10002070 : 0.171 seconds
*/

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

	// Launch each task immediately in a new thread

	// Combine results from async futures
 
 	std::cout << "\nMulti-threaded with std::launch::async:\n";
	print(freqCounter_async, get_time(async_start, async_end));
	
   	// -----------------------------------------------
	// 3. MULTI-THREADED with std::launch::deferred
	// -----------------------------------------------

	std::cout << "\nMulti-threaded with std::launch::deferred:\n";
	print(freqCounter_deferred, get_time(deferred_start, deferred_end));
}

// -----------------------------------------------
// Summary (Paste your actual output as comment) in the code:
// -----------------------------------------------
/*


*/
