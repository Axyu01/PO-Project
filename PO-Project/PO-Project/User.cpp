#include "Data.h"

User::User(std::string em, std::string log, std::string pwrd, std::string tp, MailData* mdata, UsersData* udata)
	:email{em}, login{log}, password{pwrd}, mbox(em), userType(tp)
{
	UsersData::userList.push_back(this);
}

User::User(std::string em, std::string log, std::string pwrd, std::string tp)
	: email{ em }, login{ log }, password{ pwrd }, mbox{MailBox(email)}, userType{tp}
{

}

void User::joinSpec(Spec* sp)
{
	spec = sp;
	sp->addStudent(this);
}


void User::joinLecture(Lecture* lec)
{
	userLectures.push_back(lec);
}

void User::leaveLecture(Lecture* lec)
{

	for (int i = 0; i < userLectures.size(); i++)
	{

		if (userLectures[i] == lec)
		{
			userLectures.erase(userLectures.begin() + i);
		}

	}
}

void User::leaveSpec()
{
	if (spec != nullptr)
	{
		spec = nullptr;
	}
}

bool User::isRegistered()
{
	if (spec == nullptr) return false;
	return true;
}

bool User::isRegistered(Lecture* lec)
{
	for (auto l : userLectures)
	{
		if (lec == l)
		{
			return true;
		}
	}
	return false;
}