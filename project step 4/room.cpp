#include "room.h"


Room::Room()    { // default constructor
    Type = "regular"; // type is regular unless otherwise specified 
}

Room::~Room()   {
    for (Trigger* trigger : triggers)
        delete trigger;
}

void Room::setName(std::string name) {
	this->RoomName = name;
}

void Room::setType(std::string type) {
	this->Type = type;
}

void Room::setDescription(std::string description) {
	this->Description = description;
}

void Room::addItem(std::string item) { 
	items.push_back(item);
}

void Room::removeItem(std::string item) { 
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

void Room::removeContainer(std::string container) { 
    auto it = std::find(containers.begin(), containers.end(), container);
    if (it != containers.end()) {
        containers.erase(it);
    }
}

void Room::removeCreature(std::string creature) { 
    auto it = std::find(creatures.begin(), creatures.end(), creature);
    if (it != creatures.end()) {
        creatures.erase(it);
    }
}

void Room::addContainer(std::string container) {
    containers.push_back(container);
}

void Room::addCreature(std::string creature)   {
    creatures.push_back(creature);
}

void Room::addTrigger(Trigger* trigger)    {
    triggers.push_back(trigger);
}

void Room::addBorder(std::string borderName, std::string direction)  {
    if (direction == "north")
        borders[0] = borderName;
    else if (direction == "east")
        borders[1] = borderName;
    else if (direction == "south")
        borders[2] = borderName;
    else if (direction == "west")
        borders[3] = borderName;
    else    
        std::cout << "direction of border is wrong" << direction << std::endl;
}

std::string Room::getName() {
    return RoomName;
}

std::string Room::getDescription() {
    return Description;
}

std::string Room::getType() {
    return Type;
}

std::vector<std::string> Room::getContainers() {
    return containers;
}

std::vector<std::string> Room::getCreatures() {
    return creatures;
}

std::vector<std::string> Room::getItems() {
    return items;
}

std::string Room::getBorder(int i)  {    
    return borders[i]; // [0,1,2,3] -> [north, east, south, west]
}

std::vector<Trigger*> Room::getTriggers()   {
    return triggers;
}
