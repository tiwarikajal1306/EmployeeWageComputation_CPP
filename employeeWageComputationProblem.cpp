#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int EMP_RATE_PER_HOUR = 20;

int empHrs = 0;
int empWage = 0;

int main() {
	srand(time(0));
	int is_Present = rand() % 2 + 1;
	if(is_Present == 1){
		empHrs = 8;
	}
	else{
		empHrs = 0;
	}

	empWage = empHrs * EMP_RATE_PER_HOUR;
	cout << empWage << endl;
return 0;

}
