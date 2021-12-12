#include "item.h"

Item::Item()    {
	setTurnon();
}

Item::~Item()    {
	if (turnon != NULL)
		delete turnon;
}

void Item::setName(std::string name) {
	Name = name;
}

void Item::setWriting(std::string writing) {
	Writing = writing;
}

void Item::setStatus(std::string status) {
	Status = status;
}

void Item::setTurnon(Turnon* _turnon)  {
	delete turnon;
    turnon = _turnon;
}


void Item::setTurnon() {
	Turnon* newTurnon = new Turnon;
	newTurnon->setPrint("");
	newTurnon->setAction("");
	newTurnon->setUsed();
	turnon = newTurnon;
}

std::string Item::getName()	{
	return Name;
}

std::string Item::getStatus()	{
	return Status;
}

std::string Item::getWriting()	{
	return Writing;
}


Turnon* Item::getTurnon()	{
	return turnon;
}
   
