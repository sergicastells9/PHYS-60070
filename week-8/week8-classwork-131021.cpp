#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>

double gauss(double mean, double stddev) {
	static std::default_random_engine generator(time(0));
	std::normal_distribution<double> distribution(mean, stddev);
	double number = -1;
	
	while(number < 0 || number > 100) {
		number = distribution(generator);
	}
	
	return number;
}


int main() {
	int nStudents = 100;
	double mean = 75;
	double sigma = 25;
	std::vector<double> grades;
	
	for(int i = 0; i < nStudents; i++) {
		grades.push_back(gauss(mean, sigma));
	}
	
	double min = *min_element(grades.begin(), grades.end());
	double max = *max_element(grades.begin(), grades.end());
	double average = 0;
	
	for(int i = 0; i < grades.size(); i++) {
		average += grades.at(i);
	}
	
	average /= grades.size();
	
	std::cout << "Max: " << max << std::endl;
	std::cout << "Min: " << min << std::endl;
	std::cout << "Average: " << average << std::endl;
	
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
	
	// Print first grade distribution
	std::cout << "\nGrade distribution:" << std::endl;
	for(auto const &x : cutoffs) {
		std::cout << x.first << ":  " << x.second << std::endl;
	}
	
	while(std::count_if(grades.begin(), grades.end(), [&](double grade) { return grade <= 76; }) > cutoffs.at("B-")) {
		for_each(grades.begin(), grades.end(), [&](double grade) { return grade + 2; });
	}
	
	// Print new grades distribution
	std::cout << "\nGrade distribution:" << std::endl;
	for(auto const &x : cutoffs) {
		std::cout << x.first << ":  " << x.second << std::endl;
	}
	
	return 0;
}