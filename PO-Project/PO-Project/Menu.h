#pragma once
#include "Data.h"
class Menu
{
	friend int main();
	
protected:

	User* currentUser;

	

public:

	Menu();
	void loginScreen(UsersData* ud);
	void logOut();

	virtual void selectionScreen();
	virtual void select(int);

	bool isLoggedIn();
	void drawMenu(int);
	void selectRegister();
	//void selectChat();
	void selectMail();
	//void selectCallendar();

	void selectGroup(Course*);
	void selectLecture(Group*);

};

class MailSystem : public Menu
{
public:
	MailSystem();
	void viewMailBox();
	void viewMailContents();
	void sendMail();
};