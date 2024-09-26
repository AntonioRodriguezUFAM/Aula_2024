// Images ppm Header
/*
PPM
Header
P3 // Format ASCII
250 250 // Image Size
255 // RGB Max



user >> PC - Image.ppm

User << PC
*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {

	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- PAVIC LAB 2024 ---------------------------" << std::endl;
	std::cout << "--------------------------     UFAC       ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2024    ---------------------------" << std::endl;
	std::cout << std::endl;
	std:: << "                             Prog. Antonio Souto Rodriguez                    " << std::endl;
	std::cout << cout << "------------------------ Programacao em PPM Image --------------------" << std::endl;
	std::cout"----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::ofstream image;
	image.open("Image_1.ppm");
	// Image PPM  Header
	image << "P3"<<std::endl;
	image << "2 3" << std::endl;
	image << "255" << std::endl;
	
	//loops while, for, size w , v
	// Image PPM Body
	/*RGB
	RGB
	RGB
	RGB
	RGB
	RGB*/
//	image << "" << std::endl;
	// RGB 
	image << "120 100 240" << std::endl; // Color X
	image << "255 0 0" << std::endl; // Red
	image << "0 255 0" << std::endl; // Green
	image << "0 0 255" << std::endl; //Blue
	image << "255 255 255" << std::endl; //White
	image << "0 0 0" << std::endl; // Black

	image.close();

	return 0;
}

