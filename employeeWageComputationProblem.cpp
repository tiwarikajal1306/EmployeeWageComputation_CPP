#include <iostream>
#include <ctime>
#include <list>
#include <vector>
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
	int totalEmpWage;
	list<int> dailyWage;

	void setDailyWage( list<int> dailyWage ) {
		this -> dailyWage = dailyWage;
	}
	void setEmpWage(int totalWage) {
		this -> totalEmpWage = totalWage;
	}

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
	list<EmpWageBuilder> employeeData;

	void addCompany(EmpWageBuilder empWageBuilder)
	{
		employeeData.push_back(empWageBuilder);
	}
	void employeeWage(EmpWageBuilder empWageBuilder)
	{
		list<int> dailyWage;

		int empHrs = 0;
		int totalEmpHrs = 0;
		int empWage = 0;
		int dailyEmpWage = 0;
		int totalEmpWage = 0;
		int totalWorkingDays = 0;

		const int IS_PART_TIME = 1;
		const int IS_FULL_TIME = 2;

		srand(time(0));

		fstream fileStream;
		fileStream.open( "EmployeeWage.csv", ios::out | ios::app );
		fileStream << "Day" << "," << "CompanyName" << "," << "Name" << "," << "DailyEmpWage" << "," << "TotalEmpWage" << endl;

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
			dailyEmpWage = empHrs * empWageBuilder.EMP_RATE_PER_HOUR;
			totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
			dailyWage.push_back(totalEmpWage);
			fileStream << totalWorkingDays << "," << empWageBuilder.companyName << "," << empWageBuilder.empName << "," << dailyEmpWage << "," << totalEmpWage << endl;
		}

		fileStream.close();

		totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
		empWageBuilder.setEmpWage(totalEmpWage);

		cout << empWageBuilder.empName << " " << "Wage is " << totalEmpWage << endl;

		empWageBuilder.setDailyWage(dailyWage);
		addCompany( empWageBuilder );
	}
};

void searchTotalWage(string companyName, list<EmpWageBuilder> employeeData)
{
	for( EmpWageBuilder ewb : employeeData)
	{
		if( ewb.companyName == companyName )
		{
			cout << "Total Wage of " << ewb.companyName << ":" << ewb.totalEmpWage << endl;
			break;
		}
	}
}

int main()
{

        fstream fileStream;
        fileStream.open( "EmployeeWage.csv", ios::out | ios::trunc );

	int months;
	cout << "Enter the number of month" << endl;
	cin >> months;

	struct EmpWageBuilder empWageBuilder[2];
	empWageBuilder[0].employeeDetails("Sonali", months, "BridgeLabz", 20, 10, 60);
	empWageBuilder[1].employeeDetails("NiKita", months, "Amazon", 20, 25, 70);

	struct EmpWage empWage;
	empWage.employeeWage(empWageBuilder[0]);
	empWage.employeeWage(empWageBuilder[1]);

	searchTotalWage("Amazon", empWage.employeeData);
	return 0;
}
