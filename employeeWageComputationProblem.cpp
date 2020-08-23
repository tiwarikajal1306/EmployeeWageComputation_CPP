#include <iostream>
#include <ctime>
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
	int EMP_RATE_PER_HOUR;
	int NUMBER_OF_WORKING_DAYS;
	int MAX_HRS_IN_MONTH;
	int totalEmpWage;
	vector<int> dailyWage;
	vector<int> monthWage;

	void setDailyWage( vector<int> dailyWage ) {
		this -> dailyWage = dailyWage;
	}
	void setEmpWage(int totalWage) {
		this -> totalEmpWage = totalWage;
	}

	void setMonthWage(vector<int> storeMonthWage)
        {
                this -> monthWage = storeMonthWage;
        }

	void employeeDetails( string name, int months, string companyName, int  EMP_RATE_PER_HOUR, int NUMBER_OF_WORKING_DAYS , int MAX_HRS_IN_MONTH ) {
		this -> empName = name;
		this -> months = months;
		this -> companyName = companyName;
		this -> EMP_RATE_PER_HOUR =  EMP_RATE_PER_HOUR;
		this -> NUMBER_OF_WORKING_DAYS = NUMBER_OF_WORKING_DAYS;
		this -> MAX_HRS_IN_MONTH = MAX_HRS_IN_MONTH;
	}
};

struct EmpWage
{
	vector<EmpWageBuilder> employeeData;

	void addCompany(EmpWageBuilder empWageBuilder)
	{
		employeeData.push_back(empWageBuilder);
	}
	void employeeWage(EmpWageBuilder empWageBuilder)
	{
		vector<int> dailyWage;
		vector<int> storeMonthWage;

		int empHrs = 0;
		int totalEmpHrs = 0;
		int empWage = 0;
		int dailyEmpWage = 0;
		int totalEmpWage = 0;
		int totalWorkingDays = 0;
		int monthFactor = 1;
		int perMonthWage = 0;
		int monthWage = 0;

		const int IS_PART_TIME = 1;
		const int IS_FULL_TIME = 2;

		srand(time(0));

		fstream fileStream;
		fileStream.open( "EmployeeWage.csv", ios::out | ios::app );

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

			totalEmpHrs += empHrs;
			dailyEmpWage = empHrs * empWageBuilder.EMP_RATE_PER_HOUR;
			totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
			dailyWage.push_back(dailyEmpWage);
			fileStream << totalWorkingDays << "," << empWageBuilder.companyName << "," << empWageBuilder.empName << "," << dailyEmpWage << "," << totalEmpWage << endl;

			if(empWageBuilder.NUMBER_OF_WORKING_DAYS * monthFactor == totalWorkingDays)
			{
				perMonthWage = totalEmpWage - monthWage;
				storeMonthWage.push_back(perMonthWage);
				monthWage = totalEmpWage;
				monthFactor++;
			}
		}


		fileStream.close();

		totalEmpWage = totalEmpHrs * empWageBuilder.EMP_RATE_PER_HOUR;
		empWageBuilder.setEmpWage(totalEmpWage);

		empWageBuilder.setMonthWage( storeMonthWage );

		cout << empWageBuilder.empName << " " << "Wage is " << totalEmpWage << endl;

		empWageBuilder.setDailyWage(dailyWage);
		addCompany( empWageBuilder );
	}
};

void searchTotalWage(string companyName, vector<EmpWageBuilder> employeeData)
{
	int companyWage = 0;
	for( EmpWageBuilder ewb : employeeData )
	{
		if( ewb.companyName == companyName )
		{
			companyWage = companyWage + ewb.totalEmpWage;
		}
	}
	 cout << "Total Wage of " << companyName << ":" << companyWage << endl;
}

void displayMonthlyWage(vector<EmpWageBuilder> employeeData, int sortMonth)
{
	cout << "Company Name" << " : " << "Employee Name" << " : " << "Month" << " : " << "Wage" << endl;

	for(int i = 0; i < employeeData.size(); i++)
	{
		cout << employeeData[i].companyName << " : " << employeeData[i].empName << " : " << sortMonth << " : "
			<< employeeData[i].monthWage[sortMonth] << endl;
	}
}

void sortByMonthlyWage( vector<EmpWageBuilder> employeeData, int sortMonth )
{
	cout << "-----------------------sort By Month Wage----------------------"<< endl;
	cout << "Before Sorting: " << endl;
	displayMonthlyWage( employeeData, sortMonth );
	EmpWageBuilder temp;

	for( int i = 0; i < employeeData.size(); i++ )
	{
		int flag = 0;
		for( int j = 0; j < employeeData.size() - 1 - i; j++ )
		{
			if( employeeData[j].monthWage[sortMonth] <
                        	employeeData[j + 1].monthWage[sortMonth] )
			{
				temp = employeeData[j];
				employeeData[j] = employeeData[j + 1];
				employeeData[j + 1] = temp;
				flag = 1;
			}
		}
		if(flag == 0)
		{
			break;
		}
	}

	cout << "After Sorting: " << endl;
        displayMonthlyWage(employeeData, sortMonth);
}

void displayDailyWage(vector<EmpWageBuilder> employeeData)
{
        cout << "Company Name" << " : " << "Employee Name" << " : " << "Daily Wage" << endl;

        for(int i = 0; i < employeeData.size(); i++)
        {
                cout << employeeData[i].companyName << " : " << employeeData[i].empName << " : "
                        << employeeData[i].EMP_RATE_PER_HOUR * 8 << endl;
        }
}


void sortByDailyWage(vector<EmpWageBuilder> employeeData)
{
	cout << "------------------------- Sort By Daily Wage ---------------------------" << endl;
        cout << "Before Sorting: " << endl;
        displayDailyWage(employeeData);
        EmpWageBuilder temp;

        for( int i = 0; i < employeeData.size(); i++ )
        {
                int flag = 0;
                for( int j = 0; j < employeeData.size() - 1 - i ; j++ )
                {
                        if( employeeData[j].EMP_RATE_PER_HOUR <
                                	employeeData[j + 1].EMP_RATE_PER_HOUR )
                        {
                                temp = employeeData[j];
                                employeeData[j] = employeeData[j + 1];
                                employeeData[j + 1] = temp;
                                flag = 1;
			}
                }
                if(flag == 0)
                {
                        break;
                }
        }

        cout << "After Sorting: " << endl;
        displayDailyWage(employeeData);
}

void findEmployee(int wagePerHour, vector<EmpWageBuilder> employeeData)
{
        for(EmpWageBuilder data : employeeData)
        {
                if(data.EMP_RATE_PER_HOUR == wagePerHour)
                {
                        cout << "Name Of Employee is: " << data.empName << ", Whose Wage is: "  << data.EMP_RATE_PER_HOUR << endl;
                }
        }
}

int main()
{

        fstream fileStream;
        fileStream.open( "EmployeeWage.csv", ios::out | ios::trunc );
	fileStream << "Day" << "," << "CompanyName" << "," << "Name" << "," << "DailyEmpWage" << "," << "TotalEmpWage" << endl;

	struct EmpWageBuilder empWageBuilder[5];
	empWageBuilder[0].employeeDetails("Sonali", 12, "BridgeLabz", 20, 10, 60);
	empWageBuilder[1].employeeDetails("NiKita", 12, "Amazon", 25, 25, 70);
	empWageBuilder[2].employeeDetails("NiKi", 12, "Amazon", 15, 25, 70);
	empWageBuilder[3].employeeDetails("Bhakti", 12, "Google",30, 20, 60);
	empWageBuilder[4].employeeDetails("sachin", 12, "Flipkart",50, 20, 60);


	struct EmpWage empWage;
	empWage.employeeWage(empWageBuilder[0]);
	empWage.employeeWage(empWageBuilder[1]);
	empWage.employeeWage(empWageBuilder[2]);
	empWage.employeeWage(empWageBuilder[3]);
	empWage.employeeWage(empWageBuilder[4]);


	searchTotalWage("Amazon", empWage.employeeData);

	cout << "Select month in between 1 to 12 for whichyou want to sort the empWage" << endl;
	int sortMonth;
	cin >> sortMonth;

	sortByMonthlyWage( empWage.employeeData, sortMonth );
	sortByDailyWage( empWage.employeeData);

	cout << "Eployee Whose wage per hour is 50 " << endl;
	findEmployee(50, empWage.employeeData);
	return 0;
}
