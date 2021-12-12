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
    void setAction(std::string action);
    std::string getType();
    std::string getCommand();
    std::string getPrint();
    int getUsed();
    std::vector<Condition*> getConditions();

private:
    std::vector<Condition*> conditions; // list of conditions for trigger
    std::string Type; // type of trigger 
    std::string Command; // trigger command
    std::string Print; // trigger print statement
    std::string Action; // trigger action
    int Used; // has trigger been activated

};


#endif /* TRIGGER_H_ */