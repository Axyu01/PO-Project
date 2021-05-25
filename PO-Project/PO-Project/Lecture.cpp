#include "Data.h"

Lecture::Lecture(std::string nn, bool ev, int wd, Date sd, int lc, int ul, int uc)
	: name{ nn }, isEven{ ev }, weekDay{ wd }, startDate{ sd }, lectureCount{ lc }, userLimit{ ul }, userCount{ uc }
{

}

void Lecture::addParticipant(User* usr)
{
	participants.push_back(usr);
	usr->joinLecture(this);
}


void Lecture::delParticipant(User* usr)
{
	for (int i = 0; i < participants.size(); i++)
	{

		if (participants[i] == usr)
		{
			participants.erase(participants.begin() + i);
			usr->leaveLecture(this);
		}
	}
}


void Lecture::saveToFile(std::string specname, std::string coursename, std::string groupname)
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
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename + "/" +groupname))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename + "/" + groupname);
	}
	if (!is_path_exists("Data/RegisterData/" + specname + "/" + coursename + "/" + groupname+"/"+name))
	{
		make_directory("Data/RegisterData/" + specname + "/" + coursename + "/" + groupname + "/" + name);
	}

	plik.open("Data/RegisterData/" + specname + "/" + coursename + "/" + groupname + "/" + name + "/" + name + "Data.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " << name << "Data.txt istnieje" << std::endl;
		exit(0);
	}
	std::string header = "===DATA_OF_" + name + "_LECTURE===";

		plik << header << std::endl;
		plik << name << std::endl;
		if (isEven) plik << std::to_string(1) << std::endl;
		else plik << std::to_string(0) << std::endl;
		plik << weekDay << std::endl;
		plik << startDate.toString() << std::endl;
		plik << std::to_string(lectureCount) << std::endl;
		plik << std::to_string(userLimit) << std::endl;
		plik << std::to_string(userCount) << std::endl;

		plik << "==PARTICIPANTS_LIST_BY_LOGIN==" << std::endl;


		for (int i = 0; i<participants.size();i++)
		{
			plik << participants[i]->login << std::endl;
		}


	plik.close();

}

void Lecture::readFromFile(std::string specname, std::string coursename, std::string groupname)
{

}


//Komentarz
