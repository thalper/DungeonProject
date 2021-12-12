#include "attack.h"

Attack::Attack()    {

}

Attack::~Attack()   {
    for (Condition* condition : conditions)
        delete condition;
}

void Attack::setPrint(std::string print) {
	this->Print = print;
}

void Attack::addCondition(Condition* condition)    {
    conditions.push_back(condition);
}

void Attack::addAction(std::string action)  {
    actions.push_back(action);
}

std::string Attack::getPrint()  {
    return Print;
}

std::vector<Condition*> Attack::getConditions() {
    return conditions;
}

std::vector<std::string> Attack::getActions()   {
    return actions;
}