/*
	Author: Sergi Castells
	Description: Problem 1
	
	Exit codes:
				0 - OK
				1 - choice != 1 or 2
				2 - Z not <= A
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
		exit(3);
	}
	
	return vals;
}


// Prompts user for Z/A or Elem/A and returns those values
std::string* setTrg(int ch) {
	std::string* vals = new std::string[2];
	
	if(ch == 1) {
		std::cout << "\nSpecify Z and A:" << std::endl;
		std::cout << "> ";
		std::cin >> vals[0] >> vals[1];
		std::cout << std::endl;
		
		if(!(std::stoi(vals[0]) <= std::stoi(vals[1]))) {
			std::cout << "Z must be less than or equal to A." << std::endl;
			exit(2);
		}
	}
	
	if(ch == 2) {
		std::cout << "\nSpecify Element Name and A:" << std::endl;
		std::cout << "> ";
		std::cin >> vals[0] >> vals[1];
		std::cout << std::endl;
	}
	
	return vals;
}
// Prompts user for projectile and returns those values in nuc instance
nuc setPrj(nuc proj) {
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
	
	if(!p && !d && !t && !He && !alpha) {
		std::cout << "Projectile must be from the required list." << std::endl;
		exit(4);
	}
	
	// Load values into proj
	if(p) {
		proj.Z = 1;
		proj.A = 1;
		proj.elem = "H";
	}
	if(d) {
		proj.Z = 1;
		proj.A = 2;
		proj.elem = "H";
	}
	if(t) {
		proj.Z = 1;
		proj.A = 3;
		proj.elem = "H";
	}
	if(He) {
		proj.Z = 2;
		proj.A = 3;
		proj.elem = "He";
	}
	if(alpha) {
		proj.Z = 2;
		proj.A = 4;
		proj.elem = "He";
	}
	
	return proj;
}


// Fills trg nuc instance (also retrieves missing Z/elem)
nuc fillTrg(nuc &target, nuc* all, std::string* vals, int ch) {
	if(ch == 1) {
		target.Z = std::stoi(vals[0]);
		target.A = std::stoi(vals[1]);
		
		for(int i = 0; i < 3436; i++) {
			if(target.Z == all[i].Z && target.A == all[i].A) {
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
				target.Z = all[i].Z;
				target.mass = all[i].mass;
				break;
			}
		}
	}
	
	return target;
}


// Fills prd array in Q instance
Q fillPrd(Q &q, nuc &target, nuc &proj, nuc* all) {
	std::cout << "inside 1" << std::endl;
	int sumZ = target.Z + proj.Z;
	int sumA = target.A + proj.A;
	int decayZ[8] = {0, 1, 1, 0, 0, 0, 2, 2};
	int decayA[8] = {0, 2, 3, 1, 2, 3, 4, 3};
	std::string decay[8] = {"gamma", "d", "t", "n", "2n", "3n", "alpha", "3He"};
	
	for(int i = 0; i < 8; i++) {
		if(decayZ[i] == 0 && decayA[i] == 0) {
			q.prod[i].mass[1] = 0;
		}
		std::cout << "inside 2" << std::endl;
		for(int j = 0; j < 3436; j++) {
			if(sumZ - decayZ[i] == all[j].Z && sumA - decayA[i] == all[j].A) {
				q.prod[i].elem = all[j].elem;
				q.prod[i].decay = decay[i];
				q.prod[i].mass[0] = all[j].mass;
			}
			if(decayZ[i] == all[j].Z && decayA[i] == all[j].A) {
				q.prod[i].mass[1] = all[j].mass;
			}
		}
	}
	
	std::cout << "inside 3" << std::endl;
	return q;
}


// Fill Q struct instance (also calculates Q-values)
Q fillQ(Q q, nuc target, nuc proj, double* range) {
	q.target = target;
	q.proj = proj;
	q.range = range;
	
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
	
	// Housekeeping variables
	int line_start;
	
	// Check if file opened successfully
	if(!file.is_open()) {
		std::cout << "File failed to open!" << std::endl;
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
	std::cout << "\n\t\t-- Q-values --" << std::endl;
	
	for(int i = 0; i < 8; i++) {
		std::cout << std::setw(18) << q.target.elem << " + " << q.proj.elem << " -> " << q.prod[i].elem << " + "  << q.prod[i].decay;
		std::cout << "\t\t";
		std::cout << std::setw(18) << q.qValues[i];
		
		if(q.qValues[i] < q.range[0] || q.qValues[i] > q.range[1]) {
			std::cout << "\t\t (*)" << std::endl;
		}
		else {
			std::cout << "\t\t ( )" << std::endl;
		}
	}
}


// Saves Reaction and Q-values to a file "results.txt"
void saveQValues(Q q) {
	std::fstream file("results.txt", std::fstream::out);
	
	// Check if file opened successfully
	if(!file.is_open()) {
		std::cout << "File failed to open!" << std::endl;
		exit(5);
	}
	
	// Write header
	file << "     Reaction     \t\t      Q-Value     " << std::endl;
	
	for(int i = 0; i < 8; i++) {
		if(q.qValues[i] < q.range[0] || q.qValues[i] > q.range[1]) {
			file << std::setw(18) << q.target.elem << " + " << q.proj.elem << " -> " << q.prod[i].elem << " + "  << q.prod[i].decay;
			file << "\t\t";
			file << std::setw(18) << q.qValues[i] << std::endl;
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
	target = fillTrg(target, all, trg_values, trg_choice);

	//This works so far
	
	q = fillQ(q, target, proj, range);
	std::cout << "test 1" << std::endl;
	q = fillPrd(q, target, proj, all); // testing this
	std::cout << "test 2" << std::endl;
	q = calcQValues(q);
	
	// Print and Save Q-values
	printQValues(q);
	saveQValues(q);
	
	free(trg_values);
	free(range);
	free(all);
	return 0;
}