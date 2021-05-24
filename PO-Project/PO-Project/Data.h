#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Funkcje_zapis.h"


class Data
{
public:
	virtual void saveToFile() = 0;
	virtual void readFromFile() = 0;
};

class MailBox;
class User;
class Chat;
class Date;
class Spec;

class Date
{
	friend class MailBox;

	int year = 2000;
	int month = 1;
	int day = 1;
	int hour = 12;
	int minute = 0;

public:

	Date();
	Date(int, int, int, int=12, int=0);
	void changeDate(int, int, int, int, int);
	void changeDate(int, int, int, int);
	void changeDate(int, int);
	std::string toString();
	void printDate();
};

class UsersData : public Data 
{
	friend class User;
	friend class Menu;
	friend int main();

	static std::vector<std::string> creds;
	static std::vector<User*> userList;
	static User* currentUser;

public:

	UsersData();

	void addUser();
	void delUser();
	void editUser();

	bool userExists(std::string);
	User* verifyUser(std::string, std::string);


	void registerUser();
	User* loginUser();

	void saveToFile();
	void readFromFile();
};

class RegisterData : public Data
{
	friend class Menu;
	static std::vector<Spec*> specs;

public:

	RegisterData();

	static void addSpec(std::string);
	static void listSpecs();

	void saveToFile();
	void readFromFile();

};

class ChatData : public Data
{
	friend class Chat;

	static std::vector<Chat*> chatList;

public:
	ChatData();

	void saveToFile();
	void readFromFile();
};

class MailData : public Data
{
	friend class MailBox;
	friend class User;

	static std::vector<MailBox*> mailBoxList;

public:

	MailData();

	void saveToFile();
	void readFromFile();


};
//
//class CallendarData :public Data
//{
//	std::vector<Event> uniEvents;
//	std::vector<Day> days;
//
//public:
//	CallendarData();
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class Event
//{
//	std::string eventName;
//	Date eventDate;
//	std::string description;
//
//public:
//	Event(std::string, Date);
//	Event(std::string, Date, std::string);
//};
//
//struct Day
//{
//	Event ev;
//	int day;
//};

class Chat : public Data
{
	friend class ChatData;

	std::string chatName;
	std::vector<std::string> chatArchive;

public:

	Chat(std::string);
	void sendMessage(User*);
	void viewChat();


	void saveToFile();
	void readFromFile();
};

class Lecture : public Data
{
	friend int main();
	friend class Group;

	std::string name;
	bool isEven;
	int weekDay;

	std::vector<User*> participants;

	Date startDate;
	int lectureCount;
	int userLimit;
	int userCount;
	Chat lectureChat = Chat(name);

public:

	Lecture(std::string, bool, int, Date, int, int);

	void saveToFile();
	void readFromFile();

};

class Group : public Data
{
	friend int main();
	friend class Course;

	std::string name;
	std::vector<Lecture*> lectures;

public:
	Group(std::string);

	void addLecture(std::string, bool, int, Date, int, int);
	void delLecture();

	void listLecture();

	void saveToFile();
	void readFromFile();
};

class Course : public Data
{
	friend int main();
	friend class Spec;

	std::string name;
	std::vector<Group*> groups;

public:
	Course(std::string);

	void addGroup(std::string);
	void delGroup();

	void listGroup();

	void saveToFile();
	void readFromFile();

};

class Spec : public Data
{
	friend int main();
	friend class RegisterData;
	friend class Menu;

	std::string name;
	std::vector<Course*> courses;

public:
	Spec(std::string);

	void addCourse(std::string);
	void delCourse();

	void listCourse();

	void saveToFile();
	void readFromFile();
};


class Mail : public Data
{
	friend class MailBox;

	std::string sender;
	std::string reciever;
	std::string text;
	Date date;

public:

	Mail(std::string, std::string, std::string); //konstruktor pobieraj¹cy datê systemu automatycznie
	Mail(std::string, std::string, std::string, Date); 

	void viewContents();
	void showHeader();

	void saveToFile();
	void readFromFile();

};

class MailBox : public Data
{

	friend class MailData;

	std::string address;
	std::vector<Mail*> mail;

public:

	MailBox(std::string);

	void sendEmail(MailBox*);
	void sendEmail(MailBox*, std::string);
	void sendEmail(std::string, std::string);
	void deleteEmail(int);

	void listMail();
	void readMail(int);
	

	void saveToFile();
	void readFromFile();


};

class User
{
	friend class UsersData;
	friend class Chat;
	friend class Menu;

	friend int main();

	std::string email;
	std::string login;
	std::string password;
	MailBox mbox;

	std::string userType;

	const Spec* spec = nullptr;
	std::vector<Lecture*> userLectures;
	//std::vector<Event*> customEvents;

public:

	User(std::string, std::string, std::string,std::string, MailData*, UsersData*);
	User(std::string, std::string, std::string, std::string);

	void joinSpec(Spec*);
	void joinLecture(std::string);

private:

	bool isRegistered();

public:

	//void addEvent();
	//void addEvent(Date);
	//void delCusomEvent();

};
