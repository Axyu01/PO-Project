#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
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
	friend class CallendarSystem;

	int year = 2000;
	int month = 1;
	int day = 1;
	int hour = 12;
	int minute = 0;


public:

	Date();
	Date(int yy, int mm, int dd, int hh=12, int min=0);
	void changeDate(int min, int hh, int dd, int mm, int yy);
	void changeDate(int min, int hh, int dd, int mm);
	void changeDate(int min, int hh);
	void offsetDaysBy(int);
	void roundDate();
	bool isLeapYear();
	std::string toString();
	static bool isSameDay(const Date& first, const Date& second);


	int returnDayOfWeek();
	int returnDaysInMonth();
	int returnFirstDay();


	void printDate();
};

class Event
{
	friend class CallendarData;
	friend class CallendarSystem;

	std::string eventName;
	Date eventDate;
	std::string description;

public:
	Event(std::string, Date);
	Event(std::string, Date, std::string);
};

//struct Day
//{
//	Event ev;
//	int nr;
//};

class UsersData : public Data 
{
	friend class User;
	friend class Menu;

	static std::vector<std::string> creds;
	static std::vector<User*> userList;
	static User* currentUser;

public:

	UsersData();

	static void addUser(std::string ll, std::string pp, std::string tt);
	static void delUser(User* usr);
	void editUser();

	bool userExists(std::string);
	static User* verifyUser(std::string, std::string);
	static User* findUser(std::string);

	void registerUser();
	User* loginUser();

	void saveToFile();
	void readFromFile();
};

class RegisterData : public Data
{
	friend class Menu;
	friend class RegisterSystem;
	static std::vector<Spec*> specs;
	friend int main();

public:

	RegisterData();

	static void addSpec(std::string);
	static void delSpec(std::string);
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

	static Chat* chatExists(std::string);

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

class CallendarData :public Data
{
	friend class Event;
	friend class Lecture;

	static std::vector<Event*> uniEvents;
	//std::vector<Day> days;

public:
	CallendarData();

	static std::vector<Event*> returnUserEvents(User*,const Date&);

	void saveToFile();
	void readFromFile();
};

class Chat
{
	friend class ChatData;
	friend class ChatSystem;

	std::string chatName;
	std::vector<std::string> chatArchive;

public:

	Chat(std::string);
	void sendMessage(User*, std::string);
	void viewChat();


	void saveToFile();
	void readFromFile();
};

class Lecture
{
	friend class Group;
	friend class User;
	friend class Menu;
	friend class ChatSystem;
	friend class RegisterSystem;
	friend class CallendarData;
	friend class MailSystem;

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

	Lecture(std::string, bool, int, Date, int, int, int = 0);

	void addParticipant(User*);
	void delParticipant(User*);
	void clearParticipants();

	void saveToFile(std::string, std::string, std::string);
	void readFromFile(std::string, std::string, std::string);

};

class Group
{
	friend class Course;
	friend class Menu;
	friend class RegisterSystem;

	std::string name;
	std::vector<Lecture*> lectures;

public:
	Group(std::string);

	void addLecture(std::string, bool, int, Date, int, int, int=0);
	void delLecture(std::string);
	void clearLectures();

	void delStudent(User*);

	void listLecture();
	bool userRegisteredInGroup(User*);

	void saveToFile(std::string, std::string);
	void readFromFile(std::string, std::string);
};

class Course
{
	friend class Spec;
	friend class Menu;
	friend class RegisterSystem;

	std::string name;
	std::vector<Group*> groups;

public:
	Course(std::string);

	void addGroup(std::string);
	void delGroup(std::string);

	void clearGroups();

	void delStudent(User*);

	void listGroup();

	void saveToFile(std::string);
	void readFromFile(std::string);

};

class Spec
{
	friend class RegisterSystem;
	friend class RegisterData;
	friend class Menu;
	friend class UsersData;

	std::string name;
	std::vector<Course*> courses;
	std::vector<User*> students;

public:
	Spec(std::string);

	void addCourse(std::string);
	void delCourse(std::string);

	void clearCourses();

	void addStudent(User*);
	void delStudent(User*);

	void listCourse();

	void saveToFile();
	void readFromFile();
};

class Mail
{
	friend class MailBox;
	friend class MailSystem;
	friend class User;

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

class MailBox
{

	friend class MailData;
	friend class User;
	friend class MailSystem;
	friend class UsersData;

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
	friend class Lecture;
	friend class Spec;
	friend class ChatSystem;
	friend class RegisterSystem;
	friend class CallendarData;
	friend class MailSystem;

	std::string email;
	std::string login;
	std::string password;
	MailBox mbox;

	std::string userType;

	Spec* spec = nullptr;
	std::vector<Lecture*> userLectures;
	std::vector<Event*> customEvents;
	std::vector<Event*> lectureEvents;

public:

	User(std::string, std::string, std::string,std::string, MailData*, UsersData*);
	User(std::string, std::string, std::string, std::string);

	void joinSpec(Spec*);
	void joinLecture(Lecture*);
	void leaveLecture(Lecture*);
	void leaveSpec();



	bool isRegistered();
	bool isRegistered(Lecture*);



	//void addEvent();
	//void addEvent(Date);
	void delCusomEvent(Event*);

};