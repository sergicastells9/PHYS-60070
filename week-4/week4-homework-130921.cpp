/*
	Author: Sergi Castells
	Description: 4.1.3 - Rotates vectors about x, y, and z axes in that order.
	4.2.2 - Takes number input from user and returns number of digits excluding certain criteria.
*/


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>


int main() {
	/*
	// 4.1.3
	float vec[3];
	float rot_vec[3] = {0};
	float angles[3];
	char axes[3] = {'x', 'y', 'z'};
	
	std::cout << "Provide vector coordinates: ";
	std::cin >> vec[0] >> vec[1] >> vec[2];
	
	// Gets angles for each axis of rotation
	for(int i = 0; i < 3; i++) {
		std::cout << "Provide an angle (can be 0) of rotation for " << axes[i] << " axis: ";
		std::cin >> angles[i];
	}
	
	
	// I know this is dumb but I didn't want to write out angles[i] each time
	float x = angles[0];
	float y = angles[1];
	float z = angles[2];
	
	float rot_matrix[3][3] = {{std::cos(x)*std::cos(y), std::cos(x)*std::sin(y)*std::sin(z) - std::sin(x)*std::cos(z), std::cos(x)*std::sin(y)*std::cos(z) + std::sin(x)*std::sin(z)},
							{std::sin(x)*std::cos(y), std::sin(x)*std::sin(y)*std::sin(z) + std::cos(x)*std::cos(z), std::sin(x)*std::sin(y)*std::cos(z) - std::cos(x)*std::sin(z)},
							{-std::sin(y), std::cos(y)*std::sin(z), std::cos(y)*std::cos(z)}};
	
	// Do matrix multiplication
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			rot_vec[i] += rot_matrix[i][j] * vec[j];
		}
	}
	
	std::cout << "Your rotated vector is:" << std::endl;
	std::cout << rot_vec[0] << " " << rot_vec[1] << " " << rot_vec[2] << std::endl;
	*/
	
	
	// 4.2.2
	char cStr[20];
	int counter = 0;
	bool bad_char = false;
	
	std::cout << "Provide a number: ";
	std::cin >> cStr;
	
	
	for(int i = 0; i < strlen(cStr); i++) {
		// Check if not decimal point, if not number, if not e/E, if number
		if(cStr[i] != '.' && cStr[i] != 'e' && cStr[i] != 'E') {
			if(isdigit(cStr[i])) {
				counter++;
			}
		}
		
		// Check if not everything
		if(cStr[i] != '.' && cStr[i] != 'e' && cStr[i] != 'E' && !isdigit(cStr[i])) {
			std::cout << "Not a number, decimal point, or 'e'/'E'." << std::endl;
			bad_char = true;
			break;
		}
	}
	
	// Confirm no bad character
	if(!bad_char) {
		std::cout << counter << std::endl;
	}
	
	
	return 0;
}