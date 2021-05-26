#include "Data.h"

std::vector<Spec*> RegisterData::specs;

RegisterData::RegisterData()
{}


void RegisterData::addSpec(std::string nm)
{
	for (auto s : specs)
	{
		if (nm == s->name)
		{
			return;
		}
	}

	specs.push_back(new Spec(nm));
}

void RegisterData::listSpecs()
{
	for (auto s : specs)
	{
		std::cout << ">>" <<s->name << std::endl;
	}
} 

void RegisterData::delSpec(std::string name)
{
	for (int i = 0; i < specs.size(); i++)
	{
		if (specs[i]->name == name)
		{
			specs[i]->clearCourses();
			specs.erase(specs.begin() + i);
		}
	}
}

void RegisterData::saveToFile()
{

	std::fstream plik;

	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}

	if (!is_path_exists("Data/RegisterData"))
	{
		make_directory("Data/RegisterData");
	}

	plik.open("Data/RegisterData/specsList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy specsList.txt istnieje" << std::endl;
		exit(0);
	}

	for (int i = 0; i < specs.size(); i++)
	{
		plik << specs[i]->name << std::endl;
	}

	plik.close();

	for (auto s : specs)
	{
		s->saveToFile();
	}

}

void RegisterData::readFromFile()
{
	std::fstream plik;

	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}
	if (!is_path_exists("Data/RegisterData"))
	{
		make_directory("Data/RegisterData");
	}

	plik.open("Data/RegisterData/specsList.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy specsList.txt istnieje." << std::endl;
		exit(0);
	}

	std::string line;

	while (std::getline(plik, line))
	{

		addSpec(line);
		
	}

	for (auto s : specs)
	{
		s->readFromFile();
	}


	std::cout << "Pomyslnie wczytano dane o zapisach z pliku." << std::endl;

	plik.close();

}