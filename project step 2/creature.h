#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include "trigger.h"
#include "attack.h"

class Creature {
public:
    Creature();
    ~Creature();
    void setName(std::string name);
    void addVulnerability(std::string vulnerability);
    void setAttack(Attack* _attack);
    void addTrigger(Trigger* trigger);
    std::string getName();
    std::vector<std::string> getVulnerabilities();
    Attack* getAttack();
    std::vector<Trigger*> getTriggers();
   

private:
    std::string Name;
    std::vector<std::string> vulnerabilities;
    Attack* attack;
    std::vector<Trigger*> triggers; // list of triggers in creature
    
};


#endif /* CREATURE_H_ */