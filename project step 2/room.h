#ifndef ROOM_H_
#define ROOM_H_
#include <string>
#include <vector>
#include "trigger.h"
#include <iostream>
#include <algorithm>


class Room {
public:
    Room();  
    ~Room();
    void setName(std::string name);
    void setType(std::string type);
    void addItem(std::string item);
    void addContainer(std::string container);
    void setDescription(std::string description);
    void addTrigger(Trigger* trigger);
    void addBorder(std::string borderName, std::string direction);
    void addCreature(std::string creature);
    void removeItem(std::string item);
    std::string getName();
    std::string getDescription();
    std::string getType();
    std::vector<std::string> getContainers();
    std::vector<std::string> getCreatures();
    std::vector<std::string> getItems();
    std::string getBorder(int i);
    std::vector<Trigger*> getTriggers();
    

private:
    std::string RoomName; // room name
    std::string Description; // description of room
    std::string Type; // type of room 
    std::string borders[4] = {}; // array of borders surrounding room

    std::vector<std::string> items; // list of items in room
    std::vector<std::string> containers; // list of containers in room
    std::vector<std::string> creatures; // list of creatures in room
    std::vector<Trigger*> triggers; // list of triggers in room
};


#endif /* ROOM_H_ */