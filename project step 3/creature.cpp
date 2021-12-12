#include "creature.h"

Creature::Creature()  {
    attack = NULL;
}

Creature::~Creature()  {
    for (Trigger* trigger : triggers)
        delete trigger;
    if (attack != NULL)
        delete attack;
}

void Creature::addTrigger(Trigger* trigger)    {
    triggers.push_back(trigger);
}

void Creature::setName(std::string name)    {
    Name = name;
}

void Creature::addVulnerability(std::string vulnerability)  {
    vulnerabilities.push_back(vulnerability);
}

void Creature::setAttack(Attack* _attack)   {
    attack = _attack;
}

std::vector<Trigger*> Creature::getTriggers()   {
    return triggers;
}

std::vector<std::string> Creature::getVulnerabilities() {
    return vulnerabilities;
}

Attack* Creature::getAttack()   {
    return attack;
}

std::string Creature::getName() {
    return Name;
}