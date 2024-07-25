#pragma once
#include <iostream>
#include "BaseEmployee.h"

// add support to keep track of number of CommissionEmployee
class CommissionEmployee : virtual public BaseEmployee
{
public:
	CommissionEmployee(std::string first = {},
		std::string last = {},
		std::string sin = {},
		Date sd = {}, PhoneNumber p = {},
		double rate={ 0.10 }) :
		BaseEmployee(first, last, sin, sd,p),
		grossSale(0.),
		commisionRate(rate)
		
	{
		++sNumCommissionEmployees;
	}

	~CommissionEmployee()
	{
		--sNumCommissionEmployees;
		std::cout << "~CommissionEmployee.\n";
	}

	void setGrossSale(double sale)
	{
		grossSale = sale;
	}
	double getGrossSale() const
	{
		return grossSale;
	}
	void setcommisionRate(double sale)
	{
		commisionRate = sale;
	}
	double getcommisionRate() const
	{
		return commisionRate;
	}	
	
	virtual double earning() const override
	{
		return grossSale * commisionRate;
	}

private:
	double grossSale;
	double commisionRate;
	static int sNumCommissionEmployees;

// add friend operator<< and friend operator>> overrides bellow:

	friend std::ostream& operator<<(std::ostream& os, const CommissionEmployee* cmEmp)
	{
		os << static_cast<const BaseEmployee*>(cmEmp)
			<< "\Gross Sale: " << cmEmp->getGrossSale()
			<< "\nCommission Rate: " << cmEmp->getcommisionRate()
			<< "\nTotal Earning: " << cmEmp->earning();
		return os;


	}

	friend std::istream& operator>>(std::istream& is, CommissionEmployee* cmEmp)
	{
		is >> static_cast<BaseEmployee*>(cmEmp);


		is >> cmEmp->grossSale;
		is >> cmEmp->commisionRate;
		return is;

	}


};
int CommissionEmployee::sNumCommissionEmployees = 0;
