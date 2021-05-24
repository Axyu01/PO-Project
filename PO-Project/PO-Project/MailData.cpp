#include "Data.h"


std::vector<MailBox*> MailData::mailBoxList;

MailData::MailData()
{

}


void MailData::saveToFile()
{
	std::fstream plik;

	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}

	if (!is_path_exists("Data/MailData"))
	{
		make_directory("Data/MailData");
	}

	plik.open("Data/MailData/mailBoxList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy mailBoxList.txt" << std::endl;
		exit(0);
	}

	for (int i = 0;i<mailBoxList.size();i++ )
	{
		plik << mailBoxList[i]->address << std::endl;
	}

	plik.close();

	for (auto mb : mailBoxList)
	{
		mb->saveToFile();
	}
}

void MailData::readFromFile()
{

}