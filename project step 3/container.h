#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
#include <vector>
#include "trigger.h"
#include <algorithm>

class Container {
public:
    Container();
    ~Container();
    void setName(std::string name);
    void setStatus(std::string status);
    void addAccept(std::string accept);
    void addTrigger(Trigger* trigger);
    void addItem(std::string item);
    void removeItem(std::string item);
    std::vector<Trigger*> getTriggers();
    std::string getName();
    std::string getStatus();
    std::vector<std::string> getItems();
    std::vector<std::string> getAccepted();

   

private:
    std::vector<Trigger*> triggers; // list of triggers in container
    std::string Name;
    std::string Status;
    std::vector<std::string> items;
    std::vector<std::string> accepted;
};


#endif /* CONTAINER_H_ */