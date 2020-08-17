#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int EMP_RATE_PER_HOUR = 20;
const int IS_PART_TIME = 1;
const int IS_FULL_TIME = 2;

int empHrs = 0;
int empWage = 0;

int main() {
	srand(time(0));
	int employee_Check = rand() % 3 + 1;
	if( employee_Check == IS_PART_TIME ) {
		empHrs = 4;
		cout << "Employee wage for Part Time" << endl;
	} else if( employee_Check == IS_FULL_TIME ) {
		empHrs = 8;
		cout << "Employee wage for Full Time" << endl;
	} else {
		empHrs = 0;
		cout << "Employee is absent" << endl;
	}

	empWage = empHrs * EMP_RATE_PER_HOUR;
	cout << empWage << endl;
return 0;

}
