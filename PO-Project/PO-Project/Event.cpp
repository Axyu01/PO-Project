#include "Data.h"


Event::Event(std::string name, Date date)
	:eventName{name}, eventDate{date}
{
	CallendarData::uniEvents.push_back(this);
}

Event::Event(std::string name, Date date, std::string desc)
	:eventName{name}, eventDate{date}, description{desc}
{

}