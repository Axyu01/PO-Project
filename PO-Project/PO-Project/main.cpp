#include <iostream>
#include "Data.h"
#include "Menu.h"
#include <string>
#include <conio.h>



int main()
{

	RegisterData regd;
	UsersData usersd;
	MailData maild;
	ChatData chatd;

	Data* data[4] = { &usersd ,&regd, &chatd ,&maild };

	Menu men;

	data[0]->readFromFile();
	data[1]->readFromFile();
	data[2]->readFromFile();

	//regd.addSpec("ITE");
	//regd.specs[0]->addCourse("Analiza Matematyczna 2");
	//regd.specs[0]->courses[0]->addGroup("Wyklad");
	//regd.specs[0]->courses[0]->groups[0]->addLecture("Wyklad - M.Wodecki", true, 5, Date(2021, 10, 1), 200, 0);
	//regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia - Joanna Welyczko", true, 3, Date(2021, 10, 1, 14,15), 200, 0, 0);
	//regd.addSpec("CBE");
	//regd.addSpec("EKA");
	//regd.addSpec("TEL");
	//regd.addSpec("TIN");
	//regd.addSpec("AIR");

	bool going = true;
	while (going)
	{

		men.loginScreen(&usersd, going);

		data[0]->saveToFile();
		data[1]->saveToFile();
		data[2]->saveToFile();
		data[3]->saveToFile();

		if (going == false) return 0;

		men.selectionScreen();

		data[0]->saveToFile();
		data[1]->saveToFile();
		data[2]->saveToFile();
		data[3]->saveToFile();
	}
	//User uone("Pierwszy@pwr.edu.pl","Pierwszy","password1", "student",&maild, &usersd);
	//User utwo("Drugi@pwr.edu.pl", "Drugi", "password2", "student", &maild, &usersd);
	//User uthree("Trzeci@pwr.edu.pl", "Trzeci", "password3", "student", &maild, &usersd);

	//MailBox one("one@pwr.edu.pl", &maild), two("two@pwr.edu.pl", &maild), three("three@pwr.edu.pl", &maild);

	//uone.mbox.sendEmail(&utwo.mbox);
	//uone.mbox.sendEmail(&utwo.mbox, "Mamo, potrzebuje klej i bibule na jutro.\n\n No ale pani naprawde powiedziala dopiero teraz!\n");


	/*regd.addSpec("ITE");
	regd.specs[0]->addCourse("Analiza 2.3");
	regd.specs[0]->courses[0]->addGroup("Wyklad");
	regd.specs[0]->courses[0]->groups[0]->addLecture("Wyklad Analiza 2.3", true, 3, Date(2021, 10, 2), 15, 200);
	regd.specs[0]->courses[0]->addGroup("Cwiczenia");
	regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia grupa 1", true, 3, Date(2021, 10, 2, 15), 15, 20);
	regd.specs[0]->courses[0]->groups[1]->addLecture("Cwiczenia grupa 2", true, 3, Date(2021, 10, 2, 15), 15, 20);

	
		for (auto s : regd.specs)
		{
			s->listCourse();
			for (auto c : s->courses)
			{
				std::cout << "  "; 
				c->listGroup();

				for (auto g : c->groups)
				{
					std::cout << "    ";
					g->listLecture();
				}
			}
		}

		return 0;



	saver = &usersd;

		saver->readFromFile();
	
		Chat test("TEST CHAT");

		UsersData::currentUser = UsersData::userList[0];

		while (true)
		{
			test.viewChat();
			test.sendMessage(UsersData::currentUser);
		}


	int i = 1;
	while (true)
	{
		usersd.userList[1]->mbox.listMail();
		int it = (_getch() - 48);
		usersd.userList[1]->mbox.readMail(it);
	}

	saver->saveToFile();
	saver = &maild;
	saver->saveToFile();*/

	return 0;
}

