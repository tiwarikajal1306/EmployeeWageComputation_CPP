#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int EMP_RATE_PER_HOUR = 20;
const int IS_PART_TIME = 1;
const int IS_FULL_TIME = 2;
const int NUMBER_OF_WORKING_DAYS = 20;
const int MAX_HRS_IN_MONTH = 100;

int empHrs = 0;
int totalEmpHrs = 0;
int empWage = 0;
int totalEmpWage = 0;
int totalWorkingDays = 0;

int main()
{
	srand(time(0));

	fstream fileStream;
	fileStream.open( "EmployeeWage.csv", ios::out );
	fileStream << "totalEmpHrs" << "," << "totalEmpWage" << endl;

	while ( totalEmpHrs < MAX_HRS_IN_MONTH && totalWorkingDays < NUMBER_OF_WORKING_DAYS ) {
		totalWorkingDays++;
		int employee_Check = rand() % 3 + 1;

		switch( employee_Check ) {
			case IS_PART_TIME:
				empHrs = 4;
				break;

			case IS_FULL_TIME:
				empHrs = 8;
				break;
			default:
				empHrs = 0;
		}

		totalEmpHrs +=empHrs;
		totalEmpWage = totalEmpHrs * EMP_RATE_PER_HOUR;
		fileStream << totalEmpHrs << "," << totalEmpWage << endl;
	}
	fileStream.close();

	totalEmpWage = totalEmpHrs * EMP_RATE_PER_HOUR;
	cout << "employee wage is : "<< totalEmpWage << endl;

	fstream fin;
	string data;
	cout<<"\nCSV file has been successfully created..!!";
        cout<<"\n\nDisplaying the content of CSV file=>\n\n";

	fin.open( "EmployeeWage.csv", ios::in );

		 while( getline (fin, data) ) {
                        cout << data << endl;
                }

	return 0;
}
