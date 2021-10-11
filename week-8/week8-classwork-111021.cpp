#include <vector>
#include <cmath>
#include <iostream>

int main() {
	// 1 & 2
	std::vector<int> v1;
	std::vector<int> v2;
	
	for(int i = 0; i < 10; i++) {
		v1.push_back(i);
		v2.push_back(i+10);
	}
	
	// 3
	v1.insert(v1.end(), v2.begin(), v2.end());
	
	// 4
	for(int i = 0; i < v1.size(); i++) {
		v1.at(i) = v1.at(i) * v1.at(i);
	}
	
	// 5
	std::vector<int> v3;
	
	for(std::vector<int>::iterator iter1 = v1.begin(); iter1 != v1.end(); iter1++) {
		if(*iter1 % 2 != 0) {
			v3.push_back(*iter1);
		}
	}
	
	// 6
	for(std::vector<int>::iterator iter1 = v1.begin(); iter1 != v1.end(); iter1++) {
		if(*iter1 % 2 == 0) {
			iter1 = v1.erase(iter1);
		}
	}
	
	// 7
	if(v1 == v3) {
		std::cout << "Victory!" << std::endl;
	}
	
	// 8
	std::cout << std::endl;
	
	for(std::vector<int>::reverse_iterator iter2 = v3.rbegin(); iter2 != v3.rend(); iter2++) {
		std::cout << *iter2 << std::endl;
	}
	
	return 0;
}