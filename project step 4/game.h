#ifndef GAME_H_
#define GAME_H_
#include "room.h"
#include "item.h"
#include "container.h"
#include "creature.h"
#include <fstream>


class Game {
public:
    Game();
    ~Game();
    std::vector<Room*> rooms;
    std::vector<Item*> items;
    std::vector<Container*> containers;
    std::vector<Creature*> creatures;
    Container* Inventory;
   
    void printGame();
    void playGame();
    bool testTrigger(Trigger* trigger, std::string command);


private:
    
    
};


#endif /* GAME_H_ */