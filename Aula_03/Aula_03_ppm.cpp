// Images ppm Header & Body


#include <iostream>
#include <fstream>
#include <chrono>  // For performance timing

using namespace std;

int main() {

	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- PAVIC LAB 2024 ---------------------------" << std::endl;
	std::cout << "--------------------------     UFAC       ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2024    ---------------------------" << std::endl;
	std::cout << std::endl;
	std:: cout << "                             Prog. Antonio Souto Rodriguez                    " << std::endl;
	std::cout << "------------------------ Programacao em PPM Image --------------------" << std::endl;
	std::cout<<"----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::ofstream image;
	image.open("Image_5.ppm");
	// Image PPM  Header
	image << "P3" << std::endl;
	image << "1000 1000" << std::endl;
	image << "255" << std::endl;

	//Timer
	std::cout <<"Time Start!!"<< std::endl;
	auto start_single_thread = std::chrono::high_resolution_clock::now();
	// Image PPM Body
	for (int y = 0;y < 1000;y++) {
		for (int x = 0;x < 1000;x++) {
			//Pixel RGB (0->> 255) 8 bits
			
			image << y << " " << 255 << " " << x << std::endl;
			
		}
	 }
	auto stop_single_thread = std::chrono::high_resolution_clock::now();
	std::cout << "Time End!!" << std::endl;

	auto duration_single_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_single_thread - start_single_thread);
	auto duration_single_thread = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_single_thread - start_single_thread);


	// Display timing results
	cout << "Single-threaded image processing time: " << duration_single_thread.count() << " millis" << endl;

	
	return 0;image.close();

}
