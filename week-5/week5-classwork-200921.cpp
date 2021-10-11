#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>


int main() {
	/*
	char buf[10];
	char ch;
	
	std::cin >> buf;
	std::cout << buf << std::endl;
	std::cin >> std::setw(10) >> buf;
	std::cout << buf << std::endl;
		
	while(std::cin >> ch) {
		std::cout << ch << std::endl;
	}
	*/
	
	std::string name;
	char first;
	char vowel[5] = {'a', 'e', 'i', 'o', 'u'};
	bool v = false;
	
	std::cout << "Please input your name: ";
	first = std::cin.peek();
	std::cin >> name;
	
	std::cout << first << std::endl;
	
	for(int i = 0; i < 5; i++) {
		if(tolower(first) == vowel[i]) {
			std::cout << "Your name " << name << " starts with a vowel." << std::endl;
			v = true;
		}
	}
	
	if(v == false) {
		std::cout << "Your name doesn't start with a vowel." << std::endl;
	}
	
	
	
	
	
	return 0;
}