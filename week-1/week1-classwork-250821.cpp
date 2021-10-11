#include <iostream>

using namespace std;

char n = '\n';

int main() {
	int nValue;
	double dValue;
	
	cout << "int\t" << sizeof(int) << n;
	cout << "nValue\t" << sizeof(nValue) << n;
	cout << "double\t" << sizeof(double) << n;
	cout << "dValue\t" << sizeof(dValue) << n;
	cout << "char\t" << sizeof(char) << n;
	
	
	nValue = 2147483646;
	cout << nValue << n;
	cout << nValue + 1 << n;
	cout << nValue + 2 << n;
	
	return 0;
}