/*
* @file: Aula-01-Multithreading.cpp
* @program: Impact-Lab_Computação_Heterogênea_2022
* @brief: Multithreading
* @group: IComp - UFAM
* @author: Antonio Souto Rodriguez
*/

// Ref: https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
// Github: https://github.com/sol-prog/threads

#include<iostream>
#include<thread>
//This function will be called from a thread

void call_from_thread() {
	std::cout << "Hello, World" << std::endl;
}

int main() {
	//Launch a thread
	std::thread t1(call_from_thread);
	
	//Join the thread with the main thread
	// For this particular code, the main function creates a thread 
	// and wait for the thread to finish at t1.join()
	t1.join();
	// If you forget to wait for a thread to finish his work, 
	//it is possible that main will finish first and the program
	//will exit killing the previously created thread regardless if “call_from_thread” has finished or not.
	
	return 0;

}