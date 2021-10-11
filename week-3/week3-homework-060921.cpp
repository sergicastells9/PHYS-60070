/*
	Author: Sergi Castells
	Description:
		3.1.4 - Finds Fibonacci numbers up to 25 and their corresponding Fibonacci quotient.
		3.2.2 - Calculates pi to 4 digits.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <ctime>

int main() {
	
	/*
	// 3.1.4
	std::cout << std::setprecision(10) << std::setw(20);
	
	// Declare initial values in sequence
	int f0 = 0;
	int f1 = 1;
	int fib;
	float fib_q;
	
	// Calculate sequence entries
	for(int i = 2; i <= 25; i++) {
		fib = f0 + f1;
		fib_q = static_cast<float>(f1)/static_cast<float>(f0);
		
		f0 = f1;
		f1 = fib;
		
		std::cout << "Fibonacci number: " << fib << '\t' << "Fibonacci quotient: " << fib_q << std::endl;
	}
	*/
	
	
	// 3.2.2
	
	// Define radius and coordinates of box.
	int radius = 1;
	int x0 = -1;
	int x1 = 1;
	int y0 = -1;
	int y1 = 1;
	
	
	// Define Counter and number of events.
	int Counter = 0;
	int numEvents = 1000000000; // Gets to 4 digits after the decimal consistently
	
	srand(time(0));
	float randNumX, randNumY;
	
	
	// Loop through events and check if rand(X,Y) is in circle.
	for(int i = 0; i < numEvents; i++) {
		randNumX = static_cast<float>(rand()) / RAND_MAX;
		randNumY = static_cast<float>(rand()) / RAND_MAX;
		
		if(std::sqrt(pow(randNumX,2) + pow(randNumY,2)) <= radius) {
			Counter += 1;
		}
	}
	
	// Multiply pi by 4 to account for our symmetry simplification
	float pi = 4 * static_cast<float>(Counter) / static_cast<float>(numEvents);
	
	std::cout << pi << std::endl;
	
	
	return 0;
}