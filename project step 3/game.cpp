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

void Game::playGame()   {
    Room* currentRoom;
    for (Room* room : rooms)    {
        if (room->getName() == "Entrance")  {
            currentRoom = room;
            break;
        }
    }
    //std::cout << currentRoom->getName() << std::endl;
    std::cout << currentRoom->getDescription() << std::endl;
    Container* Inventory = new Container();
    Inventory->setName("inventory");

    bool end = false;
    std::string input_line;
    while (end == false)    {
        std::getline(std::cin, input_line);
        // win the game
        if (input_line == "open exit")  {
            if (currentRoom->getType() == "exit")   {
                std::cout << "Victory!" << std::endl;
                end = true;
            }
            else
                std::cout << "Can't exit." << std::endl;
        }

        // change rooms



        else if (input_line == "n" || input_line == "e" || input_line == "s" || input_line == "w")  {
            bool allowed = true;
            for (Trigger* trigger : currentRoom->getTriggers())   {
                if (trigger->getType() != "permanent" && trigger->getUsed() != 0)   {
                }
                else if (trigger->getCommand() == input_line)    {
                    bool individualAllowed = true;
                    bool found = false;
                    for (Condition* condition : trigger->getConditions())    {
                        if (condition->getStatus() == "") { // owner condition
                            bool tval = false;
                            if (condition->getOwner() == "inventory")   {
                                for (std::string item : Inventory->getItems())  {
                                    if (condition->getObject() == item) {
                                        tval = true;
                                        found = true;
                                        break;
                                    }
                                    if (found)
                                        break;
                                }
                                if (tval == condition->boolHas())   {
                                    allowed = false;
                                    individualAllowed = false;
                                }
                            }
                            else{
                                for (std::string container : currentRoom->getContainers())  {
                                    if (container == condition->getOwner())  {
                                        for (Container* container1 : containers)    {
                                            if (container1->getName() == container) {
                                                for (std::string item : container1->getItems()) {
                                                    if (item == condition->getObject()) {
                                                        tval = true;
                                                        found = true;
                                                        if (tval == condition->boolHas())   {
                                                            allowed = false;
                                                            individualAllowed = false;
                                                            found = true;
                                                            break;
                                                        }
                                                    }
                                                    if (found)
                                                        break;
                                                }
                                            }
                                            if (found)
                                                break;
                                        }
                                    }
                                    if (found) 
                                        break;
                                }
                            }
                        }
                        else    { // status condition
                            bool tval = false;
                            for (std::string container : currentRoom->getContainers())  {
                                if (condition->getObject() == container)    {
                                    found = true;
                                    for (Container* container1 : containers) {
                                        if (container1->getName() == container) {
                                            if (container1->getStatus() == condition->getStatus())
                                                tval = true;
                                        }
                                    }
                                }
                            }
                            if (found == false) {
                                for (std::string item : Inventory->getItems())  {
                                    if (item == condition->getObject()) {
                                        found = true;
                                        for (Item* item1 : items)   {
                                            if (item1->getName() == item)   {
                                                tval = (item1->getStatus() == condition->getStatus());
                                            }
                                        }
                                    }
                                }
                            }
                            if ((tval && condition->getHas()) || (!tval && !condition->getHas()))   {
                                allowed = false;
                                individualAllowed = false;
                            }
                        }
                    }
                    if (individualAllowed == false)
                        std::cout << trigger->getPrint() << std::endl;
                }
            }




            if (allowed == false)   {   
            }
            else if (input_line == "n") {
                if (currentRoom->getBorder(0) != "")   {
                    for (Room* room : rooms)    {
                        if (room->getName() == currentRoom->getBorder(0))  {
                            currentRoom = room;
                            //std::cout << currentRoom->getName() << std::endl;
                            std::cout << currentRoom->getDescription() << std::endl;
                            break;
                        }
                    }
                }
                else
                    std::cout << "cannot move that way" << std::endl;
            }
            else if (input_line == "e") {
                if (currentRoom->getBorder(1) != "")   {
                    for (Room* room : rooms)    {
                        if (room->getName() == currentRoom->getBorder(1))  {
                            currentRoom = room;
                            std::cout << currentRoom->getName() << std::endl;
                            std::cout << currentRoom->getDescription() << std::endl;
                            break;
                        }
                    }
                }
                else
                    std::cout << "cannot move that way" << std::endl;
            }
            else if (input_line == "s") {
                if (currentRoom->getBorder(2) != "")   {
                    for (Room* room : rooms)    {
                        if (room->getName() == currentRoom->getBorder(2))  {
                            currentRoom = room;
                            std::cout << currentRoom->getName() << std::endl;
                            std::cout << currentRoom->getDescription() << std::endl;
                            break;
                        }
                    }
                }
                else
                    std::cout << "cannot move that way" << std::endl;
            }
            else if (input_line == "w") {
                if (currentRoom->getBorder(3) != "")   {
                    for (Room* room : rooms)    {
                        if (room->getName() == currentRoom->getBorder(3))  {
                            currentRoom = room;
                            std::cout << currentRoom->getName() << std::endl;
                            std::cout << currentRoom->getDescription() << std::endl;
                            break;
                        }
                    }
                }
                else
                    std::cout << "cannot move that way" << std::endl;
            }
        }


        // temporary to test lock trigger
        else if (input_line == "set lock to unlocked")  {
            for (Container* container : containers) {
                if (container->getName() == "lock") {
                    container->setStatus("open");
                    std::cout << "lock has been unlocked" << std::endl;
                }
            }
        }





        // print inventory
        else if (input_line == "i")  {
            std::cout << "Inventory:" << std::endl;
            for (std::string item: Inventory->getItems())   {
                std::cout << "  " << item << std::endl;
            }
        }

        else    { // actions
            std::string word = input_line.substr(0, input_line.find(" ")); // first word of input
            if (word == "take") {
                std::string item_input = input_line;
                item_input.erase(item_input.begin(), item_input.begin()+5);
                bool found = false;
                for (std::string item: currentRoom->getItems()) {
                    if (item_input == item) {
                        found = true;
                        currentRoom->removeItem(item);
                        Inventory->addItem(item);
                        std::cout << "Item " << item << " added to inventory." << std::endl;
                        break;
                    }
                }
                if (found == false) {
                    for (std::string containerStr: currentRoom->getContainers())    {
                        for (Container* container: containers)  {
                            if (container->getName() == containerStr && container->getStatus() == "open") {
                                for (std::string item: container->getItems())   {
                                    if (item_input == item)  {
                                        found = true;
                                        container->removeItem(item);
                                        Inventory->addItem(item);
                                        std::cout << "Item " << item << " added to inventory from " << container->getName() << std::endl;
                                        break;
                                    }
                                }
                            }
                            if (found == true)
                                break;
                        }
                        if (found == true)  
                            break;
                    }
                }
                if (found == false) {
                    std::cout << "Item " << item_input << " does not exist in room " << currentRoom->getName()  << ", or container is not open." << std::endl;
                }
            }
            else if (word == "drop")    {
                std::string item_input = input_line;
                item_input.erase(item_input.begin(), item_input.begin()+5);
                for (std::string item: Inventory->getItems())   {
                    if (item == item_input) {
                        currentRoom->addItem(item);
                        Inventory->removeItem(item);
                        std::cout << "dropped " << item << std::endl;
                        break;
                    }
                }
            }
            else if (word == "open")    {
                bool found = false;
                std::string container_input = input_line;
                container_input.erase(container_input.begin(), container_input.begin()+5);
                for (std::string containerStr: currentRoom->getContainers())    {
                    if (containerStr == container_input)    {
                        found = true;
                        for (Container* container: containers)  {
                            if (container->getName() == containerStr)   {
                                if (container->getStatus() == "closed") {
                                    container->setStatus("open");
                                    std::cout << container->getName() << " has been opened. " << container->getName() << " contains: " << std::endl;
                                    for (std::string item : container->getItems())  {
                                        std::cout << "  " << item << std::endl;
                                    }
                                }
                                else if (container->getStatus() == "open")  {
                                    std::cout << container->getName() << " is already open." << std::endl;
                                }
                                else if (container->getStatus() == "locked")    {
                                    std::cout << container->getName() << " is locked." << std::endl;
                                }
                                else    
                                    std::cout << container->getName() << " has status " << container->getStatus() << std::endl;
                                break;
                            }
                        }
                    }
                    if (found == true)  
                        break;
                }
                if (found == false) 
                    std::cout << container_input << " not found in " << currentRoom->getName() << std::endl;
            }
            //else if (word == "read")
            else    
                std::cout << "command '" << word << "' not recognized" << std::endl;
        } 
        
    }
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