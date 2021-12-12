#include <string>
#include <vector>
#include <iostream>
#include "XMLParser.h"
#include "tinyxml.h"




Condition* XMLParser::parseCondition(TiXmlElement* element) {
	Condition* condition = new Condition();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
        TiXmlElement* childElement = node->ToElement();
        if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
            if (elementName == "has")   {
                std::string value = childElement->GetText();
                if (value == "no")
                    condition->setHas(false);
                else
                    condition->setHas(true);
            }
            else if (elementName == "name") {
                condition->setName(childElement->GetText());
            }
            else if (elementName == "owner") {
                condition->setOwner(childElement->GetText());
            }
            else if (elementName == "status") {
                condition->setStatus(childElement->GetText());
            }
            else if (elementName == "object") {
                condition->setObject(childElement->GetText());
            }
            else    {
                std::cout << "condition child has attribute name: " << elementName << std::endl;
            }
        }
    }

	return condition;
}


Attack* XMLParser::parseAttack(TiXmlElement* element) {
    Attack* attack = new Attack();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
        TiXmlElement* childElement = node->ToElement();
        if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
            if (elementName == "print") {
                attack->setPrint(childElement->GetText()); 
			}
            else if (elementName == "action")  {
                attack->addAction(childElement->GetText()); 
            }
            else if (elementName == "condition") {
                Condition* condition = parseCondition(childElement); 
				if (condition != NULL) {
					attack->addCondition(condition); 
				}
            }
            else    {
                std::cout << "attack child has attribute name: " << elementName << std::endl;
            }
        }
    }
    
	return attack;
}


Turnon* XMLParser::parseTurnon(TiXmlElement* element) {
	Turnon* turnon = new Turnon();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
        TiXmlElement* childElement = node->ToElement();
        if (childElement != NULL) {
            std::string value = childElement->GetText();
            std::string elementName = childElement->ValueStr();
            turnon->setUsed();
            if (elementName == "print") {
                turnon->setPrint(value);
            }
            else if (elementName == "action") {
                turnon->setAction(value);
            }
            else    {
                std::cout << "turnon child has attribute name: " << elementName << std::endl;
            }
        }
    }

	return turnon;
}



Container* XMLParser::parseContainer(TiXmlElement* element) {
	// create new item
	Container* container = new Container();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
        	if (elementName == "name") {
				container->setName(childElement->GetText()); 
			}
            else if (elementName == "status") {
                container->setStatus(childElement->GetText());
			}
            else if (elementName == "accept") {
                container->addAccept(childElement->GetText()); 
			}
            else if (elementName == "trigger") {
                Trigger* trigger = parseTrigger(childElement);
				if (trigger != NULL) {
					container->addTrigger(trigger); 
				}
            }
            else if (elementName == "item") {
                container->addItem(childElement->GetText());
			}
            else    {
                std::cout << "container child has attribute name: " << elementName << std::endl;
            }
		}
	}

	return container;
}



std::tuple<std::string, std::string> XMLParser::parseBorder(TiXmlElement* element) {
	// create new borer
    std::string borderName, direction;

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
            std::string value = childElement->GetText();
            std::string elementName = childElement->ValueStr();
        	if (elementName == "name") {
				borderName = value; 
			}
            else if (elementName == "direction") {
                direction = value;
			}
            else    {
                std::cout << "border child has attribute name: " << elementName << std::endl;
            }
		}        
	}

	return std::tuple<std::string, std::string> (borderName, direction);
}



Trigger* XMLParser::parseTrigger(TiXmlElement* element) {
    Trigger* trigger = new Trigger();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
        TiXmlElement* childElement = node->ToElement();
        if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
            if (elementName == "type") {
                trigger->setType(childElement->GetText()); 
			}
            else if (elementName == "command")  {
                trigger->setCommand(childElement->GetText()); 
            }
            else if (elementName == "print")    {
                trigger->setPrint(childElement->GetText());              
            }
            else if (elementName == "action")    {
                trigger->addAction(childElement->GetText());              
            }
            else if (elementName == "condition") {
                Condition* condition = parseCondition(childElement); 
				if (condition != NULL) {
					trigger->addCondition(condition); 
				}
            }
            else    {
                std::cout << "trigger child has attribute name: " << elementName << std::endl;
            }
        }
    }


	return trigger;
}

Creature* XMLParser::parseCreature(TiXmlElement* element) {
	// create new item
	Creature* creature = new Creature();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
        	if (elementName == "name") {
				creature->setName(childElement->GetText()); 
			}
            else if (elementName == "vulnerability") {
                creature->addVulnerability(childElement->GetText());
			}
            else if (elementName == "trigger") {
                Trigger* trigger = parseTrigger(childElement);
				if (trigger != NULL) {
					creature->addTrigger(trigger); 
				}
            }
            else if (elementName == "attack") {
                Attack* attack = parseAttack(childElement); // need to write
				if (attack != NULL) {
					creature->setAttack(attack);  
				}
            }
            else    {
                std::cout << "creature child has attribute name: " << elementName << std::endl;
            }
		}
	}

	return creature;
}



Item* XMLParser::parseItem(TiXmlElement* element) {
	// create new item
	Item* item = new Item();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
        	if (elementName == "name") {
				item->setName(childElement->GetText()); 
			}
            else if (elementName == "writing") {
                item->setWriting(childElement->GetText());
			}
            else if (elementName == "status") {
                item->setStatus(childElement->GetText()); 
			}
            else if (elementName == "turnon") {
                Turnon* turnon = parseTurnon(childElement); // need to write
				if (turnon != NULL) {
					item->setTurnon(turnon);  
				}
            }
            else    {
                std::cout << "item child has attribute name: " << elementName << std::endl;
            }
		}
	}

	return item;
}


Room* XMLParser::parseRoom(TiXmlElement* element) {
	// create new room
	Room* room = new Room();

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
            std::string elementName = childElement->ValueStr();
        	if (elementName == "name") {
				room->setName(childElement->GetText());
			}
            else if (elementName == "item") {
                room->addItem(childElement->GetText());
			}
            else if (elementName == "type") {
                room->setType(childElement->GetText()); 
			}
            else if (elementName == "container") {
                room->addContainer(childElement->GetText()); 
            }
            else if (elementName == "description") {
                room->setDescription(childElement->GetText()); 
            }
            else if (elementName == "trigger") {
                Trigger* trigger = parseTrigger(childElement);
				if (trigger != NULL) {
					room->addTrigger(trigger); 
				}
            }
            else if (elementName == "border") {
                std::string borderName, direction;
                std::tuple<std::string, std::string> temp;
                temp = parseBorder(childElement);
                borderName = std::get<0>(temp);
                direction = std::get<1>(temp);
				room->addBorder(borderName, direction); 
            }
            else if (elementName == "creature") {
                room->addCreature(childElement->GetText()); 
			}
            else    {
                std::cout << "room child has attribute name: " << elementName << std::endl;
            }
		}
	}

	return room;
}

void XMLParser::parseGame(Game &game, TiXmlElement* element) {

	// this method of iterating child nodes uses the IterateChildren method as recommended in the TinyXML docs. It is overall the most compact, but it requires a complex while loop condition
	// I would advise against using this unless you understand exactly what it is doing
	// parseCourse shows this same method written as a for loop which might help with understanding this method
	// alternatively, parseStudent shows a cleaner for loop approach using FirstChild and NextSibling to iterate a linked list of child nodes
	TiXmlNode* node = NULL;
	while ((node = element->IterateChildren(node)) != NULL) {
		// this function will cast the node if its a TiXmlElement, or returh NULL if it is not
		// there is also a ToText function to get a TiXmlText, which represents raw text inside an XML element
		TiXmlElement* childElement = node->ToElement();

        // ADD ALL OF THESE PARSING FUNCTIONS
		if (childElement->ValueStr() == "room") {
			game.rooms.push_back(parseRoom(childElement));
		}

        else if (childElement->ValueStr() == "item") {
			game.items.push_back(parseItem(childElement));
		}

        else if (childElement->ValueStr() == "container") {
			game.containers.push_back(parseContainer(childElement));
		}

        else if (childElement->ValueStr() == "creature") {
			game.creatures.push_back(parseCreature(childElement)); // need to write
		}
        else    {
                std::cout << "game child has attribute name: " << childElement->ValueStr() << std::endl;
            }
	}

	return;
}

/**
 * Parses the XML file for the given filename. Returns a vector of students if successful
 * If failed, prints an error and returns an empty vector
 */
void XMLParser::parseXML(Game &game, std::string filename) {
	// start parsing XML, we first need to create a TiXmlDocument and read it
	TiXmlDocument doc(filename);
	doc.LoadFile();

	// fetch the top level element, this should be the students array
	TiXmlElement* rootElement = doc.RootElement();
	// null check handles the case where the filename is not a valid XML file
	// there may be a way to get more info (determine whether the file is missing or just contains invalid XML), but for the example this is good enough
	if (rootElement == NULL) {
		std::cerr << "Invalid XML file, contains no data" << std::endl;
		return;
	}
	// this validation is not strictly needed, but its can help avoid the problem of accidently using an XML file from the wrong source
	if (rootElement->ValueStr() != "map") {
		std::cerr << "Invalid XML file, should start with a map" << std::endl;
		return;
	}
	// found the proper root element, so call the relevant parsing function
	parseGame(game, rootElement);
}
