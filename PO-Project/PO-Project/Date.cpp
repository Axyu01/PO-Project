#include "Data.h"
#include <iomanip>
#include <ctime>


Date::Date(int yy, int mm, int dd, int hh, int min)
	:year{yy},month{mm},day{dd},hour{hh},minute{min}
{}

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
}

void Date::changeDate(int min, int hh, int dd, int mm)		//prze³adowanie dla zmiany tylko godziny i daty
{
	minute = min;
	hour = hh;
	day = dd;
	month = mm;
}

void Date::changeDate(int min, int hh)			//prze³adowanie dla zmiany samej godziny
{
	minute = min;
	hour = hh;
}

void Date::printDate() {
	std::cout << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute << std::setw(1) << "   " << std::setw(2) << day << "-" << std::setw(2) << std::setfill('0') << month << "-" << year;
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