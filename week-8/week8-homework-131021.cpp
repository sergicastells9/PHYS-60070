/*
	Author: Sergi Castells
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>


// Generates Gaussian distribution
double gauss(double mean, double stddev) {
	static std::default_random_engine generator(time(0));
	std::normal_distribution<double> distribution(mean, stddev);
	double number = -1;
	
	while(number < 0 || number > 100) {
		number = distribution(generator);
	}
	
	return number;
}


// Count grades in ranges
std::map<std::string, int> count(std::map<std::string, int> cutoffs, std::vector<double> grades) {
	cutoffs["A"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade >= 94; });
	cutoffs["A-"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 94 && grade >= 91; });
	cutoffs["B+"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 91 && grade >= 88; });
	cutoffs["B"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 88 && grade >= 82; });
	cutoffs["B-"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 82 && grade >= 79; });
	cutoffs["C+"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 79 && grade >= 76; });
	cutoffs["C"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 76 && grade >= 70; });
	cutoffs["C-"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 70 && grade >= 67; });
	cutoffs["D"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 67 && grade >= 64; });
	cutoffs["F"] = std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade < 64; });
	
	return cutoffs;
}


int main() {
	// Set up variables
	int nStudents = 100; // low sample size makes it a bad distribution (I checked)
	double mean = 75;
	double sigma = 25;
	std::vector<double> grades;
	
	// Do Gaussian distribution
	for(int i = 0; i < nStudents; i++) {
		grades.push_back(gauss(mean, sigma));
	}
	
	// Get min, max, avg
	double min = *min_element(grades.begin(), grades.end());
	double max = *max_element(grades.begin(), grades.end());
	double average = 0;
	
	for(int i = 0; i < grades.size(); i++) {
		average += grades.at(i);
	}
	
	average /= nStudents;
	
	
	// Print stats
	std::cout << "Max: " << max << std::endl;
	std::cout << "Min: " << min << std::endl;
	std::cout << "Average: " << average << std::endl;
	
	// Set up map for grade counting
	std::map<std::string, int> cutoffs;
	cutoffs["A"] = 0;
	cutoffs["B+"] = 0;
	cutoffs["B"] = 0;
	cutoffs["B-"] = 0;
	cutoffs["C+"] = 0;
	cutoffs["C"] = 0;
	cutoffs["C-"] = 0;
	cutoffs["D"] = 0;
	cutoffs["F"] = 0;
	
	// Count grades in ranges
	cutoffs = count(cutoffs, grades);
	
	// Print first grade distribution
	// The map sorts Cs above C+s so it looks weird when printing
	std::cout << "\nGrade distribution:" << std::endl;
	for(auto const &x : cutoffs) {
		std::cout << x.first << ":  " << x.second << std::endl;
	}
	
	// Set up curvedGrades vector
	std::vector<double> curvedGrades = grades;
	
	// Curve grades
	int underC = cutoffs.at("C+") + cutoffs.at("C") + cutoffs.at("C-") + cutoffs.at("D") + cutoffs.at("F");
	int overB = cutoffs.at("B-") + cutoffs.at("B") + cutoffs.at("B+") + cutoffs.at("A-") + cutoffs.at("A");
	while(underC >= overB) {
		for(int i = 0; i < curvedGrades.size(); i++){
			// Increment and update cutoffs
			curvedGrades.at(i) += 2;
			cutoffs = count(cutoffs, curvedGrades);
			
			// Account for grades over 100
			if(curvedGrades.at(i) > 100) {
				curvedGrades.at(i) = 100;
			}
			
			// Update counters
			underC = cutoffs.at("C+") + cutoffs.at("C") + cutoffs.at("C-") + cutoffs.at("D") + cutoffs.at("F");
			overB = cutoffs.at("B-") + cutoffs.at("B") + cutoffs.at("B+") + cutoffs.at("A-") + cutoffs.at("A");
		}
	}
	
	// Get curved min, max, avg
	min = *min_element(curvedGrades.begin(), curvedGrades.end());
	max = *max_element(curvedGrades.begin(), curvedGrades.end());
	average = 0;
	
	// Average curved grades
	for(int i = 0; i < curvedGrades.size(); i++) {
		average += curvedGrades.at(i);
	}
	
	average /= curvedGrades.size();
	
	
	// Print curved stats
	std::cout << "\n\nCurved Max: " << max << std::endl;
	std::cout << "Curved Min: " << min << std::endl;
	std::cout << "Curved Average: " << average << std::endl;
	
	// Print curved grades distribution
	std::cout << "\nGrade distribution:" << std::endl;
	for(auto const &x : cutoffs) {
		std::cout << x.first << ":  " << x.second << std::endl;
	}
	
	return 0;
}