#pragma once
#include "Data.h"

//////////////////////////////////////////////////////////////////
//																//
//																//
//		TA KLASA JEST TYLKO DLA DEBUGOWANIA BACKENDOWEGO		//
//				TO NIE JEST FINALNE NARZEDZIE					//
//																//
//////////////////////////////////////////////////////////////////

class Menu
{
	friend int main();
	
protected:

	User* currentUser;

public:

	Menu();
	void loginScreen(UsersData* ud, bool&);
	void logOut();

	virtual void selectionScreen();
	virtual void select(int);

	bool isLoggedIn();
	void drawMenu(int);
	void selectRegister();
	void leaveSpec();
	void selectChat();
	void openChat(Chat*);
	void selectMail();
	void selectCallendar();

	void selectGroup(Course*);
	void selectLecture(Group*);

};