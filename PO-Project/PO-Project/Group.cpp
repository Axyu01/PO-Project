#include "Data.h"

Group::Group(std::string nm)
	:name{nm}
{
	
}

void Group::addLecture(std::string nm, bool ev, int wd, Date sd, int lc, int ul, int uc)
{
	lectures.push_back(new Lecture(nm, ev, wd, sd, lc, ul, uc));
}

void Group::delLecture()
{

}

void Group::delStudent(User* st)
{
	for (auto l : lectures)
	{
		l->delParticipant(st);
	}
}

void Group::listLecture()
{
	for (auto l : lectures)
	{
		std::cout << l->name << std::endl;
	}
}

bool Group::userRegisteredInGroup(User*us)
{
	for (auto l : lectures)
	{
		if (us->isRegistered(l))
			return true;
	}
	return false;
}

void Group::saveToFile(std::string specname, std::string coursename)
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
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename);
	}
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename + "/" + name))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename + "/" + name);
	}

	plik.open("Data/RegisterData/" + specname + "/" + coursename + "/" + name + "/" + name + "LectureList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " << name << "GroupList.txt istnieje" << std::endl;
		exit(0);
	}

	for (int i = 0; i < lectures.size(); i++)
	{
		plik << lectures[i]->name << std::endl;
	}

	plik.close();

	for (auto l : lectures)
	{
		l->saveToFile(specname,coursename,name);
	}

}

void Group::readFromFile(std::string specname, std::string coursename)
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
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename);
	}
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename + "/" + name))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename + "/" + name);
	}

	plik.open("Data/RegisterData/" + specname + "/" + coursename + "/" + name + "/"+ name+"LectureList.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " + name + "LectureList.txt istnieje." << std::endl;
		exit(0);
	}

	std::string line;

	int which_lecture = -1;

	while (std::getline(plik, line))
	{
		std::fstream data;

		if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename + "/" + name + "/" + line))
		{
			make_directory("Data/RegisterData/" + specname + "/" + coursename + "/" + name + "/" + line);
		}

		data.open("Data/RegisterData/" + specname + "/" + coursename + "/" + name + "/" +line +"/"+ line + "Data.txt", std::ios::in);
		if (plik.good() == false)
		{
			std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " + line + "Data.txt istnieje." << std::endl;
			exit(0);
		}

		std::string verse;
		int line_nr = 1;

		std::string nm, ev, wd,sd,lc,ul,uc;
		Date temp;

		

		while (std::getline(data, verse))
		{
			switch (line_nr)
			{
			case 1: 
				break;
			case 2:
				nm = verse;
				break;
			case 3:
				ev = verse;
				break;
			case 4:
				wd = verse;
				break;
			case 5:
				sd = verse;
				temp.changeDate(stoi(verse.substr(3, 2)), stoi(verse.substr(0, 2)), stoi(verse.substr(6, 2)), stoi(verse.substr(9, 2)), stoi(verse.substr(12, 4)));
				break;
			case 6:
				lc = verse;
				break;
			case 7:
				ul = verse;
				break;
			case 8:
				uc = verse;

				addLecture(nm, std::stoi(ev), std::stoi(wd), temp, std::stoi(lc), std::stoi(ul), std::stoi(uc));
				which_lecture++;
				break;
			case 9:
				break;
			default:
				lectures[which_lecture]->addParticipant(UsersData::findUser(verse));
			}

			line_nr++;
		}
		std::cout << "Pomyslnie wczytano zajecia z pliku " + line + ".txt" << std::endl;
		data.close();
	}
	std::cout << "Pomyslnie wczytano grupe z pliku " + name + ".txt" << std::endl;

	plik.close();
}