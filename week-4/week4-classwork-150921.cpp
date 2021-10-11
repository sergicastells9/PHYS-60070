#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>



int main() {
	char name[40];
	char fname[20];
	char lname[20];
	char phone[12];
	char city[20];
	
	std::cout << "Input a first and last name:\n";
	std::cin.getline(name, 40);
	
	bool space = false;
	for(int i = 0; i < strlen(name); i++) {
		if(isspace(name[i])) {
			space = true;
		}
		
		else if(space == false) {
			fname[i] = name[i];
		}
		else if(space == true) {
			lname[i] = name[i];
		}
	}
	
	fname[0] = toupper(fname[0]);
	lname[0] = toupper(lname[0]);
	
	
	std::cout << "Input your phone number:\n";
	std::cin.getline(phone, 12);
	
	for(int i = 0; i < strlen(phone); i++) {
		if( !((i == 3 || i == 7) && phone[i] == '-') || !((i != 3 || i != 7) && isdigit(phone[i]))) {
			std::cout << "ERROR: Phone number formatting incorrect!" << std::endl;
			exit(1);
		}
	}
	
	std::cout << "Input your city of residence:\n";
	std::cin.getline(city, 20);
	
	char SB[] = "south bend";
	for(int i = 0; i < strlen(city); i++) {
		city[i] = tolower(city[i]);
		if(!(SB[i] == city[i])) {
			std::cout << "Go Irish!" << std::endl;
		}
		else {
			std::cout << "Welcome to South Bend!" << std::endl;
		}
	}
	
	
	
	
	
	return 0;
}