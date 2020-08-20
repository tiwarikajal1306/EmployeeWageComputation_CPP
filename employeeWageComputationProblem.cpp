#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

struct CalculateEmpWage
{

int EMP_RATE_PER_HOUR = 20;
int NUMBER_OF_WORKING_DAYS = 20;
int MAX_HRS_IN_MONTH = 100;

int empHrs = 0;
int totalEmpHrs = 0;
int empWage = 0;
int totalEmpWage = 0;
int totalWorkingDays = 0;

void employeeWage(string name, int months )
{
	const int IS_PART_TIME = 1;
	const int IS_FULL_TIME = 2;

	srand(time(0));

	fstream fileStream;
	fileStream.open( "EmployeeWage.csv", ios::out | ios::app );
	fileStream << "Day" << "," << "Name" << "," << "TotalEmpHrs" << "," << "TotalEmpWage" << endl;

	while ( totalEmpHrs < MAX_HRS_IN_MONTH * months && totalWorkingDays < NUMBER_OF_WORKING_DAYS * months  ) {
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
		fileStream << totalWorkingDays << "," << name << "," << totalEmpHrs << "," << totalEmpWage << endl;
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

}
};

int main()
{

        fstream fileStream;
        fileStream.open( "EmployeeWage.csv", ios::out | ios::trunc );

	int totalMonths;
	cout << "Enter the number of month month" << endl;
	cin >> totalMonths;

	struct CalculateEmpWage calculateEmpWage1;
	calculateEmpWage1.employeeWage("Kajal", totalMonths);
	sleep(3);

	struct CalculateEmpWage calculateEmpWage2;
	calculateEmpWage2.employeeWage("NiKita", totalMonths);
	return 0;
}
