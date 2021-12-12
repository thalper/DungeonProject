#ifndef ATTACK_H_
#define ATTACK_H_
#include <string>
#include <vector>
#include "condition.h"

class Attack {
public:
    Attack();
    ~Attack();
    void setPrint(std::string print);
    void addCondition(Condition* condition);
    void addAction(std::string action);
    std::string getPrint();
    std::vector<Condition*> getConditions();
    std::vector<std::string> getActions();


private:
    std::vector<Condition*> conditions; // list of conditions for attack
    std::vector<std::string> actions; // list of actions
    std::string Print; // print statement for attack

};


#endif /* ATTACK_H_ */