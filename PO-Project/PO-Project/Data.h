#pragma once

#include <iostream>
#include <vector>
#include <string>

class Data
{
public:
	virtual void saveToFile() = 0;
	virtual void readFromFile() = 0;
};
//
//class UsersData : public Data 
//{
//	std::vector<std::string> creds;
//	std::vector<User*> userList;
//	User* currentUser;
//
//public:
//	UsersData();
//
//	void addUser();
//	void delUser();
//	void editUser();
//
//	bool userExists(std::string);
//	User* verifyUser(std::string, std::string);
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class RegisterData : public Data
//{
//	std::vector<Spec*> specs;
//
//public:
//	RegisterData();
//
//	void saveToFile();
//	void readFromFile();
//
//};
//
//class ChatData : public Data
//{
//	std::vector<Chat*> chatList;
//
//public:
//	ChatData();
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class MailData : public Data
//{
//	std::vector<MailBox*> mailBoxLis;
//
//public:
//
//	MailData();
//
//	void saveToFile();
//	void readFromFile();
//};
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
//
//class Chat : public Data
//{
//	std::string chatName;
//	std::vector<std::string> chatArchive;
//
//public:
//	Chat(std::string);
//	void sendMessage(User*);
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class Lecture : public Data
//{
//	std::string name;
//	bool isEven;
//	int weekDay;
//
//	std::vector<User*> participants;
//
//	Date startDate;
//	int lectureCount;
//	int userLimit;
//	int userCount;
//	Chat lectureChat;
//
//public:
//
//	Lecture(std::string, bool, int, Date, int, int, int);
//
//	void saveToFile();
//	void readFromFile();
//
//};
//
//class Group : public Data
//{
//	std::string name;
//	std::vector<Lecture*> lectures;
//
//public:
//	Group(std::string);
//
//	void addLecture();
//	void delLecture();
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class Course : public Data
//{
//	std::string name;
//	std::vector<Group*> groups;
//
//public:
//	Course(std::string);
//
//	void addGroup();
//	void delGroup();
//
//	void saveToFile();
//	void readFromFile();
//
//};
//
//class Spec : public Data
//{
//	std::string name;
//	std::vector<Course*> courses;
//
//public:
//	Spec(std::string);
//
//	void addCourse();
//	void delCourse();
//
//	void saveToFile();
//	void readFromFile();
//};
//
//class User
//{
//	std::string email;
//	std::string login;
//	std::string password;
//	MailBox mailBox;
//
//	std::string userType;
//
//	const Spec* spec;
//	std::vector<Lecture*> userLectures;
//	std::vector<Event*> customEvents;
//
//public:
//
//	User(std::string, std::string, std::string);
//
//	void joinSpec();
//	void joinLecture();
//
//private:
//
//	bool isRegistered();
//
//public:
//
//	void addEvent();
//	void addEvent(Date);
//	void delCusomEvent();
//
//};

class Date
{
	int year=2000;
	int month=1;
	int day=1;
	int hour=12;
	int minute=0;

public:

	Date();
	Date(int, int, int, int, int);
	void changeDate(int, int, int, int, int);
	void changeDate(int, int, int, int);
	void changeDate(int, int);
	void printDate();
};

class Mail : public Data
{
	std::string sender;
	std::string reciever;
	std::string text;
	Date date;

public:

	Mail(std::string, std::string, std::string); //konstruktor pobieraj¹cy datê systemu automatycznie
	Mail(std::string, std::string, std::string, Date); 

	void viewContents();

	void saveToFile();
	void readFromFile();

};
//
//class MailBox : public Data
//{
//	std::string address;
//	std::vector<Mail*> mail;
//
//public:
//	MailBox(std::string);
//
//	void sendEmail(MailBox*);
//	void deleteEmail();
//	void readMail();
//
//	void saveToFile();
//	void readFromFile();
//};
