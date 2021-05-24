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
}


void User::joinLecture(std::string nm)
{

}

bool User::isRegistered()
{
	if (spec == nullptr) return false;
	return true;
}