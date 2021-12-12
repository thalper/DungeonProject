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

bool Game::testTrigger(Trigger* trigger, std::string command) {
	if (trigger->getCommand() != "" && trigger->getCommand() != command)
		return false;
	if (trigger->getType() == "single" && trigger->getUsed() == true)
		return false;
	bool CTV = true; // condition truth value
	for (Condition* condition : trigger->getConditions())	{
		std::string objName = condition->getObject();
		Item* itemObj;
		Container* containerObj;
		Creature* creatureObj;
		int objType = 0; // 1 item, 2 container, 3 creature
		for (Item* item : items)	{
			if (item->getName() == objName)	{
				itemObj = item;
				objType = 1;
				break;
			}
		}
		if (objType == 0)	{
			for (Container* container : containers)	{
				if (container->getName() == objName)	{
					containerObj = container;
					objType = 2;
					break;
				}
			}
		}
		if (objType == 0)	{
			for (Creature* creature : creatures)	{
				if (creature->getName() == objName)	{
					creatureObj = creature;
					objType = 3;
					break;
				}
			}
		}
		if (condition->getOwner() == "")	{ // status condition
			switch(objType)	{
				case 1:
					if (itemObj->getStatus() != condition->getStatus())
						CTV = false;
					break;
				case 2: 
					if (containerObj->getStatus() != condition->getStatus())
						CTV = false;
					break;
				case 3: 
					std::cout << "creature with status condition???? " << creatureObj->getName() << std::endl;
					break;
				
			}
		}
		else	{ // owner condition
            bool found = false;
			switch(objType) {
				case 1: 
					if (condition->getOwner() == "inventory")	{
						CTV = false;
						for (std::string item : Inventory->getItems())	{
							if (itemObj->getName() == item)	{
								CTV = true;
								break;
							}
						}
						CTV = (CTV == condition->getHas());
					}
					for (Container* container : containers)	{
						if (condition->getOwner() == container->getName())	{
							found = true;
							CTV = false;
							for (std::string item : container->getItems())	{
								if (itemObj->getName() == item)	{
									CTV = true;
									break;
								}
							}
							CTV = (CTV == condition->getHas());
						}
					}
					if (!found)	{
						for (Room* room : rooms)	{
							if (condition->getOwner() == room->getName())	{
								found = true;
								CTV = false;
								for (std::string item : room->getItems())	{
									if (itemObj->getName() == item)	{
										CTV = true;
										break;
									}
								}
								CTV = (CTV == condition->getHas());
							}
						}
					}
					break;
				case 2:
					std::cout << "container has owner????" << std::endl;

			}
		}
		if (!CTV)
			break;
	}
	return CTV;
}

void Game::playGame()   {
    Room* currentRoom;
    for (Room* room : rooms)    {
        if (room->getName() == "Entrance")  {
            currentRoom = room;
            break;
        }
    }
    std::cout << currentRoom->getDescription() << std::endl;
    //Inventory->setName("inventory");

    bool end = false;
    std::string input_line;
    std::vector<std::string> inputQ;
    while (end == false)    {
        if (inputQ.empty())
            std::getline(std::cin, input_line);
        else    {
            input_line = inputQ.back();
            inputQ.pop_back();
        }
        // win the game
        if (input_line == "open exit")  {
            if (currentRoom->getType() == "exit")   {
                std::cout << "Victory!" << std::endl;
                end = true;
            }
            else
                std::cout << "Can't exit." << std::endl;
        }

        else if (input_line == "Game Over") {
            std::cout << "Victory!" << std::endl;
            end = true;
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
                            std::cout << currentRoom->getDescription() << std::endl;
                            break;
                        }
                    }
                }
                else
                    std::cout << "cannot move that way" << std::endl;
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
            if (word == "Add")  {
                std::string remainder = input_line;
                remainder.erase(remainder.begin(), remainder.begin()+4);
                std::string itemName = remainder.substr(0, remainder.find(" "));
                remainder.erase(remainder.begin(), remainder.begin()+itemName.length()+1);
                std::string temp = remainder.substr(0, remainder.find(" "));
                if (temp != "to")
                    std::cout << "command '" << input_line << "' not recognized" << std::endl;
                else
                    remainder.erase(remainder.begin(), remainder.begin()+3);
                bool found = false;
                int objType = 0; // 0 none, 1 item, 2 container, 3 creature
                for (Item* item : items)    {
                    if (item->getName() == itemName)   {
                        found = true;
                        objType = 1;
                        break;
                    }
                }
                for (Container* container : containers) {
                    if (found)
                        break;
                    if (container->getName() == itemName)   {
                        found = true;
                        objType = 2;
                        break;
                    }
                }
                for (Creature* creature : creatures)    {
                    if (found)
                        break;
                    if (creature->getName() == itemName)  {
                        found = true;
                        objType = 3;
                        break;
                    }
                }
                if (found && remainder != "inventory")  {
                    found = false;
                    for (Room* room : rooms)    {
                        if (room->getName() == remainder)   {
                            if (objType == 1)
                                room->addItem(itemName);
                            else if (objType == 2)
                                room->addContainer(itemName);
                            else if (objType == 3) 
                                room->addCreature(itemName);
                            found = true;
                            break;
                        }
                    }
                    if (!found && objType == 1) {
                        for (Container* container : containers) {
                            if (container->getName() == remainder)  {
                                container->addItem(itemName);
                                found = true;
                                break;
                            }
                        }
                    }
                }
                if (!found)
                    std::cout << "'Add' Error" << itemName << std::endl;
            }

            else if (word == "Delete")  {
                std::string itemName = input_line;
                itemName.erase(itemName.begin(), itemName.begin()+7);
                bool found = false;
                int objType = 0; // 0 none, 1 item, 2 container, 3 creature, 4 room
                for (Item* item : items)    {
                    if (item->getName() == itemName)   {
                        found = true;
                        objType = 1;
                        break;
                    }
                }
                for (Container* container : containers) {
                    if (found)
                        break;
                    if (container->getName() == itemName)   {
                        found = true;
                        objType = 2;
                        break;
                    }
                }
                for (Creature* creature : creatures)    {
                    if (found)
                        break;
                    if (creature->getName() == itemName)  {
                        found = true;
                        objType = 3;
                        break;
                    }
                }
                for (Room* room : rooms)    {
                    if (found) 
                        break;
                    if (room->getName() == itemName)    {
                        found = true;
                        objType = 4;
                        break;
                    }
                }

                if (objType == 1)   {
                    for (Container* container : containers) {
                        container->removeItem(itemName);
                    }
                    for (Room* room : rooms)    {
                        room->removeItem(itemName);
                    }
                }

                else if (objType == 2)  {
                    for (Room* room : rooms)    {
                        room->removeContainer(itemName);
                    }
                }

                else if (objType == 3) {
                    for (Room* room : rooms)    
                        room->removeCreature(itemName);           
                }
                if (!found)
                    std::cout << "'Delete' Error" << std::endl;
            }

            else if (word == "take") {
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
                                    for (std::string item : container->getItems())  {
                                        std::cout << "  " << item << std::endl;
                                    }
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
            else if (word == "read")    {
                bool found = false;
                std::string item_input = input_line;
                item_input.erase(item_input.begin(), item_input.begin()+5);
                for (std::string item : Inventory->getItems())  {
                    if (item == item_input) {
                        found = true;
                        for (Item* itemObj : items) {
                            if (itemObj->getName() == item) {
                                if (itemObj->getWriting() == "")
                                    std::cout << item << " has nothing written on it." << std::endl;
                                else
                                    std::cout << itemObj->getWriting() << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (found == false)
                    std::cout << item_input << " is not in inventory." << std::endl;
            }
            else if (word == "update") {
                std::string remainder = input_line;
                remainder.erase(remainder.begin(), remainder.begin()+7);
                std::string object = remainder.substr(0, remainder.find(" "));
                remainder.erase(remainder.begin(), remainder.begin()+object.length()+1);
                std::string test = remainder.substr(0, remainder.find(" "));
                if (test != "to")
                    std::cout << "command '" << input_line << "' not recognized" << std::endl;
                else{
                    remainder.erase(remainder.begin(), remainder.begin()+3);
                    bool found = false;
                    //for item, container, creature
                    for (Item* item : items)    {
                        if (item->getName() == object)   {
                            found = true;
                            item->setStatus(remainder);
                            break;
                        }
                    }
                    if (found == false) {
                        for (Container* container : containers) {
                            if (container->getName() == object) {
                                found = true;
                                container->setStatus(remainder);
                                break;
                            }
                        }
                    }
                    if (found == false) {
                        std::cout << "can not update the status of " << object << std::endl;
                    }
                }
            }
            else if (word == "put") {
                std::string remainder = input_line;
                remainder.erase(remainder.begin(), remainder.begin()+4);
                std::string item_input = remainder.substr(0, remainder.find(" "));
                bool exists = false;
                for (std::string itemName : Inventory->getItems())  {
                    if (itemName == item_input) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    remainder.erase(remainder.begin(), remainder.begin()+item_input.length()+1);
                    std::string test = remainder.substr(0, remainder.find(" "));
                    if (test != "in")
                        std::cout << "command '" << input_line << "' not recognized" << std::endl;
                    else{
                        remainder.erase(remainder.begin(), remainder.begin()+3);
                        exists = false;
                        for (std::string container : currentRoom->getContainers())  {
                            if (remainder == container)  {
                                exists = true;
                                break;
                            }
                        }
                        if (!exists)    {
                            std::cout << remainder << " does not exist." << std::endl;
                        }
                        else{
                            for (Container* container : containers) {
                                if (container->getName() == remainder) {
                                    bool accept = false;
                                    bool open = false;
                                    if (container->getStatus() == "open")
                                        open = true;
                                    for (std::string accepted : container->getAccepted()) {
                                        if (item_input == accepted)
                                            accept = true;
                                    }
                                    if (!open)  {
                                        std::cout << "Cannot add " << item_input << " to closed " << container->getName() << std::endl;
                                    }
                                    else if (accept) {
                                        container->addItem(item_input);
                                        Inventory->removeItem(item_input);
                                        std::cout << "Item " << item_input << " added to " << remainder << "." << std::endl;
                                    }
                                    else    
                                        std::cout << "Error" << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                    std::cout << item_input << " not in inventory." << std::endl;
            }
            else if (word == "turn")    {
                std::string remainder = input_line;
                remainder.erase(remainder.begin(), remainder.begin()+5);
                std::string test = remainder.substr(0, remainder.find(" "));
                if (test == "on")   {
                    bool found = false;
                    remainder.erase(remainder.begin(), remainder.begin()+3);
                    for (std::string item : Inventory->getItems())  {
                        if (item == remainder)  {
                            found = true;
                            for (Item* itemObj : items) {
                                if (itemObj->getName() == item) {
                                    Turnon* turnon = itemObj->getTurnon();
                                    turnon->use();
                                    std::cout << turnon->getPrint() << std::endl;
                                    inputQ.push_back(turnon->getAction());
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    if (!found)
                        std::cout << "Error" << std::endl;
                }
                else 
                    std::cout << "Error" << std::endl;
            }
            else if (word == "attack")  {
                std::string remainder = input_line;
                remainder.erase(remainder.begin(), remainder.begin()+7);
                std::string creature_input = remainder.substr(0, remainder.find(" "));
                bool exists = false;
                for (std::string creatureName : currentRoom->getCreatures())  {
                    if (creatureName == creature_input) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    remainder.erase(remainder.begin(), remainder.begin()+creature_input.length()+1);
                    std::string test = remainder.substr(0, remainder.find(" "));
                    if (test != "with")
                        std::cout << "command '" << input_line << "' not recognized" << std::endl;
                    else    {
                        remainder.erase(remainder.begin(), remainder.begin()+5);
                        exists = false;
                        for (std::string item : Inventory->getItems())  {
                            if (remainder == item)  {
                                exists = true;
                                break;
                            }
                        }
                        if (!exists)    {
                            std::cout << "You don't have a(n) " << remainder << std::endl;
                        }
                        else    {
                            bool vulnerable = false;
                            
                            for (Creature* creature : creatures)    {
                                if (creature->getName() == creature_input)  {
                                    for (std::string vulnerability : creature->getVulnerabilities())  {
                                        if (vulnerability == remainder) {
                                            vulnerable = true;
                                            std::cout << "You assault the " << creature_input << " with the " << remainder << std::endl;
                                            for (Trigger* trigger : creature->getTriggers())    {
                                                
                                                if (this->testTrigger(trigger, input_line))    {
                                                    trigger->use();
                                                    std::cout << trigger->getPrint() << std::endl;
                                                    for (std::string action : trigger->getActions())    {
                                                        inputQ.push_back(action);
                                                    }
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    if (vulnerable) {
                                        std::cout << creature->getAttack()->getPrint() << std::endl;
                                        for (std::string action : creature->getAttack()->getActions())  {
                                            inputQ.push_back(action);
                                        }
                                    }
                                    break;
                                }
                            }
                            if (!vulnerable)   
                                std::cout << "not vulnerable" << std::endl;
                        }
                    }
                }
                else 
                    std::cout << "Error" << std::endl;
            }
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