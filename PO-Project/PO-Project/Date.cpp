#include "Data.h"
#include <iomanip>
#include <ctime>


Date::Date(int yy, int mm, int dd, int hh, int min)
	:year{yy},month{mm},day{dd},hour{hh},minute{min}
{
	roundDate();
}

Date::Date()					// <-- konstruktor domniemany - pobiera datê z systemu;
{
	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);


	minute = TM.tm_min;
	hour = TM.tm_hour;
	day = TM.tm_mday;
	month = TM.tm_mon + 1;
	year = TM.tm_year + 1900;
}

void Date::changeDate(int min, int hh, int dd, int mm, int yy)
{
	minute = min;
	hour = hh;
	day = dd;
	month = mm;
	year = yy;
	roundDate();
}

void Date::changeDate(int min, int hh, int dd, int mm)		//prze³adowanie dla zmiany tylko godziny i daty
{
	minute = min;
	hour = hh;
	day = dd;
	month = mm;
	roundDate();
}

void Date::changeDate(int min, int hh)			//prze³adowanie dla zmiany samej godziny
{
	minute = min;
	hour = hh;
	roundDate();
}

void Date::offsetDaysBy(int dd)
{
	day += dd;
	roundDate();
}

void Date::printFullDate() 
{
	std::cout << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute << std::setw(1) << "   " << std::setw(2) << day << "-" << std::setw(2) << std::setfill('0') << month << "-" << year;
}

std::string Date::toStringDate() 
{
	std::string mth;
	if (month < 10) mth = "0" + std::to_string(month);
	else mth = std::to_string(month);

	std::string dd;
	if (day < 10) dd = "0" + std::to_string(day);
	else dd = std::to_string(day);

	return dd + "-" + mth + "-" + std::to_string(year);
}

std::string Date::toStringTime()
{
	std::string hrs;
	if (hour < 10)  hrs = "0" + std::to_string(hour);
	else hrs = std::to_string(hour);

	std::string mins;
	if (minute < 10)  mins = "0" + std::to_string(minute);
	else mins = std::to_string(minute);

	return hrs + ":" + mins;
}

void Date::roundDate()
{
	bool going = true;
	while (going)
	{
		if (month < 1)
		{
			year--;
			month += 12;
			continue;
		}

		if (month > 12)
		{
			year++;
			month -= 12;
			continue;
		}

		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 1 || month == 12)
		{
			if (day > 31)
			{
				month++;
				day -= 31;
				continue;
			}

			if (day < 1)
			{
				month--;

				if (month == 2)
				{
					if (!isLeapYear())
					{
						day += 28;
					}
					else 
						day += 29;
				}
				else if (month == 7)
				{
					day += 31;
					continue;
				}
				else
					day += 30;
				continue;
			}
		}

		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30)
			{
				month++;
				day -= 30;
				continue;
			}

			if (day < 1)
			{
				month--;
				if(month == 1 || month == 3 || month == 5 || month == 8 || month == 10 || month == 1 || month == 12)
				day += 31;
				continue;
			}
		}

		if (month == 2)
		{
			if (!isLeapYear() && day > 28)
			{
				month++;
				day -= 28;
				continue;
			}
			else if (isLeapYear() && day > 29)
			{
				month++;
				day -= 29;
				continue;
			}

		}

		if (hour >= 24)
		{
			day++;
			hour -= 24;
			continue;
		}

		if (minute >= 60)
		{
			hour++;
			minute -= 60;
			continue;
		}

		going = false;
	}
}

bool Date::isLeapYear()
{
	if (!(year % 4))
	{
		if (!(year % 100))
		{
			if (!(year % 400))
				return true;
		}
		else
			return true;

	}
	return false;
}

bool Date::isSameDay(const Date& d1, const Date& d2)
{
	if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day) 
		return true;
	return false;
}

std::string Date::toString() 
{
	std::string hrs;
	if (hour < 10)  hrs = "0" + std::to_string(hour);
	else hrs = std::to_string(hour);

	std::string mins;
	if (minute < 10)  mins = "0" + std::to_string(minute);
	else mins = std::to_string(minute);

	std::string mth;
	if (month < 10) mth = "0" + std::to_string(month);
	else mth = std::to_string(month);

	std::string dd;
	if (day < 10) dd = "0" + std::to_string(day);
	else dd = std::to_string(day);

	return hrs + ":" + mins + " " + dd + "-" + mth + "-" + std::to_string(year);
}