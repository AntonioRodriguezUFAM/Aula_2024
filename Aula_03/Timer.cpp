
#include <iostream>
#include <chrono>  // For performance timing

using namespace std;

int main() {
	auto start_single_thread = std::chrono::high_resolution_clock::now();
	
	for (int i = 0;i < 1000000;i++) {} //1000000

	auto stop_single_thread = std::chrono::high_resolution_clock::now();
	auto duration_single_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_single_thread - start_single_thread);
	// Display timing results
	cout << "Single-threaded image processing time: " << duration_single_thread.count() << " ms" << endl;




	auto start_multi_thread = std::chrono::high_resolution_clock::now();

		for (int i = 0;i < 1000;i++) {} //1000

	auto stop_multi_thread = std::chrono::high_resolution_clock::now();
	auto duration_multi_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_multi_thread - start_multi_thread);



	cout << "Multithreaded image processing time: " << duration_multi_thread.count() << " ms" << endl;

	return 0;


}