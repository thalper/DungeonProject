#include "game.h"

Game::Game()    {

}

Game::~Game()   {
    for (Room* room : rooms)
        delete room;
    for (Item* item : items){
        delete item;
    }
    for (Container* container : containers)
        delete container;
    for (Creature* creature : creatures)
        delete creature;    
}

void Game::printGame()   {
    std::ofstream oFile;
    oFile.open("output.txt");
    oFile<<"Map:\n";
    for (Room* room : rooms)    {
        oFile<<"    Room:\n";
        oFile<<"        Name: " << room->getName() << "\n";
        oFile<<"        Description: " << room->getDescription() << "\n";
        oFile<<"        Type: " << room->getType() << "\n";
        for (std::string container : room->getContainers()) {
            oFile<<"        Container: " << container << "\n";
        }
        for (std::string creature : room->getCreatures()) {
            oFile<<"        Creature: " << creature << "\n";
        }
        for (std::string item : room->getItems()) {
            oFile<<"        Item: " << item << "\n";
        }
        for (int i = 0; i < 4; i++)  {
            std::string dir;
            if (i==0)
                dir = "north";
            else if (i==1)
                dir = "east";
            else if (i==2)
                dir = "south";
            else if (i==3)
                dir = "west";
            std::string border = room->getBorder(i);
            if (border != "")
                oFile<<"        " << dir << ": " << border << "\n";
        }
    
        for (Trigger* trigger : room->getTriggers())   {
                oFile<<"        Trigger:" << "\n";
                oFile<<"            Permanent: " << (trigger->getType() == "permanent" ? "1" : "0") << "\n";
                oFile<<"            Used: " << trigger->getUsed() << "\n";
                oFile<<"            Command: " << trigger->getCommand() << "\n";
                oFile<<"            Print: " << trigger->getPrint() << "\n";
                for (Condition* condition : trigger->getConditions())   {
                    oFile<<"            Condition:" << "\n";
                    oFile<<"                Has: " << condition->getHas() << "\n";
                    oFile<<"                Object: " << condition->getObject() << "\n";
                    if (condition->getStatus() != "") {
                        oFile<<"                Status: " << condition->getStatus() << "\n";
                    }
                    else if (condition->getOwner() != "")   {
                        oFile<<"                Owner: " << condition->getOwner() << "\n";
                    }
                }
        }
    }

    for (Item* item : items)    {
        oFile<<"    Item:\n";
        if (item->getName() != "")
            oFile<<"        Name: " << item->getName() << "\n";
        if (item->getStatus() != "")
            oFile<<"        Status: " << item->getStatus() << "\n";
        if (item->getWriting() != "")   
            oFile<<"        Writing: " << item->getWriting() << "\n";

        if (item->getTurnon())    {
            oFile<<"        Turnon:\n";
            oFile<<"            Print: " << item->getTurnon()->getPrint() << "\n";
            oFile<<"            Action: " << item->getTurnon()->getAction() << "\n";
            oFile<<"            Used: " << item->getTurnon()->getUsed() << "\n"; 
        }
    }

    for (Container* container : containers) {
        oFile<<"    Container:\n";
        oFile<<"        Name: " << container->getName() << "\n";
        if (container->getStatus() != "")
            oFile<<"        Status: " << container->getStatus() << "\n";
        for (std::string item : container->getItems())   {
            oFile<<"        Item: " << item << "\n";
        }
        for (std::string accepted : container->getAccepted())   {
            oFile<<"        Accept: " << accepted << "\n";
        }


        for (Trigger* trigger : container->getTriggers())   {
            oFile<<"        Trigger:" << "\n";
            oFile<<"            Permanent: " << (trigger->getType() == "permanent" ? "1" : "0") << "\n";
            oFile<<"            Used: " << trigger->getUsed() << "\n"; 
            oFile<<"            Command: " << trigger->getCommand() << "\n";
            oFile<<"            Print: " << trigger->getPrint() << "\n";
            for (Condition* condition : trigger->getConditions())   {
                oFile<<"            Condition:" << "\n";
                oFile<<"                Has: " << condition->getHas() << "\n";
                oFile<<"                Object: " << condition->getObject() << "\n";
                if (condition->getStatus() != "") {
                    oFile<<"                Status: " << condition->getStatus() << "\n";
                }
                else if (condition->getOwner() != "")   {
                    oFile<<"                Owner: " << condition->getOwner() << "\n";
                }
            }
        }
    }

    for (Creature* creature : creatures)    {
        oFile<<"    Creature:\n";
        oFile<<"        Name: " << creature->getName() << "\n";

        for (Trigger* trigger : creature->getTriggers())   {
                oFile<<"        Trigger:" << "\n";
                oFile<<"            Permanent: " << (trigger->getType() == "permanent" ? "1" : "0") << "\n";
                oFile<<"            Used: " << trigger->getUsed() << "\n"; 
                oFile<<"            Command: " << trigger->getCommand() << "\n";
                oFile<<"            Print: " << trigger->getPrint() << "\n";
                for (Condition* condition : trigger->getConditions())   {
                    oFile<<"            Condition:" << "\n";
                    oFile<<"                Has: " << condition->getHas() << "\n";
                    oFile<<"                Object: " << condition->getObject() << "\n";
                    if (condition->getStatus() != "") {
                        oFile<<"                Status: " << condition->getStatus() << "\n";
                    }
                    else if (condition->getOwner() != "")   {
                        oFile<<"                Owner: " << condition->getOwner() << "\n";
                    }
                }
        }

            if (creature->getAttack())  {
                oFile<<"        Attack:" << "\n";
                oFile<<"            Print: " << creature->getAttack()->getPrint() << "\n";
                for (Condition* condition : creature->getAttack()->getConditions())   {
                    oFile<<"            Condition:" << "\n";
                    oFile<<"                Has: " << condition->getHas() << "\n";
                    oFile<<"                Object: " << condition->getObject() << "\n";
                    if (condition->getStatus() != "") {
                        oFile<<"                Status: " << condition->getStatus() << "\n";
                    }
                    else if (condition->getOwner() != "")   {
                        oFile<<"                Owner: " << condition->getOwner() << "\n";
                    }
                }
                for (std::string action : creature->getAttack()->getActions())  {
                    oFile<<"            Action: " << action << "\n";
                }
        }

    }
    oFile.close();
}