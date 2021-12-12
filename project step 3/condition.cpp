#include "condition.h"

Condition::Condition()    { // default constructor
}

void Condition::setHas(bool has){
    this->Has = has;
}

void Condition::setName(std::string name){
    this->Name = name;
}

void Condition::setOwner(std::string owner){
    this->Owner = owner;
}

void Condition::setStatus(std::string status){
    this->Status = status;
}

void Condition::setObject(std::string object){
    this->Object = object;
}

int Condition::getHas()    {
    return Has ? 1 : 0;
}

bool Condition::boolHas()  {
    return Has;
}

std::string Condition::getObject()  {
    return Object;
}

std::string Condition::getStatus()  {
    return Status;
}

std::string Condition::getOwner()  {
    return Owner;
}