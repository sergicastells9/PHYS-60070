#include <iostream>
#include <stdlib.h>
#include <cstring>



int main() {
	/*
	// Problem 1
	
	float vec1[3], vec2[3];
	float add[3], sub[3], dot[3], cross[3];
	
	std::cout << "Provide a vector of 3 numbers: ";
	std::cin >> vec1[0] >> vec1[1] >> vec1[2];
	
	std::cout << "Provide another vector of 3 numbers: ";
	std::cin >> vec2[0] >> vec2[1] >> vec2[2];
	
	// Addition
	for(int i = 0; i < sizeof(vec1)/sizeof(vec1[0]); i++) {
		add[i] = vec1[i] + vec2[i];
	}
	
	// Subtraction
	for(int i = 0; i < sizeof(vec1)/sizeof(vec1[0]); i++) {
		sub[i] = vec1[i] - vec2[i];
	}
	
	// Scalar Product
	for(int i = 0; i < sizeof(vec1)/sizeof(vec1[0]); i++) {
		dot[i] = vec1[i] * vec2[i];
	}
	
	// Cross Product
	for(int i = 0; i < sizeof(vec1)/sizeof(vec1[0]); i++) {
		cross[i] = vec1[(i+1)%3]*vec2[(i+2)%3] - vec1[(i+2)%3]*vec2[(i+1)%3];
	}
	
	std::cout << add[0] << '\t' << add[1] << '\t' << add[2] << std::endl;
	std::cout << sub[0] << '\t' << sub[1] << '\t' << sub[2] << std::endl;
	std::cout << dot[0] << '\t' << dot[1] << '\t' << dot[2] << std::endl;
	std::cout << cross[0] << '\t' << cross[1] << '\t' << cross[2] << std::endl;
	*/
	
	
	/*
	// Problem 2
	
	float mtx1[3][3], mtx2[3][3];
	float transpose1[3][3], transpose2[3][3], trace1, trace2;
	float add[3][3], sub[3][3], prod[3][3];
	
	std::cout << "Input first matrix: \n";
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cin >> mtx1[i][j];
		}
	}
	
	std::cout << "Input second matrix: \n";
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cin >> mtx2[i][j];
		}
	}
	
	
	// Transpose
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			transpose1[j][i] = mtx1[i][j];
			transpose2[j][i] = mtx1[i][j];
		}
	}
	
	std::cout << "---------" << std::endl;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << transpose1[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	std::cout << "---------" << std::endl;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << transpose2[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	std::cout << "---------" << std::endl;
	
		
	// Trace
	for(int i = 0; i < 3; i++) {
		trace1 += mtx1[i][i];
		trace2 += mtx1[i][i];
	}
	
	std::cout << trace1 << std::endl;
	std::cout << trace2 << std::endl;
	
	
	// Addition
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			add[i][j] = mtx1[i][j] + mtx2[i][j];
		}
	}
	
	std::cout << "---------" << std::endl;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << add[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	
	// Subtraction
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			sub[i][j] = mtx1[i][j] - mtx2[i][j];
		}
	}
	
	std::cout << "---------" << std::endl;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << sub[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	
	// Multiplication
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			prod[i][j] = mtx1[i][j] * mtx2[j][i];
		}
	}
	
	std::cout << "---------" << std::endl;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << prod[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	*/
	
	
	return 0;
}