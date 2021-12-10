/*
	Author: Sergi Castells
	Problem 10
*/

#include <iostream>
#include <string>
#include <fstream>


int main() {
	std::ifstream fIn;
	fIn.open("file_test.dat", std::ofstream::in);
	
	int inp[2];
	std::cout << "What product do you want (i <= 9, j <= 19?" << std::endl;
	std::cin >> inp[0] >> inp[1];
	
	// Skip lines i-1 times
	for(int i = 1; i < inp[1]; i++) {
		std::string tmp;
		getline(fIn, tmp);
	}
	
	// Move sideways 4*(i-1) times
	fIn.seekg(4*(inp[0]-1), std::ios::cur);
	
	// Read and print out result
	char out[3];
	fIn.read(out, 3);
	std::cout << "Product of " << inp[0] << " and " << inp[1] << " is: " << out[0] << out[1] << out[2] << std::endl;
	
	
	return 0;
}