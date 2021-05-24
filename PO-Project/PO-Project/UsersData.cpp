#include "Data.h"
#include <conio.h>


std::vector<std::string> UsersData::creds;

std::vector<User*> UsersData::userList;

User* UsersData::currentUser;


UsersData::UsersData()
{}

void UsersData::addUser(){}

void UsersData::delUser(){}

void UsersData::editUser(){}

bool UsersData::userExists(std::string lgn){
	for (auto u : userList)
	{
		if (u->login == lgn || u->email == lgn) return true;
	}
	return false;
}


User* UsersData::verifyUser(std::string lgn, std::string pwrd)
{
	if(lgn.find("@pwr.edu.pl")!=lgn.npos)
	{
		for (auto u : userList)
		{
			if (lgn == u->email && pwrd == u->password) return u;

		}
	}
	else
	{
		for (auto u : userList)
		{
			if (lgn == u->login && pwrd == u->password) return u;
		}
	}
	return nullptr;
}


void UsersData::registerUser()
{
	std::string login, password, email;

	system("cls");
	std::cout << "==REJESTRACJA==\n";
	std::cout << "\nLogin:";	std::cin >> login;
	if (!userExists(login)) 
	{
		std::cout << "\nPassword:"; std::cin >> password;


		email = login + "@pwr.edu.pl";

		userList.push_back(new User(email, login, password, "student"));
		saveToFile();
	}
	else
	{
		std::cout << "\n\nUzytkownik o takim loginie juz istnieje.";
		_getch();
	}

}

User* UsersData::loginUser()
{
	std::string login, password;

	system("cls");
	std::cout << "==LOGOWANIE==\n";
	std::cout << "\nLogin/email:";	std::cin >> login;
	if (userExists(login))
	{
		std::cout << "\nPassword:"; std::cin >> password;

		if (User* temp = verifyUser(login, password))
		{
			std::cout << "\n\nSkutecznie zalogowano do systemu.";
			_getch();
			return temp;
		}
		else
			std::cout << "\n\nPodano nieprawidlowe haslo." << std::endl;
		return nullptr;
	}
	else
	{
		std::cout << "\n\nUzytkownik o takim loginie nie istnieje.";
	}
	_getch();
	return nullptr;
}

void UsersData::saveToFile()
{
	std::fstream plik;

	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}

	if (!is_path_exists("Data/Users"))
	{
		make_directory("Data/Users");
	}
	
	
		plik.open("Data/Users/usersData.txt", std::ios::out);
		if (plik.good() == false)
		{
			std::cout << "Wystapil blad z odczyywaniem pliku. Sprawdz czy usersData.txt istnieje" << std::endl;
			exit(0);
		}


		std::string header = "-----USERS DATA----";
		plik << header << std::endl;

		for (auto u : userList)
		{
			plik << "==========" << std::endl;

			plik << u->email << std::endl;
			plik << u->login << std::endl;
			plik << u->password << std::endl;

			plik << u->userType << std::endl;
		}
		plik.close();
	

	plik.close();

	std::cout << "\nPomyslnie zapisano liste userow do pliku usersData.txt" << std::endl;

}

void UsersData::readFromFile()
{
	std::fstream plik;

	plik.open("Data/Users/usersData.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy usersData.txt istnieje." << std::endl;
		exit(0);
	}

	std::string line;
	int readsLeft = 5;

	std::string em;
	std::string log;
	std::string pwrd;
	std::string type;

	while (std::getline(plik, line))
	{
		if (line == "==========") readsLeft = 4;

		switch (readsLeft)
		{
		case 4:
			readsLeft--;
			break;
		case 3:
			em = line;
			readsLeft--;
			break;
		case 2:

			//else winner = else;											<-- pozdrawiam Arkadiusza Pytke <3

			log = line;
			readsLeft--;
			break;
		case 1:
			pwrd = line;
			readsLeft--;
			break;
		case 0:
			type = line;


			userList.push_back(new User(em, log, pwrd, type));

			readsLeft = 4;
			type.clear();
			em.clear();
			log.clear();
			pwrd.clear();
			break;
		}
	}
}