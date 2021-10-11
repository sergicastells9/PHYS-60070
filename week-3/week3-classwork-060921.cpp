#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>


float Normal(float mean, float stddev) {
	float R1, R2;
	R1 = (float)rand()/(float)(RAND_MAX);
	R2 = (float)rand()/(float)(RAND_MAX);
	
	return mean + stddev*cos(2*3.14*R1)*sqrt((-2*log(R2)));
}


int main() {
	/*
	for(int iii = 0, jjj = 9; iii < 10; iii++, jjj--) {
		std::cout << iii << " " << jjj << std::endl;
	}
	
	std::cout << "\n\n\n" << std::endl;
	
	for(int iii = 0; iii < 10; iii++) {
		for(int jjj = 9; jjj >= 0; jjj--) {
			std::cout << iii << " " << jjj << std::endl;
		}
	}
	*/
	
	
	// Classwork 3.1
	
	// 3.1.1
	/*
	std::cout << "Input an operator: ";
	char op = getchar();
	
	float a,b;
	std::cout << "Input two values: ";
	std::cin >> a >> b;
	
	switch(op) {
		case '+':
			std::cout << a+b << std::endl;
			break;
		case '-':
			std::cout << a-b << std::endl;
			break;
		case '*':
			std::cout << a*b << std::endl;
			break;
		case '/':
			std::cout << a/b << std::endl;
			break;
		default:
			std::cout << "Error" << std::endl;
			exit(1);
	}
	*/
	
	// 3.1.2
	/*
	long double sum; // Using long double to avoid overflow
	int a,b;
	
	std::cout << "Input two values: ";
	std::cin >> a >> b;
	
	for(int i = a; i <= b; i++) {
		sum += std::pow(i,2);
	}
	
	std::cout << sum << std::endl;
	*/
	
	// 3.1.3
	/*
	double sin_sum, e_sum;
	
	for(double i = 1.1; i < 10; i += 0.1) {
		sin_sum += std::sin(i);
		e_sum += std::exp(i);
	}
	
	std::cout << "sin(x) sum: " << sin_sum << std::endl;
	std::cout << "exp(x) sum: " << e_sum << std::endl;
	*/
	
	// 3.2.1
	srand(time(0));
	
	float hist[100] = {0}; // automatically initialize every element to 0
	float mean = 0;
	float stddev = 2;
	
	for(int i = 0; i < 10000; i++) {
		float val = Normal(mean, stddev);
		
		for(int j = -sizeof(hist)/2; j < sizeof(hist)/2; j++) {
			if(val >= j * 0.2 && val < (j+1) * 0.2) {
				hist[j+sizeof(hist)/2] += 1;
			}
		}
	}
	
	
	for(int i = 0; i < sizeof(hist); i++) {
		std::cout << hist[i] << std::endl;
	}
	
	
	return 0;
}
