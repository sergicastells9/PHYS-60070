#include <iostream>
#include <cmath>

int main() {
	/*
	int pointAx, pointAy;
	int pointBx, pointBy;
	
	std::cout << "\nInput the first point (x,y): ";
	std::cin >> pointAx >> pointAy;
	
	std::cout << "\nInput the second point (x,y): ";
	std::cin >> pointBx >> pointBy;
	
	float distance = std::sqrt(std::pow((pointAx - pointBx), 2.0) + std::pow((pointAy - pointBy), 2.0));
	
	std::cout << "The distance between the two points is: " << distance << std::endl;
	*/
	
	int input;
	int sum;
	
	std::cin >> input;
	sum += input;
	std::cin >> input;
	sum += input;
	std::cin >> input;
	sum += input;
	std::cin >> input;
	sum += input;
	std::cin >> input;
	sum += input;
	
	std::cout << "The average is: " << sum/5 << std::endl;
	
	
	
	return 0;
}