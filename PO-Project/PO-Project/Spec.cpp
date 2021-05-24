#include "Data.h"

Spec::Spec(std::string nm)
	:name{nm}
{

}

void Spec::addCourse(std::string nm)
{
	courses.push_back(new Course(nm));
}

void Spec::delCourse()
{

}

void Spec::listCourse()
{
	for (auto c : courses)
	{
		std::cout << c->name << std::endl;
	}
}

void Spec::saveToFile()
{

}

void Spec::readFromFile()
{

}