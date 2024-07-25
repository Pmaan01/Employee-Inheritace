#pragma once
// a class to represent date
#include <array>

class Date
{
public:
	Date(unsigned int m = 1, unsigned d = 1, unsigned y = 1900);// default constructor

	void setDate(unsigned, unsigned , unsigned );// set month, day, year
	

	Date& operator++();  // prefix increment operator ++i
	Date operator++(int);  // postfix increment operator  i++
	Date& operator+=(unsigned);

	static bool leapYear(unsigned y); // is year y a leap year or not
	bool endOfMonth(unsigned d) const; // is day d end of the month
	int yearsEmployed() const;


	// add operator<< and operator>> as friend here, similar to how was done for PhoneNumber class
	virtual std::string to_string() const
	{
		return std::to_string(month) + "-" + std::to_string(day) + "-" + std::to_string(year);
	}

	operator std::string() const { return to_string(); }

	friend std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		// to be done by students. Must use to_string() method above.
		os << d.to_string();
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Date& d)
	{

		char formatLine;
		is >> d.month >> formatLine >> d.day >> formatLine >> d.year;
		return is;
	}

private:
	unsigned int month, day, year;
	static const std::array<unsigned int, 13> days;
	void helpIncrement(); // utility method used internally for incrementing date
	
	
};
