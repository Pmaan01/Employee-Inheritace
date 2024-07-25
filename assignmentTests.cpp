#include <iostream>
#include <vector>
#include "BaseEmployee.h"
#include "CommissionEmployee.h"
#include "SalaryCommisionEmployee.h"
#include "Date.h"
#include <fstream>
#include <sstream>

using namespace std;

int BaseEmployee::sNumEmployees{};

int main(int argc, char** argv)

{

	/* This assignment is to test functionalities supported by the Employee Hierarchy along with operator overloading we introduced in class, in the form of overloading << , >> , ++, and so on.The steps to perform the tests are as following :
	// 1- Complete operator overloading for stream input >> and output << for BaseEmployee, SalaryEmployee, CommisionEmployee, and SalaryCommisionEmployee, and Date and PhoneNumber classes. You are supposed to use the input operator overload to load the data from the data file EmployeeData.txt. Read the data in this file, line by line (after skipping the first few comment lines). For each line that you read, first detect what type of employee it is. Based on the type, construct an employee of that type and add that employee to the vector of employees bellow:
	vector<BaseEmployee*> employees;
	ifstream file("EmployeeData.txt");
	// suppose you have read a line from the file into a string str. Also suppose you have determined that str is for SalaryEmployee. Then constructing the employee and adding it to the vector goes as following:
	string aline; // suppose you have read this line from the input file
	SalaryEmployee* sEmp0{ new SalaryEmployee; };
	istringstream is{ aline };
	is >> sEmp0;
    employees.push_back(&sEmp0);
	// The above is a sample code. Your code goes here bellow:
	// ....*/


	vector<BaseEmployee*> employees;
	vector<SalaryEmployee*> salaryEmployees;
	vector<CommissionEmployee*> commissionEmployees;
	vector<SalaryCommissionEmployee*> salaryCommissionEmployees; 


	if (argc < 2) 
	{
		std::cout << "Usage: assignmentTests.exe filename\n";
		return 1;
	}
	else {
		std::cout << "Processing input file " << argv[1] << endl;

		// Opening input file for processing
		ifstream fs(argv[1]);

		if (!fs.is_open()) {
			std::cout << "Error opening file: " << argv[1] << endl;
			return 1;
		}

		string line;
		getline(fs, line); // skip the header line

		while (getline(fs, line)) {
			if (line[0] == '/' || line.empty())
			{
				continue; // commented lines
			}

			// Read employee name
			stringstream ss(line);
			string firstname, lastname, SIN, phoneNumStr, startDateStr, employeeType;
			ss >> firstname >> lastname >> SIN >> phoneNumStr >> startDateStr >> employeeType;

			std::stringstream phoneStream(phoneNumStr);
			PhoneNumber phoneNumber;
			phoneStream >> phoneNumber;

			std::stringstream dateStream(startDateStr);
			Date startDate;
			dateStream >> startDate;

			if (employeeType == "SalaryEmployee")
			{
				double salary;
				string salaryStr;
				ss >> salaryStr;
				salary = (salaryStr == "DNA") ? 0 : stod(salaryStr);

				std::cout << "Creating SalaryEmployee: " << firstname << " " << lastname << " with salary " << salary << std::endl;

				SalaryEmployee* sEmp = new SalaryEmployee(firstname, lastname, SIN, startDate, phoneNumber, salary);
				employees.push_back(sEmp);
				salaryEmployees.push_back(sEmp);

			}
			else if (employeeType == "CommissionEmployee")
			{

				double salary, commissionRate, grossSale;
				string salaryStr, commissionRateStr, grossSaleStr;
				ss >> salaryStr >> grossSaleStr >> commissionRateStr;
				salary = (salaryStr == "DNA") ? 0 : stod(salaryStr);
				commissionRate = (commissionRateStr == "DNA") ? 0 : stod(commissionRateStr);
				grossSale = (grossSaleStr == "DNA") ? 0 : stod(grossSaleStr);

				std::cout << "Creating CommissionEmployee: " << firstname << " " << lastname << " with commission rate " << commissionRate << " and gross sale " << grossSale << std::endl;

				CommissionEmployee* cEmp = new CommissionEmployee(firstname, lastname, SIN, startDate, phoneNumber, commissionRate);
				cEmp->setGrossSale(grossSale);

				employees.push_back(cEmp);
				commissionEmployees.push_back(cEmp);

			}
			else if (employeeType == "SalaryCommissionEmployee") 
			{
				double salary, commissionRate, grossSale;
				string salaryStr, commissionRateStr, grossSaleStr;
				ss >> salaryStr >> grossSaleStr >> commissionRateStr;
				salary = (salaryStr == "DNA") ? 0 : stod(salaryStr);
				commissionRate = (commissionRateStr == "DNA") ? 0 : stod(commissionRateStr);
				grossSale = (grossSaleStr == "DNA") ? 0 : stod(grossSaleStr);

				std::cout << "Creating SalaryCommissionEmployee: " << firstname << " " << lastname << " with salary " << salary << ", commission rate " << commissionRate << " and gross sale " << grossSale << std::endl;

				SalaryCommissionEmployee* scEmp = new SalaryCommissionEmployee(firstname, lastname, SIN, startDate, phoneNumber, salary, commissionRate);
				scEmp->setGrossSale(grossSale);

				employees.push_back(scEmp);
				salaryCommissionEmployees.push_back(scEmp);
			}
		}
		fs.close();
	}

	// 2- print all the employees out using output operator >> for each employee.
	std::cout << "\nPrinting all the employees:\n\n";
	// YOur code goes here ....

	for (const auto& emp : employees) 
	{
		std::cout << emp << endl;
	}

	// 3-Increase salary for SalaryEmployees and SalaryCommissionEmployees by 10% and increase commission rate for the rest by 3%. Then print each employee 
	//  new earning using earning() method.
	std::cout << "Increase salary for all SalaryEmployees and SalaryCommissionEmployees by 10% " <<
		"  and increase commission rate by 3% for Commision employees and salaryComission employees\n " <<
		"And finally print the updated earnings below : \n\n";
	// Your code goes here: 

	////As instructions were clear so i am increasing salary rate for  SalaryEmployees and SalaryCommissionEmployees by 10% and commision rate for salary commison and commision employes by 3%.
	for (const auto& emp : employees)
	{
		if (SalaryEmployee* se = dynamic_cast<SalaryEmployee*>(emp)) 
		{
			if (dynamic_cast<CommissionEmployee*>(emp) == nullptr)
			{
				se->setSalary(se->getSalary() * 1.10);
			}
			
		}
		if (CommissionEmployee* ce = dynamic_cast<CommissionEmployee*>(emp)) 
		{
			if (dynamic_cast<SalaryEmployee*>(emp) == nullptr)
			{
				ce->setcommisionRate(ce->getcommisionRate() + 0.03);
			}
			
		}
		if (SalaryCommissionEmployee* ce = dynamic_cast<SalaryCommissionEmployee*>(emp))
		{
			ce->setSalary(ce->getSalary() * 1.10);
			ce->setcommisionRate(ce->getcommisionRate() + 0.03);
			
		}

		std::cout << emp->getFullName() << " new earning: " << emp->earning() << endl;
	}

	// 4-Find all employees who have been with the company more than 2 years, and print those employees info using output operator >>
	std::cout << "\nList of all employees who have been with the company for more than 2 years to date:\n\n";
	// Your code goes here: 

	for (const auto& emp : employees) 
	{
		if (emp->getYearsWorked() > 2)
		{
			std::cout << emp << endl;
		}
	}

	// 5- Compute average earning for each type of employee in the company, and print the result
	// Your code goes here:
	double totalSalaryEarnings = 0;
	double totalCommissionEarnings = 0;
	double totalSalaryCommissionEarnings = 0;
	int numSalaryEmployees = 0;
	int numCommissionEmployees = 0;
	int numSalaryCommissionEmployees = 0;

	for (const auto& emp : employees)
	{
		if (SalaryEmployee* se = dynamic_cast<SalaryEmployee*>(emp) )
		{
			if (dynamic_cast<CommissionEmployee*>(emp) == nullptr)
			{
				totalSalaryEarnings += se->earning();
				numSalaryEmployees++;
			}
		}
		if (CommissionEmployee* ce = dynamic_cast<CommissionEmployee*>(emp))
		{
			if (dynamic_cast<SalaryEmployee*>(emp) == nullptr) 
			{
				totalCommissionEarnings += ce->earning();
				numCommissionEmployees++;
			}
		}
		if (SalaryCommissionEmployee* sce = dynamic_cast<SalaryCommissionEmployee*>(emp)) 
		{
			totalSalaryCommissionEarnings += sce->earning();
			numSalaryCommissionEmployees++;
		}
	}

	double avgSalaryEarnings;
	if (numSalaryEmployees > 0) 
	{
		avgSalaryEarnings = totalSalaryEarnings / numSalaryEmployees;
	}
	else {
		avgSalaryEarnings = 0;
	}

	double avgCommissionEarnings;
	if (numCommissionEmployees > 0) 
	{
		avgCommissionEarnings = totalCommissionEarnings / numCommissionEmployees;
	}
	else {
		avgCommissionEarnings = 0;
	}

	double avgSalaryCommissionEarnings;
	if (numSalaryCommissionEmployees > 0) 
	{
		avgSalaryCommissionEarnings = totalSalaryCommissionEarnings / numSalaryCommissionEmployees;
	}
	else 
	{
		avgSalaryCommissionEarnings = 0;
	}

	std::cout << "\nAverage earning for SalaryEmployees: " << avgSalaryEarnings << endl;
	std::cout << "\nAverage earning for CommissionEmployees: " << avgCommissionEarnings << endl;
	std::cout << "\nAverage earning for SalaryCommissionEmployees: " << avgSalaryCommissionEarnings << endl;


	// 6- Print average earning for the whole company. Then Remove the toppest earning employee from the company and then compute  average company earning again and print it.

	// Your code goes here: 

	double totalEarnings = 0;
	for (const auto& emp : employees) 
	{
		totalEarnings += emp->earning();
	}
	size_t totalEmployees = employees.size();

	double avgCompanyEarnings;
	if (totalEmployees > 0) {
		avgCompanyEarnings = totalEarnings / totalEmployees;
	}
	else {
		avgCompanyEarnings = 0;
	}

	std::cout << "\nAverage employee earning for the whole company: " << avgCompanyEarnings << endl;

	std::cout << "\nFind the toppest earner and print his/her info.\n";

	// Your code goes here: 
	BaseEmployee* topEarner = nullptr;
	double maxEarning = 0;
	for (const auto& emp : employees) 
	{
		if (emp->earning() > maxEarning)
		{
			maxEarning = emp->earning();
			topEarner = emp;
		}
	}

	if (topEarner)
	{
		std::cout << "\nTop earner: " << topEarner << "with earnings: " << topEarner->earning() << endl;
	}


	std::cout << "\nRemove the toppest earner and print the earning average for the company before and after the removal: ";
	// Your code goes here:
	if (topEarner) 
	{
		employees.erase(remove(employees.begin(), employees.end(), topEarner), employees.end());
		totalEarnings = 0;
		for (const auto& emp : employees) 
		{
			totalEarnings += emp->earning();
		}
		totalEmployees = employees.size();
		double avgCompanyEarningsAfterRemoval;

		// Check if there are employees left after removing the top earner
		if (totalEmployees > 0) {
			avgCompanyEarningsAfterRemoval = totalEarnings / totalEmployees;
		}
		else {
			avgCompanyEarningsAfterRemoval = 0; // No employees left
		}

		// Print the average earning for the whole company after removing the top earner
		std::cout << "\nAverage employee earning for the whole company after removing top earner: "
			<< avgCompanyEarningsAfterRemoval << std::endl;

	}
	
	std::cout << "\nDelete all dynamic object:";
	// Your code goes here: 
	for (auto& emp : employees)
	{
		delete emp;
	}

	std::cout << "\nEnd of tests. Enter any key to finish.";
	std::cin.ignore();

	return 0;
	
}
