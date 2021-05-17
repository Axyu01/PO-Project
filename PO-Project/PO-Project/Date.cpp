#include "Data.h"
#include <iomanip>
#include <ctime>


Date::Date(int yy, int mm, int dd, int hh, int min)
	:year{yy},month{mm},day{dd},hour{hh},minute{min}
{}

Date::Date()					//konstruktor domniemany - pobiera datê z systemu;
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
	std::cout << hour << ":" << std::setw(2) << std::setfill('0') << minute << std::setw(1) << "   " << std::setw(2) << day << "-" << month << "-" << year;
}