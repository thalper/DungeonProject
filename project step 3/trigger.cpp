#include "trigger.h"

Trigger::Trigger()    { // default constructor
	Type = "single";
	Used = false;
}

Trigger::~Trigger()    { 
	for (Condition* condition : conditions)
        delete condition;
}

void Trigger::setCommand(std::string command) {
	this->Command = command;
}

void Trigger::setType(std::string type) {
	this->Type = type;
}

void Trigger::setPrint(std::string print) {
	this->Print = print;
}

void Trigger::addCondition(Condition* condition)    {
    conditions.push_back(condition);
}

void Trigger::setAction(std::string action) {
	this->Action = action;
}

std::string Trigger::getType()	{
	return Type;
}

std::string Trigger::getCommand()	{
	return Command;
}

std::string Trigger::getPrint()	{
	return Print;
}

bool Trigger::getUsed()	{
	return Used;
}

void Trigger::use()	{
	this->Used = true;
}

std::vector<Condition*> Trigger::getConditions()   {
    return conditions;
}