#include "Date.h"
#include<iostream>
#include<iomanip>

bool Date::isLeapYear() const
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

Date::Date(size_t day, size_t month, size_t year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}
size_t Date::getDay() const
{
	return day;
}
size_t Date::getMonth() const
{
	return month;
}
size_t Date::getYear() const
{
	return year;
}

void Date::setYear(size_t year)
{
	this->year = year;

	if (isLeapYear())
		MAX_DAYS[1] = 29;
	else
		MAX_DAYS[1] = 28;
}

void Date::setMonth(size_t month)
{
	if (month > 12)
		month = 1;
	this->month = month;

	if (day > MAX_DAYS[month - 1])
		day = MAX_DAYS[month - 1];
}

void Date::setDay(size_t day)
{
	if (day > MAX_DAYS[month - 1])
		day = 1;
	this->day = day;
}

void Date::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << day << "." << std::setw(2) << std::setfill('0') << month << ".";
	std::cout << std::setw(4) << std::setfill('0') << year;
}

void Date::goToNextDay()
{
	setDay(day + 1);
	if (day == 1)
	{
		setMonth(month + 1);
		if (month == 1)
			setYear(year + 1);
	}
}

bool Date::areEqual(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

size_t Date::getDayOfWeek() const
{
	Date d(1, 1, 1);
	int day = 5;

	while (!areEqual(d))
	{
		d.goToNextDay();
		(day += 1) % 7;
	}

	dayOfWeek = day + 1;
}
