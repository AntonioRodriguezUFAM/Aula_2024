/*
* @file: Aula-03-Multithreading.cpp
* @program: Impact-Lab_Computação_Heterogênea_2022
* @brief: Multithreading
* @group: IComp - UFAM
* @author: Antonio Souto Rodriguez
*/


#include <iostream>
#include <thread>

// Adding Threads ID numbers
/*
You can see in the above result that there is no particular order in which once created a thread will run.
*/

//This function will be called from a thread
void call_from_thread(int tid) {
	std::cout << "Launched by thread = " << tid << std::endl;
}
static const int num_threads = 10;

/*
Remember that the main function is also a thread, 
usually named the main thread, so the above code actually runs 11 threads.
*/

int main() {
	std::thread t[num_threads];

	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread(call_from_thread, i);
	}
	std::cout << "\nLaunched from the main\n";

	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}

	return 0;

}