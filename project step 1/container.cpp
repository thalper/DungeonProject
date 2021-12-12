#include "container.h"

Container::Container()  {

}

Container::~Container()  {
    for (Trigger* trigger : triggers)
        delete trigger;
}

void Container::addItem(std::string item) { 
	items.push_back(item);
}

void Container::addAccept(std::string accept) { 
	accepted.push_back(accept);
}

void Container::addTrigger(Trigger* trigger)    {
    triggers.push_back(trigger);
}

void Container::setName(std::string name) {
	this->Name = name;
}

void Container::setStatus(std::string status) {
	this->Status = status;
}

std::vector<Trigger*> Container::getTriggers()   {
    return triggers;
}

std::string Container::getName()	{
	return Name;
}

std::string Container::getStatus()	{
	return Status;
}

std::vector<std::string> Container::getItems()	{
	return items;
}
    
std::vector<std::string> Container::getAccepted()	{
	return accepted;
}