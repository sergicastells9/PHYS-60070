/*
	Author: Sergi Castells
	Description: Problem 5/6 asks user for input (name, phone number) and checks input.
	Problem 10 
*/


#include <iostream>
#include <string>
#include <fstream>


int main() {
	/*
	// Problem 5/6
	std::string name;
	char first;
	char vowel[5] = {'a', 'e', 'i', 'o', 'u'};
	bool v = false;
	
	std::cout << "Please input your name: ";
	first = std::cin.peek();
	std::cin >> name;
	
	// Check if name starts with a vowel
	for(int i = 0; i < 5; i++) {
		if(tolower(first) == vowel[i]) {
			std::cout << "Your name " << name << " starts with a vowel." << std::endl;
			v = true;
		}
	}
	
	if(v == false) {
		std::cout << "Your name doesn't start with a vowel." << std::endl;
	}
	
	
	
	std::string phone;
	std::cout << "Please input your phone number: ";
	std::cin >> phone;
	
	// Check if each character is good. Break if not
	for(int i = 0; i < 14; i++) {
		if(i == 0) {
			if(phone[i] != '(') {
				std::cout << "Formatting incorrect. Missing parentheses around first three numbers." << std::endl;
				break;
			}
		}
		if(i == 4) {
			if(phone[i] != ')') {
				std::cout << "Formatting incorrect. Missing parentheses around first three numbers." << std::endl;
				break;
			}
		}
		if(i == 5 || i == 9) {
			if(phone[i] != '-') {
				std::cout << "Formatting incorrect. Missing dashes." << std::endl;
				break;
			}
		}
		if(i != 0 && i != 4 && i != 5 && i != 9){
			if(isdigit(phone[i]) != true) {
				std::cout << "Formatting incorrect. Missing numbers." << std::endl;
				break;
			}
		}
	}
	
	
	std::string age;
	
	std::cout << "What is your age?" << std::endl;
	std::cin >> age;
	
	// Checks if characters are all digits.
	for(int i = 0; i < age.length(); i++) {
		if(!isdigit(age[i])) {
			std::cout << "At least one character is not a number." << std::endl;
			break;
		}
	}
	*/
	
	
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