#ifndef TRIGGER_H_
#define TRIGGER_H_
#include <string>
#include <vector>
#include "condition.h"


class Trigger {
public:
    Trigger();
    ~Trigger();
    void setType(std::string type);
    void setCommand(std::string command);
    void setPrint(std::string print);
    void addCondition(Condition* condition);
    void addAction(std::string action);
    void use();
    std::string getType();
    std::string getCommand();
    std::string getPrint();
    bool getUsed();
    std::vector<Condition*> getConditions();
    //bool test(std::string command, Game* game, Container* Inventory);
    std::vector<std::string> getActions();

private:
    std::vector<Condition*> conditions; // list of conditions for trigger
    std::string Type; // trigger permanence
    std::string Command; // trigger command
    std::string Print; // trigger print statement
    std::vector<std::string> Action; // trigger action
    bool Used; // has trigger been activated

};


#endif /* TRIGGER_H_ */