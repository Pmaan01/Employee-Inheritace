#pragma once

#include <string>
#include <sstream>
#include "SalaryEmployee.h"
#include "CommissionEmployee.h"

class SalaryCommissionEmployee : public SalaryEmployee, public CommissionEmployee
{
public:
	SalaryCommissionEmployee(std::string first = {},
		std::string last = {},
		std::string sin = {}, Date sd = {}, PhoneNumber p = {}, double pay = { 35000. }, double rate = { 0.10 }) :
		BaseEmployee(first, last, sin, sd,p),
		SalaryEmployee(first, last, sin, sd, p, pay),
		CommissionEmployee(first, last, sin, sd ,p, rate)

	{
		setSalary(pay);
		setcommisionRate(rate);
		++sNumSalaryCommissionEmployees;

	}


	~SalaryCommissionEmployee()
	{
		--sNumSalaryCommissionEmployees;
		std::cout << "salarycommission employee deleted";
	}

	virtual double earning() const override
	{
		return SalaryEmployee::earning() + CommissionEmployee::earning();
	}

	virtual std::string to_string() const override
	{
		return "SalaryCommisionEmployee: " + BaseEmployee::to_string() + ", earning=" + std::to_string(earning());
	}

private:

	static int sNumSalaryCommissionEmployees;
	// add static variable to keep track of number of SalComm Employees.

protected:
	friend std::ostream& operator<<(std::ostream& os, const SalaryCommissionEmployee* salComm)
	{
		os << static_cast<const BaseEmployee*>(salComm)
			<< "\nSalary: " << salComm->getSalary()
			<< "\nCommission Rate: " << salComm->getcommisionRate()
			<< "\nTotal Earning: " << salComm->earning();
		return os;
	}

	friend std::istream& operator>>(std::istream& is, SalaryCommissionEmployee* salComm) 
	{
		is >> static_cast<BaseEmployee*>(salComm);
		double salary;
		double commissionRate;

		is >> salary;

		is >> commissionRate;
		salComm->setSalary(salary);
		salComm->setcommisionRate(commissionRate);
		return is;
	}


};
int SalaryCommissionEmployee::sNumSalaryCommissionEmployees = 0;