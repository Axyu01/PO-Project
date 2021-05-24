#include "Data.h"

Course::Course(std::string nm)
	:name{nm}
{}

void Course::addGroup(std::string nm)
{
	groups.push_back(new Group(nm));
}

void Course::delGroup()
{}

void Course::listGroup()
{
	for (auto g : groups)
	{
		std::cout << g->name << std::endl;
	}
}

void Course::saveToFile(){}

void Course::readFromFile(){}