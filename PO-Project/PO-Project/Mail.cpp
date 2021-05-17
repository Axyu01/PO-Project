#include "Data.h"
#include <iomanip>

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
	std::cout<< "From: " << std::setw(12) << std::internal << std::setfill(' ') << sender << "\nTo: " << std::setw(12) << std::internal << std::setfill(' ') << reciever;
	std::cout << "\n\n\t" << std::setw(12) << text << "\n\n" << "Created and sent: ";
	date.printDate();

}

void Mail::saveToFile(){}

void Mail::readFromFile(){}