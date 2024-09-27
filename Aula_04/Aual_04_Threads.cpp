// Aula 4 - Threads


#include<iostream>
#include <thread> // threads 


void Task_1() {
	std::cout << "Hello  From Thread A !!" << std::endl;
}

void Task_2() {
	std::cout << "Hello  From Thread B !!" << std::endl;
}

void Task_3() {
	std::cout << "Hello  From Thread C!!" << std::endl;
}


int main() {

	// Main task
	std::cout << "Hello  From Main !!" << std::endl;

	std::thread Child_A(Task_1); // Create threads !!
	std::thread Child_B(Task_2);
	std::thread Child_C(Task_3);

	
	// Return Threads
	Child_A.join();
	Child_B.join();
	Child_C.join();


	return 0;
}