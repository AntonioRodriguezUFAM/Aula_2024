// Images ppm Header & Body


#include <iostream>
#include <fstream>
#include <chrono>  // For performance timing
#include "codeTimer.h"
#include<sstream>

using namespace std;

int main() {

	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- PAVIC LAB 2024 ---------------------------" << std::endl;
	std::cout << "--------------------------     UFAC       ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2024    ---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "                             Prog. Antonio Souto Rodriguez                    " << std::endl;
	std::cout << "------------------------ Programacao em PPM Image --------------------" << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	// Header
	std::string type = "";
	std::string width = "";
	std::string height = "";
	std::string RGB = "";

	std::ifstream old_image; // Read file
	std::ofstream new_image; // Write file

	old_image.open("Image_5.ppm");
	new_image.open("New_Image_5.ppm");

{ // Start timer Header
		Timer timer;

	// copy from header old file(image) to memory
	old_image >> type;
	old_image >> width;
	old_image >> height;
	old_image >> RGB;
	// Copy from memory to  new file (image)

	new_image << type << std::endl;
	new_image << width << " " << height << std::endl;
	new_image << RGB << std::endl;

} // End Timer
	
	// copy from body old file(image) to memory
	std::string red = "";
	std::string green = "";
	std::string blue="";
	int intred = 0;
	int intgreen = 0;
	int intblue = 0;

	

	//Timer
	std::cout << "Time Start!!" << std::endl;
	auto start_single_thread = std::chrono::high_resolution_clock::now();

	// Read each pixel!!

{ // Start timer Body
		Timer timer;

	while (!old_image.eof()){

		old_image >> red;
		old_image >> green;
		old_image >> blue;
		/*
		Syntax:

		int stoi (string s, size_t* position = 0, int base = 10)
		Parameters: 

		The string which has to be transformed is the first parameter.
		Location of an integer used to track how many characters were read. In that scenario, it is not used if this parameter is a null pointer.
		The third and last parameter is base. The sequence’s format determines the base used if this is 0. It uses base 10(decimal) if no argument is passed
		
		*/
		// convert string to number!!
		//intred = std::stoi(red, nullptr);
		//intgreen = std::stoi(green, nullptr);
		intblue = std::stoi(blue, nullptr);


		// Blue filter !!
		intblue = intblue + 50;


		if (intblue > 249) {
			intblue = 255;
		}

		// Copy pixels
		new_image << red << " " << green << " " << intblue << std::endl;


	}
} // End Timer




	//auto stop_single_thread = std::chrono::high_resolution_clock::now();
	//std::cout << "Time End!!" << std::endl;

	//auto duration_single_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_single_thread - start_single_thread);
	//

	//// Display timing results
	//cout << "Single-threaded image processing time: " << duration_single_thread.count() << " millis" << endl;

	old_image.close();
	new_image.close();
	return 0;
}