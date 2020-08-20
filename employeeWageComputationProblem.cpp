#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

struct EmpWageBuilder
{

string empName;
int months;
string companyName;
int  EMP_RATE_PER_HOUR;
int NUMBER_OF_WORKING_DAYS;
int MAX_HRS_IN_MONTH;

EmpWageBuilder( string name, int months, string companyName, int  EMP_RATE_PER_HOUR, int NUMBER_OF_WORKING_DAYS , int MAX_HRS_IN_MONTH ) {
	this -> empName = name;
	this -> months = months;
	this -> companyName = companyName;
	this ->  EMP_RATE_PER_HOUR =  EMP_RATE_PER_HOUR;
	this -> NUMBER_OF_WORKING_DAYS = NUMBER_OF_WORKING_DAYS;
	this -> MAX_HRS_IN_MONTH = MAX_HRS_IN_MONTH;
}


int empHrs = 0;
int totalEmpHrs = 0;
int empWage = 0;
int totalEmpWage = 0;
int totalWorkingDays = 0;


void employeeWage()
{
	const int IS_PART_TIME = 1;
	const int IS_FULL_TIME = 2;

	srand(time(0));

	fstream fileStream;
	fileStream.open( "EmployeeWage.csv", ios::out | ios::app );
	fileStream << "Day" << "," << "CompanyName" << "," << "Name" << "," << "TotalEmpHrs" << "," << "TotalEmpWage" << endl;

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
		fileStream << totalWorkingDays << "," << companyName << "," << empName << "," << totalEmpHrs << "," << totalEmpWage << endl;
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

	EmpWageBuilder bridgeLabz("Kajal", totalMonths, "BridgeLabz", 20, 20, 100);
	bridgeLabz.employeeWage();
	sleep(3);

	EmpWageBuilder amazon("NiKita", totalMonths, "Amazon", 20, 25, 70);
	amazon.employeeWage();
	return 0;
}
