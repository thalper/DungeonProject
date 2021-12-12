#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <vector>
#include <iostream>
#include "turnon.h"

class Item {
public:
    Item();
    ~Item();
    void setName(std::string name);
    void setWriting(std::string writing);
    void setStatus(std::string status);
    void setTurnon(Turnon* turnon);
    void setTurnon();
    std::string getName();
    std::string getStatus();
    std::string getWriting();
    Turnon* getTurnon();
   

private:
    std::string Name; // item name
    std::string Writing; // writing on item    
    std::string Status; // status of item
    Turnon* turnon; // what happens when the item is turned on
};


#endif /* ITEM_H_ */