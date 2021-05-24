#include "Data.h"
#include <cstdlib>
#include <direct.h>
#include <sys/stat.h>
#include <fstream>


MailBox::MailBox(std::string adr)
	: address{adr}
{
	if (file_exists(adr, "Data/MailData/"))
	{
		readFromFile();
	}
	else saveToFile();


	MailData::mailBoxList.push_back(this);
}

void MailBox::sendEmail(MailBox* rec) {
	std::string txt = "Hello world!";

	Mail* temp = new Mail(address,rec->address, txt);
	
	rec->mail.push_back(temp);
}

void MailBox::sendEmail(MailBox* rec, std::string txt) {

	Mail* temp = new Mail(address, rec->address, txt);

	rec->mail.insert(mail.begin(), temp);
}

void MailBox::sendEmail(std::string rec, std::string txt) {

	for (auto mb : MailData::mailBoxList)
	{
		if (mb->address == rec)
		{
			Mail* temp = new Mail(address, mb->address, txt);

			mb->mail.insert(mb->mail.begin(), temp);
		}
	}

}

void MailBox::deleteEmail(int which) 
{
	listMail();
		if(which <= mail.size() && which > 0)
		mail.erase(mail.begin() + which - 1);
}

void MailBox::listMail() 
{
	system("cls");
	std::cout << "Witamy w skrzynce pocztowej " << address << "\n\n";

	for (auto m : mail)
	{
		m->showHeader();
	}

}

void MailBox::readMail(int which) 
{
	listMail();

	if (mail.size()) {
		if (which > mail.size()) which = mail.size();
		else if (which < 0) which = 1;

		mail[which - 1]->viewContents();
	}
}

void MailBox::saveToFile() 
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

	plik.open("Data/MailData/" + address + ".txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytem pliku. Sprawdz czy istnieje\n";
	}

	std::string header = "-----DATA_OF_" + address + ".txt" + "----";
	plik << header << std::endl;
	for (int i = 0; i < mail.size(); i++)											//zapis poszczegolnych skladowych do pliku txt
	{
		std::string sdr = "sdr=" + mail[i]->sender;
		std::string tx = mail[i]->text;
		std::string date = "date=" + mail[i]->date.toString();

		plik << "==========" << std::endl;

		plik << sdr << std::endl;
		plik << tx << std::endl;
		plik << date << std::endl;

	}
	plik.close();

	std::cout << "\nPomyslnie zapisano skrzynke do pliku " + address + ".txt" << std::endl;
}

void MailBox::readFromFile() 
{
	std::fstream plik;

	plik.open("Data/MailData/" + address + ".txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " + address + ".txt istnieje." << std::endl;
		exit(0);
	}

	if (mail.size()) {
		for (auto m : mail)					//czyszczenie wektora i zwalnianie pamiêci
		{
			delete m;
		}
		mail.clear();
	}

	std::string line;
	int which = 1;
	int readsLeft = 4;

	std::string sdr;
	std::string tx;
	int ltrcnt;
	Date dt;

	while (std::getline(plik, line))
	{

		if (line == "==========") readsLeft =3 ;

		switch (readsLeft)
		{
		case 3: 
			readsLeft--;
			break;
		case 2:
			sdr = line.substr(line.rfind('=') + 1);
			readsLeft--;
			break;
		case 1:
			tx += line;
			if (line.substr(0, 5) == "date=") {
				tx.erase(tx.length() - 21);

				dt.changeDate(stoi(line.substr(8, 2)),stoi(line.substr(5,2)),stoi(line.substr(11, 2)),stoi(line.substr(14, 2)), stoi(line.substr(17, 4)));
				mail.push_back(new Mail{ sdr, address, tx, dt });
				sdr.clear();
				tx.clear();

				readsLeft = 4;
			}
			break;
		default:
			break;
		}
	}


	std::cout << "Pomyslnie wczytano skrzynke z pliku." << std::endl;

	plik.close();

}

