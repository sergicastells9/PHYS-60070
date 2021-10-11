#include <iostream>




int main() {
	float grades[] = {5,4.5,4,3.5,3,2};
	float students[] = {3,5,7,4,1,1};
	float wsum;
	float sum;
	
	float *pGrades = grades;
	float *pStudents = students;
	
	for(int i = 0; i < 6; i++) {
		wsum += *(pGrades+i) * *(pStudents+i);
		sum += *(pStudents+i);
	}
	
	std::cout << wsum/sum << std::endl;
	
	
	
	return 0;
}