#include "Data.h"

Group::Group(std::string nm)
	:name{nm}
{
	
}

void Group::addLecture(std::string nm, bool ev, int wd, Date sd, int lc, int ul)
{
	lectures.push_back(new Lecture(nm, ev, wd, sd, lc, ul));
}

void Group::delLecture()
{

}

void Group::listLecture()
{
	for (auto l : lectures)
	{
		std::cout << l->name << std::endl;
	}
}

void Group::saveToFile()
{

}

void Group::readFromFile()
{

}