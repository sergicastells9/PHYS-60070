/*
	Author: Sergi Castells
	
	Description: Variables quad1a, quad1b compute the roots in the standard way. Variables quad2a, quad2b compute the roots
		in the reciprocal way. Arrays corresponding to test functions (test1, test2, ...) are inputted into the root solvers.
		Each set of roots are printed after running the two forms of solvers. The original test functions are commented out.
*/


#include <iostream>
#include <iomanip>
#include <cmath>

char tab = '\t';

// Save time by computing root values here
void setVars(long double a, long double b, long double c,
			long double &quad1a, long double &quad1b, long double &quad2a, long double &quad2b) {
	quad1a = (-b + std::sqrt(std::pow(b,2) - 4*a*c)) / (2*a);
	quad1b = (-b - std::sqrt(std::pow(b,2) - 4*a*c)) / (2*a);
	quad2a = (2*c) / (-b + std::sqrt(std::pow(b,2) - 4*a*c));
	quad2b = (2*c) / (-b - std::sqrt(std::pow(b,2) - 4*a*c));
}

int main() {
	std::cout << std::setprecision(6);
	
	
	// Note the use of a long double instead of float. That was intentional. See last comment.
	long double a, b, c;
	long double quad1a, quad1b, quad2a, quad2b;
	
	
	// Test the example functions below
	long double test1[3] = {0.001, 1000, 0.001};
	long double test2[3] = {1, -3, 2};
	long double test3[3] = {0.001, -1000, 0.001};
	
	
	// Test A
	a = test1[0];
	b = test1[1];
	c = test1[2];
	
	// Compute roots
	setVars(a,b,c,quad1a,quad1b,quad2a,quad2b);
	
	std::cout << quad1a << tab << quad1b << tab << quad2a << tab << quad2b << std::endl;
	
	
	// Test B
	a = test2[0];
	b = test2[1];
	c = test2[2];
	
	// Compute roots
	setVars(a,b,c,quad1a,quad1b,quad2a,quad2b);
	
	std::cout << quad1a << tab << quad1b << tab << quad2a << tab << quad2b << std::endl;
	
	
	// Test C
	a = test3[0];
	b = test3[1];
	c = test3[2];
	
	// Compute roots
	setVars(a,b,c,quad1a,quad1b,quad2a,quad2b);
	
	std::cout << quad1a << tab << quad1b << tab << quad2a << tab << quad2b << std::endl;
	
	
	
	// Test various other functions here. This now works in all cases when using a long double.
	long double test4[3] = {0.001, -1000, 0.001};
	a = test4[0];
	b = test4[1];
	c = test4[2];
	
	
	// Check sign of b. Check real/imaginary.
	if(!((std::pow(b,2) - 4*a*c) < 0)) {
		if(b < 0) {
			quad1a = (-b + std::sqrt(std::pow(b,2) - 4*a*c)) / (2*a);
			quad1b = (-b - std::sqrt(std::pow(b,2) - 4*a*c)) / (2*a);
			std::cout << quad1a << tab << quad1b << std::endl;
		}
		else if(b > 0) {
			quad2a = (2*c) / (-b + std::sqrt(std::pow(b,2) - 4*a*c));
			quad2b = (2*c) / (-b - std::sqrt(std::pow(b,2) - 4*a*c));
			std::cout << quad2a << tab << quad2b << std::endl;
		}
	}
	else {
		std::cout << "Imagainary roots..." << std::endl;
	}
	
	
	return 0;
}
