#include "Data.h"

std::vector<Event*> CallendarData::uniEvents;

CallendarData::CallendarData()
{}

void CallendarData::saveToFile()
{

}

std::vector<Event*> CallendarData::returnUserEvents(User* usr, const Date &dt)
{
	std::vector<Event*> events;
	for (auto e : CallendarData::uniEvents)
	{
		for (auto l : usr->userLectures)
		{
			if (l->name == e->eventName && Date::isSameDay(e->eventDate,dt))
			{
				events.push_back(e);
			}
		}
	}
	for (auto e : usr->customEvents)
	{
		if (Date::isSameDay(e->eventDate, dt))
		{
			events.push_back(e);
		}
	}

	return events;
}

void CallendarData::readFromFile()
{

}