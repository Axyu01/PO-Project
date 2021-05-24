#include "Data.h"

std::vector<Spec*> RegisterData::specs;

RegisterData::RegisterData()
{}


void RegisterData::addSpec(std::string nm)
{
	specs.push_back(new Spec(nm));
}

void RegisterData::listSpecs()
{
	for (auto s : specs)
	{
		std::cout << ">>" <<s->name << std::endl;
	}
} 

void RegisterData::saveToFile()
{}

void RegisterData::readFromFile()
{}