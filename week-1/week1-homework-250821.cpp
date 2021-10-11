/**
	Author: Sergi Castells
	Date: 26-08-2021
	
	Description: Takes two integers as input and prints their sum. Created two functions: ReadNumber and WriteNumber.
**/

#include <iostream>


// Takes user input and stores it as an int. Returns int.
int ReadNumber() {
	int num;
	std::cout << "Input an integer:\n";
	std::cin >> num;
	
	return num;
}

// Takes an int as a parameter and prints it out.
void WriteNumber(int num) {
	std::cout << "Your integer is " << num << std::endl;
}

// Takes two ints as input and adds them. Prints the result.
int main() {
	int num1, num2, num3;
	
	std::cout << "Please provide two integers..." << std::endl;
	num1 = ReadNumber();
	num2 = ReadNumber();
	num3 = num1 + num2;
	
	int&& var = ReadNumber();
	
	WriteNumber(num3);
	
	return 0;
}