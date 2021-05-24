#include "Data.h"
#include <iomanip>
#include <conio.h>

Mail::Mail(std::string sen, std::string rec, std::string txt, Date dt) 
	: sender{sen}, reciever{rec}, text{txt}, date{dt}
{

}

Mail::Mail(std::string sen, std::string rec, std::string txt)				//konstruktor pobieraj¹cy datê systemu
	: sender{ sen }, reciever{ rec }, text{ txt }
{
	date = Date();
}

void Mail::viewContents()
{
	system("cls");
	std::cout<< "From: " << std::setw(12) << std::internal << std::setfill(' ') << sender << "\nTo: " << std::setw(12) << std::internal << std::setfill(' ') << reciever;
	std::cout << "\n\n\t" << std::setw(12) << text << "\n\n" << "Created and sent: ";
	date.printDate();

	_getch();
}

void Mail::showHeader() {
	std::cout << "From: " << sender << std::endl;
	std::cout << text.substr(0, 8) << "..." << std::endl;
	for (int i = 0; i < 20; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;

}

void Mail::saveToFile(){}

void Mail::readFromFile(){}