#include "Data.h"
#include <iomanip>

Chat::Chat(std::string name)
	: chatName{name}
{
	ChatData::chatList.push_back(this);
}

void Chat::sendMessage(User* us)
{
	std::string txt;

	std::getline(std::cin, txt);

	Date time;
	txt.insert(0, "<" + us->login + "> " + time.toString() + "\n");

	chatArchive.push_back(txt);
}

void Chat::viewChat()
{
	system("cls");
	std::cout << std::internal << std::setw(15) << "><><" << chatName << "><><\n" << std::endl;

	for (auto m : chatArchive)
	{
		std::cout << m << std::endl << std::endl;
	}

}



void Chat::saveToFile() {}

void Chat::readFromFile(){}