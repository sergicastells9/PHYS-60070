#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string>

int main() {
	// Problem 7
	/*
	int inp[2];
	int out[2];
	
	std::cout << "Provide two integers: ";
	std::cin >> inp[0] >> inp[1];
	
	std::ofstream fOut("file_test.dat");
	fOut << inp[0] << '\t' << inp[1] << std::endl;
	fOut.close();
	
	std::ifstream fIn("file_test.dat");
	
	if(!fIn) {
		std::cout << "file_test.dat not opened!" << std::endl;
		exit(1);
	}
	
	fIn >> out[0] >> out[1];
	fIn.close();
	
	std::cout << out[0] << '\t' << out[1] << std::endl;
	*/
	
	// Problem 8
	/*
	std::ofstream fOut("file_test.dat");
	
	for(int i = 1; i < 10; i++) {
		for(int j = 1; j < 10; j++) {
			int prod = i*j;
			fOut << std::setfill('0') << std::setw(3) << prod << ' ';
		}
		
		fOut << std::endl;
	}
	
	fOut.close();
	*/
	
	// Problem 9
	/*
	std::ofstream fOut;
	fOut.open("file_test.dat", std::ofstream::app);
	
	for(int i = 10; i < 20; i++) {
		for(int j = 1; j < 10; j++) {
			int prod = i*j;
			fOut << std::setfill('0') << std::setw(3) << prod << ' ';
		}
		
		fOut << std::endl;
	}
	
	fOut.close();
	*/
	
	// Problem 10
	std::ifstream fIn;
	fIn.open("file_test.dat", std::ofstream::in);
	
	int inp[2];
	std::cout << "What product do you want (i,j)?: ";
	std::cin >> inp[0] >> inp[1];
	
	for(int i = 1; i < inp[1]; i++) {
		std::string tmp;
		getline(fIn, tmp);
	}
	
	// Need to account for spaces
	fIn.seekg(3*(inp[0]-1), std::ios::cur);
	
	char out[3];
	fIn.read(out, 3);
	std::cout << "Product of " << inp[0] << " and " << inp[1] << " is: " << out[0] << out[1] << out[2] << std::endl;
	
	
	
	
	
	return 0;
}