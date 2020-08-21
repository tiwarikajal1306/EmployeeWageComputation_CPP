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

	void employeeDetails( string name, int months, string companyName, int  EMP_RATE_PER_HOUR, int NUMBER_OF_WORKING_DAYS , int MAX_HRS_IN_MONTH ) {
		this -> empName = name;
		this -> months = months;
		this -> companyName = companyName;
		this ->  EMP_RATE_PER_HOUR =  EMP_RATE_PER_HOUR;
		this -> NUMBER_OF_WORKING_DAYS = NUMBER_OF_WORKING_DAYS;
		this -> MAX_HRS_IN_MONTH = MAX_HRS_IN_MONTH;
	}
};

struct EmpWage
{

	void employeeWage(EmpWageBuilder empWageBuilder)
	{

		int empHrs = 0;
		int totalEmpHrs = 0;
		int empWage = 0;
		int totalEmpWage = 0;
		int totalWorkingDays = 0;

		const int IS_PART_TIME = 1;
		const int IS_FULL_TIME = 2;

		srand(time(0));

		fstream fileStream;
		fileStream.open( "EmployeeWage.csv", ios::out | ios::app );
		fileStream << "Day" << "," << "CompanyName" << "," << "Name" << "," << "TotalEmpHrs" << "," << "TotalEmpWage" << endl;

		while( totalEmpHrs < empWageBuilder.MAX_HRS_IN_MONTH * empWageBuilder.months &&
			 totalWorkingDays < empWageBuilder.NUMBER_OF_WORKING_DAYS * empWageBuilder.months ) {

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
			totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
			fileStream << totalWorkingDays << "," << empWageBuilder.companyName << "," << empWageBuilder.empName << "," << totalEmpHrs << "," << totalEmpWage << endl;
		}

		fileStream.close();

		totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
		cout << "employee wage is : "<< totalEmpWage << endl;


	}
};

int main()
{

        fstream fileStream;
        fileStream.open( "EmployeeWage.csv", ios::out | ios::trunc );

	int months;
	cout << "Enter the number of month month" << endl;
	cin >> months;

	struct EmpWageBuilder empWageBuilder[2];
	empWageBuilder[0].employeeDetails("Sonali", months, "BridgeLabz", 20, 10, 60);
	empWageBuilder[1].employeeDetails("NiKita", months, "Amazon", 20, 25, 70);

	struct EmpWage empWage;
	empWage.employeeWage(empWageBuilder[0]);
	empWage.employeeWage(empWageBuilder[1]);
	return 0;
}
