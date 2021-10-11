/*
	Author: Sergi Castells
	Description: Creates an array of grades from grades.dat. Finds min/max grade and calculates average. Returns number of students
		that received an A and number of students that failed.
*/


#include <iostream>
#include <fstream>
#include <string>


int main() {
	// Set up variables
	std::fstream file("grades.dat");
	std::string buf;
	int size;
	int low = 100;
	int high = 0;
	int failed = 0;
	int a = 0;
	float avg;
	
	// Get the number of students from the file and skip to data
	std::getline(file, buf, ':');
	file >> size;
	std::getline(file, buf);
	
	int* grades = new int[size];
	
	// Loop through file
	for(int i = 0; i < 100; i++) {
		// Add score to grades array and start computing avg
		std::getline(file, buf, '\t');
		file >> grades[i];
		avg += grades[i];
		
		// Check failing, getting an A, high, low scores and increment
		if(grades[i] < low) {
			low = grades[i];
		}
		if(grades[i] > high) {
			high = grades[i];
		}
		if(grades[i] >= 94) {
			a++;
		}
		if(grades[i] < 60) {
			failed++;
		}
	}
	
	// Calculate avg
	avg = avg/size;
	
	// Print results
	std::cout << "Highest score: " << high << std::endl;
	std::cout << "Lowest score: " << low << std::endl;
	std::cout << "Average score: " << avg << std::endl;
	
	std::cout << "Received an A: " << a << std::endl;
	std::cout << "Failed class: " << failed << std::endl;
	
	// Free memory
	delete grades;
	
	return 0;
}