#include "Data.h"
#include <conio.h>

std::vector<Chat*> ChatData::chatList;

ChatData::ChatData()
{}

Chat* ChatData::chatExists(std::string nm)
{
	for (auto c : chatList)
	{
		if (c->chatName == nm)
		{
			return c;
		}
	}
	return nullptr;
}

void ChatData::saveToFile()
{
	for (auto c : chatList)
	{
		std::fstream plik;

		if (!is_path_exists("Data"))
		{
			make_directory("Data");
		}
		if (!is_path_exists("Data/ChatData"))
		{
			make_directory("Data/ChatData");
		}

		plik.open("Data/ChatData/" + c->chatName + "_ChatArchive.txt", std::ios::out);
		if (plik.good() == false)
		{
			std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " + c->chatName + "_ChatArchive.txt istnieje." << std::endl;
			exit(0);
		}

		std::string header = "===" + c->chatName+ " CHAT_ARCHIVE===";

		plik << header << std::endl;

		for (auto m : c->chatArchive)
		{
			plik << m << std::endl;
		}


		std::cout << "Pomyslnie zapisano archiwum z chatu" + c->chatName + " do pliku." << std::endl;

		plik.close();
	}
}

void ChatData::readFromFile()
{
	for (auto c : chatList)
	{
		std::fstream plik;

		if (!is_path_exists("Data"))
		{
			make_directory("Data");
		}
		if (!is_path_exists("Data/ChatData"))
		{
			make_directory("Data/ChatData");
		}

		plik.open("Data/ChatData/" + c->chatName + "_ChatArchive.txt", std::ios::in);
		if (plik.good() == false)
		{
			std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " + c->chatName + "_ChatArchive.txt istnieje." << std::endl;
			_getch();
		}

		std::string line;
		int which_line = 1;

		std::string prefix;

		while (std::getline(plik, line))
		{
			switch (which_line++)
			{
			case 1:
				break;
			default:
				if (prefix.size())
				{
					c->chatArchive.push_back(prefix + "\n" + line);
					prefix.clear();
				}
				else 
					prefix = line;
				break;
			}
		}


		std::cout << "Pomyslnie wczytano archiwum chatu" + c->chatName + " z pliku." << std::endl;

		plik.close();
	}



}