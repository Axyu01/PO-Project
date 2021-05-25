#include "Menu.h"
#include <conio.h>

#define KEY_UP 72

#define KEY_DOWN 80

Menu::Menu()
	:currentUser{nullptr}
{}

void Menu::loginScreen(UsersData* ud, bool& going)
{
	while (currentUser==nullptr && going == true)
	{
		system("cls");
		std::cout << "===LOGIN===\n\n";

		std::cout << "1) Sign in.\n";
		std::cout << "2) Sign up.\n";
		std::cout << "\n0) Exit.\n";

		int op = _getch();

		switch (op)
		{
		case '1':
			currentUser = ud->loginUser();
			break;

		case '2':
			ud->registerUser();
			break;
		case '0':
			going = false;
			break;
		default:
			break;
		}
	}
}

void Menu::logOut()
{
	currentUser = nullptr;
}

bool Menu::isLoggedIn()
{
	if (currentUser == nullptr) return false;
	else return true;
}

void Menu::drawMenu(int it)
{
	std::vector<std::string> optsTxt = { "Poczta", "Zapisy", "Wypisz z kierunku", "Wyloguj" };

	system("cls");
	std::cout << "===WITAMY " << currentUser->login << "===\n\n";

	for (auto o : optsTxt)
	{
		if (o == optsTxt.at(optsTxt.size() - 1) && o == optsTxt.at(it))
			std::cout << std::endl << ">>" << o << std::endl;
		else if (o == optsTxt.at(it))
			std::cout << ">>" << o << std::endl;
		else if (o==optsTxt.at(optsTxt.size()-1))
			std::cout<< std::endl << o << std::endl;
		else
			std::cout << o << std::endl;
	}
}


void Menu::selectMail()
{
	bool leave = false;


	while (leave != true)
	{
		bool inmail = true;
		std::string rec, content;



		system("cls");
		std::cout << "===SKRZYNKA POCZTOWA " << currentUser->login << "===\n\n";

		std::cout << "1) View your mail.\n";
		std::cout << "2) Send new mail.\n";

		std::cout << "\n0) Go back.\n";

		int op = _getch();
		switch (op)
		{
		case '1':

			while (inmail)
			{
				currentUser->mbox.listMail();
				std::cout << "\n0) Go back.";
				int it = _getch() - 48;
				switch (it)
				{
				case 0:
					inmail = false;
					break;
				default:
					currentUser->mbox.readMail(it);
					break;
				}
			}
			break;

		case '2':
			system("cls");
			std::cout << "Input reciever address:"; std::cin >> rec;
			system("cls");

			std::cout << "To: " << rec << std::endl;

			std::cin.ignore();
			std::getline(std::cin, content);
			currentUser->mbox.sendEmail(rec, content);
			break;
		case'0':
			leave = true;
			break;
		default:
			break;
		}
	}
}

void Menu::selectRegister()
{
	if (!currentUser->isRegistered())
	{
		bool going = true;
		int it = 0;
		while (going)
		{
			system("cls");
			std::cout << "==LISTA DOSTEPNYCH KIERUNKOW==" << std::endl;

			for (auto s : RegisterData::specs)
			{
				if (s == RegisterData::specs.at(it))
					std::cout << ">>";
				std::cout << s->name << std::endl;
			}

			std::cout << "\n0) Go back.";

			char op = _getch();
			switch (op)
			{
			case KEY_DOWN:
				if (it < RegisterData::specs.size()-1)
				{
					it++;
				}
				break;
			case KEY_UP:
				if (it > 0)
				{
					it--;
				}
				break;
			case 13:
				currentUser->joinSpec(RegisterData::specs[it]);
				std::cout << "\n\nPomyslnie zapisales sie na kierunek " << currentUser->spec->name; 
				_getch();
				
				going = false;
				break;
			case '0':
				going = false;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		bool going = true;
		int it = 0;
		while (going)
		{
			system("cls");
			std::cout << "==LISTA DOSTEPNYCH KURSOW DLA "+ currentUser->spec->name + "==" << std::endl;

			for (auto s : currentUser->spec->courses)
			{
				if (s == currentUser->spec->courses.at(it))
					std::cout << ">>";
				std::cout << s->name << std::endl;
			}

			std::cout << "\n0) Go back.";

			char op = _getch();
			switch (op)
			{
			case KEY_DOWN:
				if (it < currentUser->spec->courses.size() - 1)
				{
					it++;
				}
				break;
			case KEY_UP:
				if (it > 0)
				{
					it--;
				}
				break;
			case 13:
				if (currentUser->spec->courses.size())
				{	
					selectGroup(currentUser->spec->courses[it]);
				}
				break;
			case '0':
				going = false;
				break;
			default:
				break;
			}
		}
	}
}

void Menu::selectGroup(Course* course)
{

		bool going = true;
		int it = 0;
		while (going)
		{
			system("cls");
			std::cout << "==LISTA DOSTEPNYCH GRUP DLA KURSU \"" + course->name + "\"==" << std::endl;

			for (auto g : course->groups)
			{
				if (g == course->groups.at(it))
					std::cout << ">>";
				std::cout << g->name << std::endl;
			}

			std::cout << "\n0) Go back.";

			char op = _getch();
			switch (op)
			{
			case KEY_DOWN:
				if (it < course->groups.size() - 1)
				{
					it++;
				}
				break;
			case KEY_UP:
				if (it > 0)
				{
					it--;
				}
				break;
			case 13:
				if (course->groups.size())
				{
					selectLecture(course->groups[it]);
				}
				break;
			case '0':
				going = false;
				break;
			default:
				break;
			}
		}
}

void Menu::selectLecture(Group* group)
{
	bool going = true;
	int it = 0;
	while (going)
	{
		system("cls");
		std::cout << "==LISTA DOSTEPNYCH ZAJEC DLA GRUPY \"" + group->name + "\"==" << std::endl;

		for (auto l : group->lectures)
		{
			if (l == group->lectures.at(it))
				std::cout << ">>";
			std::cout << l->name;
			if (currentUser->isRegistered(l))
				std::cout << " <- ZAPISANY";
			std::cout << std::endl;
		}

		std::cout << "\n0) Go back.";

		char op = _getch();
		switch (op)
		{
		case KEY_DOWN:
			if (it < group->lectures.size() - 1)
			{
				it++;
			}
			break;
		case KEY_UP:
			if (it > 0)
			{
				it--;
			}
			break;
		case 13:

			if (group->lectures.size())	//dodaje u¿ytkownika do zajêæ, je¿eli jest niezapisany, oraz niezapisany na ¿adne inne zajêcia w grupie
			{
				if (!(currentUser->isRegistered(group->lectures[it])))
				{
					if (group->userRegisteredInGroup(currentUser))
					{
						std::cout << "\n\nJestes juz zapisany na zajecia z tej grupy. Wypisz sie aby wybrac inne.\n";
						_getch();
					}
					else if(!(currentUser->isRegistered(group->lectures[it])))
						group->lectures[it]->addParticipant(currentUser);
				}
				else
					group->lectures[it]->delParticipant(currentUser);
			}

			break;
		case '0':
			going = false;
			break;
		default:
			break;
		}
	}
}

void Menu::selectionScreen()
{
	int it = 0;
	while (isLoggedIn())
	{
		drawMenu(it);
	
		char op = _getch();

		switch (op)
		{
		case KEY_DOWN:

			if (it < 3)
			{
				it++;
			}
			break;

		case KEY_UP:
			if (it > 0)
			{
				it--;
			}
			break;

		case 13:
			select(it);
			break;
		default:
			break;
		}
	}
}
void Menu::leaveSpec()
{
	if (currentUser->isRegistered()) {
		bool going = true;
		system("cls");
		std::cout << "Czy na pewno wypisac z " << currentUser->spec->name << "?\n(Y/N)";
		while (going)
		{
			char op = _getch();
			switch (op)
			{
			case 'y':
				std::cout << "Pomyslnie wypisano " << currentUser->login << " z kierunku" << currentUser->spec->name;
				currentUser->spec->delStudent(currentUser);
				currentUser->leaveSpec();
				going = false;
				break;
			case 'n':
				going = false;
				break;
			}
		}
	}
}

void Menu::select(int op)
{
	switch (op)
	{
	case 0:
		selectMail();
		break;
	case 1:
		selectRegister();
		break;
	case 2:
		leaveSpec();
		break;
	default:
		logOut();
		break;
	}

}
