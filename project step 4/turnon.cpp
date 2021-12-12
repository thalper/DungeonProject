#include "turnon.h"

Turnon::Turnon()    {
}

void Turnon::setPrint(std::string print)    {
    Print = print;
}

void Turnon::setAction(std::string action)  {
    Action = action;
}

void Turnon::setUsed()  {
    Used = 0;
}

std::string Turnon::getPrint()  {
    return Print;
}

std::string Turnon::getAction()  {
    return Action;
}

void Turnon::use()  {
    Used += 1;
}

int Turnon::getUsed()   {
    return Used;
}