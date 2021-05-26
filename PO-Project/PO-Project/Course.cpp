#include "Data.h"

Course::Course(std::string nm)
	:name{nm}
{}

void Course::addGroup(std::string nm)
{
	for (auto g : groups)
	{
		if (nm == g->name)
		{
			return;
		}
	}
	groups.push_back(new Group(nm));
}

void Course::delGroup(std::string name)
{
	for (int i = 0; i < groups.size(); i++)
	{
		if (groups[i]->name == name)
		{
			groups[i]->clearLectures();

			groups.erase(groups.begin() + i);
		}
	}
}

void Course::clearGroups()
{
	while (groups.size())
	{
		groups.back()->clearLectures();
		groups.pop_back();
	}
}

void Course::delStudent(User* st)
{
	for (auto g : groups)
	{
		g->delStudent(st);
	}
}

void Course::listGroup()
{
	for (auto g : groups)
	{
		std::cout << g->name << std::endl;
	}
}

void Course::saveToFile(std::string specname)
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
	if (!is_path_exists("Data/RegisterData/" + specname))
	{
		make_directory("Data/RegisterData/" + specname);
	}
	if (!is_path_exists("Data/RegisterData/" + specname +"/" + name))
	{
		make_directory("Data/RegisterData/" + specname + "/" + name);
	}

	plik.open("Data/RegisterData/" + specname + "/" + name + "/" + name + "GroupList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " << name << "GroupList.txt istnieje" << std::endl;
		exit(0);
	}

	for (int i = 0; i < groups.size(); i++)
	{
		plik << groups[i]->name << std::endl;
	}

	plik.close();

	for (auto g : groups)
	{
		g->saveToFile(specname,name);
	}

}

void Course::readFromFile(std::string specname)
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
	if (!is_path_exists("Data/RegisterData/" + specname))
	{
		make_directory("Data/RegisterData/" + specname);
	}
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + name))
	{
		make_directory("Data/RegisterData/" + specname + "/" + name);
	}

	plik.open("Data/RegisterData/" + specname +"/" + name +"/" + name+ "GroupList.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy "+name+"GroupList.txt istnieje." << std::endl;
		exit(0);
	}

	std::string line;

	while (std::getline(plik, line))
	{

		addGroup(line);

	}

	for (auto g : groups)
	{
		g->readFromFile(specname, name);
	}


	std::cout << "Pomyslnie wczytano dane o " + name + " z pliku." << std::endl;

	plik.close();
}