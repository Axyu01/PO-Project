#include "Data.h"
#include <iomanip>
#include <ctime>


Date::Date(int yy, int mm, int dd, int hh, int min)
	:year{yy},month{mm},day{dd},hour{hh},minute{min}
{}

Date::Date()					// <-- konstruktor domniemany - pobiera datę z systemu;
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

void Date::changeDate(int min, int hh, int dd, int mm)		//przeładowanie dla zmiany tylko godziny i daty
{
	minute = min;
	hour = hh;
	day = dd;
	month = mm;
	roundDate();
}

void Date::changeDate(int min, int hh)			//przeładowanie dla zmiany samej godziny
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

void Date::printDate() {
	std::cout << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute << std::setw(1) << "   " << std::setw(2) << day << "-" << std::setw(2) << std::setfill('0') << month << "-" << year;
}

int Date::returnDayOfWeek()
{
	int dd = day;
	int mm = month;
	int yy = year;

	yy -= mm < 3; 
	return(yy + yy / 4 - yy / 100 + yy / 400 + "-bed=pen+mad."[mm] + dd) % 7;

	//0 = niedziela, 1 = poniedzialek, 2 = wtorek, 3 = sroda, 4 = czwartek, 5 = piatek, 6 = sobota

}

int Date::returnDaysInMonth()
{
	switch (month)
	{
	case 2:
			if (isLeapYear())
				return 29;
			return 28;
	case 4: return 30;
	case 6: return 30;
	case 9: return 30;
	case 11: return 30;
	default: return 31;
	}
}

int Date::returnFirstDay()
{
	Date temp = *this;

	temp.day = 1;
	return temp.returnDayOfWeek();
}

bool Date::isSameDay(const Date& first, const Date& second)
{
	return (first.day == second.day && first.month == second.month && first.year == second.year);
}

void Date::roundDate()
{
	bool going = true;
	while (going)
	{
		if (month > 12)
		{
			year++;
			month -= 12;
		}

		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 1 || month == 12)
		{
			if (day > 31)
			{
				month++;
				day -= 31;
				continue;
			}
		}

		if (month == 4 || month == 6 || month == 9 || month == 7 || month == 11)
		{
			if (day > 30)
			{
				month++;
				day -= 30;
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