/*
	Author: Sergi Castells
	Description: Problem 1
	
	Exit codes:
				0 - OK
				1 - choice != 1 or 2
				2 - Z not <= A or Elem and A invalid
				3 - min not < max
				4 - Projectile not within restrictions
				5 - File falied to open
	
	Order of masses:
				0 - Target mass
				1 - Projectile mass
				2-10 - Masses for reaction channels
	
	Order of reaction channels:
				- gamma
				- d
				- t
				- n
				- 2n
				- 3n
				- alpha
				- 3He
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>



// Struct for target/projectile
struct nuc {
	int Z;
	int A;
	std::string elem;
	
	double mass;
};

// Struct for decay products
struct prd {
	std::string elem;
	std::string decay;
	
	int Z;
	int A;
	double* mass;
};

// Struct for info needed for Q-values
struct Q {
	nuc target;
	nuc proj;
	prd* prod;
	
	double* range;
	double* qValues;
};

// Determines if user wants to provide Z and A or Element Name and A
int getChoice() {
	int choice;
	
	std::cout << "Specify information via:\n\t1) Z and A \t 2) Element Name and A" << std::endl;
	std::cout << "> ";
	std::cin >> choice;
	
	if(choice != 1 && choice != 2) {
		std::cout << "Must provide a value of either 1 or 2." << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(1);
	}
	
	return choice;
}


// Prompts user for bounds on Q-values
double* getRange() {
	double* vals = new double[2];
	
	std::cout << "Specify minimum and maximum values of Q-value:" << std::endl;
	std::cout << "> ";
	std::cin >> vals[0] >> vals[1];
	std::cout << std::endl;
	
	if(!(vals[0] < vals[1])) {
		std::cout << "Minimum must be strictly less than maximum." << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(3);
	}
	
	return vals;
}


// Prompts user for Z/A or Elem/A and returns those values
std::string* setTrg(int ch) {
	std::string* vals = new std::string[2];
	
	// Checks Z/A or Elem/A choice
	if(ch == 1) {
		std::cout << "\nSpecify Z and A:" << std::endl;
		std::cout << "> ";
		std::cin >> vals[0] >> vals[1];
		std::cout << std::endl;
		
		if(!(std::stoi(vals[0]) <= std::stoi(vals[1]))) {
			std::cout << "Z must be less than or equal to A." << std::endl;
			std::cout << "Exiting program..." << std::endl;
			exit(2);
		}
		if(std::stoi(vals[0]) < 0 || std::stoi(vals[1]) < 0) {
			std::cout << "Z/A must be greater than zero." << std::endl;
			std::cout << "Exiting program..." << std::endl;
			exit(2);
		}
	}
	
	if(ch == 2) {
		std::cout << "\nSpecify Element Name and A:" << std::endl;
		std::cout << "> ";
		std::cin >> vals[0] >> vals[1];
		std::cout << std::endl;
		
		if(std::stoi(vals[1]) < 0) {
			std::cout << "A must be greater than zero." << std::endl;
			std::cout << "Exiting program..." << std::endl;
			exit(2);
		}
	}
	
	return vals;
}
// Prompts user for projectile and returns those values in nuc instance
nuc setPrj(nuc &proj) {
	std::string prj;
	
	std::cout << "Specify projectile (p, d, t, 3He, alpha):" << std::endl;
	std::cout << "> ";
	std::cin >> prj;
	std::cout << std::endl;
	
	bool p = prj == "p";
	bool d = prj == "d";
	bool t = prj == "t";
	bool He = prj == "3He";
	bool alpha = prj == "alpha";
	
	// Check restrictions
	if(!p && !d && !t && !He && !alpha) {
		std::cout << "Projectile must be from the required list." << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(4);
	}
	
	// Load values into proj
	if(p) {
		proj.Z = 1;
		proj.A = 1;
		proj.elem = "p";
	}
	if(d) {
		proj.Z = 1;
		proj.A = 2;
		proj.elem = "d";
	}
	if(t) {
		proj.Z = 1;
		proj.A = 3;
		proj.elem = "t";
	}
	if(He) {
		proj.Z = 2;
		proj.A = 3;
		proj.elem = "He";
	}
	if(alpha) {
		proj.Z = 2;
		proj.A = 4;
		proj.elem = "alpha";
	}
	
	return proj;
}


// Fills projectile nuc instance with masses
nuc fillPrj(nuc &proj, nuc* all) {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 3436; j++) {
			if(proj.Z == all[j].Z && proj.A == all[j].A) {
				proj.mass = all[j].mass;
				break;
			}
		}
	}
	
	return proj;
}


// Fills trg nuc instance (also retrieves missing Z/elem)
nuc fillTrg(nuc &target, nuc* all, std::string* vals, int ch) {
	bool valid = false;
	
	// Checks Z/A and Elem/A choice
	if(ch == 1) {
		target.Z = std::stoi(vals[0]);
		target.A = std::stoi(vals[1]);
		
		for(int i = 0; i < 3436; i++) {
			if(target.Z == all[i].Z && target.A == all[i].A) {
				valid = true;
				target.elem = all[i].elem;
				target.mass = all[i].mass;
				break;
			}
		}
	}
	
	if(ch == 2) {
		target.elem = vals[0];
		target.A = std::stoi(vals[1]);
		
		for(int i = 0; i < 3436; i++) {
			if(target.elem == all[i].elem && target.A == all[i].A) {
				valid = true;
				target.Z = all[i].Z;
				target.mass = all[i].mass;
				break;
			}
		}
	}
	
	if(!valid) {
		std::cout << "Invalid input for target." << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(2);
	}
	
	return target;
}


// Fills prd array in Q instance
Q fillPrd(Q &q, nuc &target, nuc &proj, nuc* all) {
	// Z/A conservation and decay Z/A/Elem
	int sumZ = target.Z + proj.Z;
	int sumA = target.A + proj.A;
	int decayZ[8] = {0, 1, 1, 0, 0, 0, 2, 2};
	int decayA[8] = {0, 2, 3, 1, 2, 3, 4, 3};
	std::string decay[8] = {"gamma", "d", "t", "n", "2n", "3n", "alpha", "3He"};
	
	// Sets product name, decay name, and masses (mass[0] = product mass, mass[1] = decay mass)
	for(int i = 0; i < 8; i++) {
		if(decayZ[i] == 0 && decayA[i] == 0) {
			q.prod[i].mass[1] = 0;
			q.prod[i].Z = 0;
			q.prod[i].A = 0;
		}
		for(int j = 0; j < 3436; j++) {
			if(sumZ - decayZ[i] == all[j].Z && sumA - decayA[i] == all[j].A) {
				q.prod[i].elem = all[j].elem;
				q.prod[i].decay = decay[i];
				q.prod[i].mass[0] = all[j].mass;
				q.prod[i].Z = all[j].Z;
				q.prod[i].A = all[j].A;
			}
			if(decayZ[i] == all[j].Z && decayA[i] == all[j].A) {
				q.prod[i].mass[1] = all[j].mass;
			}
		}
	}
	
	q.prod[4].mass[1] = q.prod[3].mass[1] * 2;
	q.prod[5].mass[1] = q.prod[3].mass[1] * 3;
	
	return q;
}


// Fill Q struct instance and dynamically allocates arrays as needed
Q fillQ(Q &q, nuc &target, nuc &proj, double* range) {
	q.target = target;
	q.proj = proj;
	q.range = range;
	q.prod = new prd[8];
	q.qValues = new double[8];
	
	for(int i = 0; i < 8; i++) {
		q.prod[i].mass = new double[2];
	}
	
	return q;
}


// Calculates Q-values
Q calcQValues(Q &q) {
	for(int i = 0; i < 8; i++) {
		q.qValues[i] = (q.target.mass + q.proj.mass) - (q.prod[i].mass[0] + q.prod[i].mass[1]);
	}
	
	return q;
}


// Reads in from mass16.txt file
nuc* readFile() {
	nuc* all = new nuc[3436];
	std::fstream file("mass16.txt", std::fstream::in);
	
	// Set up variables
	std::string tmp;
	int Z;
	int A;
	std::string elem;
	double mass;
	
	// Line variables
	int line_start;
	
	// Check if file opened successfully
	if(!file.is_open()) {
		std::cout << "File failed to open!" << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(5);
	}
	
	// Skip to first line with data
	for(int i = 0; i < 39; i++) {
		std::getline(file, tmp);
	}
	
	// Loop through file until end
	for(int i = 0; i < 3436; i++) {
		line_start = file.tellp();
		file.seekg(1, file.cur);
		file >> tmp;
		file >> tmp;
		
		file >> Z;
		file >> A;
		file >> elem;
		
		file.seekg(line_start + 28, file.beg);
		file >> tmp;
		mass = std::stod(tmp.substr(0, tmp.find("#")));
		
		all[i].Z = Z;
		all[i].A = A;
		all[i].elem = elem;
		all[i].mass = mass;
		
		std::getline(file, tmp);
	}
		
	file.close();
	return all;
}


// Prints Q-values to screen with (*) if Q is within bounds
void printQValues(Q q) {
	std::cout << std::setw(18) << "\n\t\t-- Reaction --";
	std::cout << std::setw(18) << "\t\t\t-- Q-values (keV) --";
	std::cout << std::setw(18) << "\t\t\t-- Q-values (keV) --";
	std::cout << "\t\tMatch"<< std::endl;
	
	for(int i = 0; i < 8; i++) {
		std::cout << std::setw(10) << q.target.elem << "-" << q.target.A << std::setw(1) << " + " << std::setw(2) << q.proj.elem << " -> ";
		std::cout << std::setw(4) << q.prod[i].elem << "-" << q.prod[i].A << std::setw(1) << " + "  << std::setw(2) << q.prod[i].decay;
		std::cout << "\t\t";
		std::cout << std::setw(8) << q.qValues[i];
		
		// Mark "good" Q-values
		if(q.qValues[i] >= q.range[0] && q.qValues[i] <= q.range[1]) {
			std::cout << std::setw(12) << "\t\t (*)" << std::endl;
		}
		else {
			std::cout << std::setw(12) << "\t\t ( )" << std::endl;
		}
	}
}


// Saves Reaction and Q-values to a file "results.txt"
void saveQValues(Q q) {
	std::fstream file("results.txt", std::fstream::out);
	
	// Check if file opened successfully
	if(!file.is_open()) {
		std::cout << "File failed to open!" << std::endl;
		std::cout << "Exiting program..." << std::endl;
		exit(5);
	}
	
	// Write header
	file << std::setw(18) << "\n\t\t-- Reaction --";
	file << std::setw(18) << "\t\t\t\t-- Q-values (keV) --" << std::endl;
	
	// Write Q-values
	for(int i = 0; i < 8; i++) {
		if(q.qValues[i] >= q.range[0] && q.qValues[i] <= q.range[1]) {
			file << std::setw(10) << q.target.elem << "-" << q.target.A << std::setw(1) << " + " << std::setw(2) << q.proj.elem << " -> ";
			file << std::setw(4) << q.prod[i].elem << "-" << q.prod[i].A << std::setw(1) << " + "  << std::setw(2) << q.prod[i].decay;
			file << "\t\t";
			file << std::setw(8) << q.qValues[i];
		}
	}
}


int main() {
	// Initialize structs
	nuc target;
	nuc proj;
	Q q;
	nuc* all;
	
	// Target Setup
	std::cout << "\n\t\t-- Target information --" << std::endl;
	int trg_choice = getChoice();
	std::string* trg_values = setTrg(trg_choice);
	
	// Projectile Setup and Check
	std::cout << "\n\t\t-- Projectile information --" << std::endl;
	proj = setPrj(proj);
	
	// Range Setup
	std::cout << "\n\t\t-- Range information --" << std::endl;
	double* range = getRange();
	
	// Read file and store data
	all = readFile();
	
	// Fill structs
	// Checks for issues with inputs here
	target = fillTrg(target, all, trg_values, trg_choice);
	proj = fillPrj(proj, all);
	q = fillQ(q, target, proj, range);
	q = fillPrd(q, target, proj, all);
	
	// Calculate Q-values
	q = calcQValues(q);
	
	// Print and Save Q-values
	printQValues(q);
	saveQValues(q);
	
	
	// Delete dynamically allocated memory
	delete[] trg_values;
	delete[] range;
	delete[] all;
	for(int i = 0; i < 8; i++) { delete[] q.prod[i].mass; }
	delete[] q.prod;
	
	return 0;
}