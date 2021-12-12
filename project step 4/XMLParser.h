#pragma once
#include <vector>
#include <string>
#include <tuple>
#include "tinyxml.h"
#include "game.h"


// The way this class is set up, you could easily use static methods or non-class C functions.
// I choose to use functions in a class to use something familar
class XMLParser {
private:
	void parseGame(Game &game, TiXmlElement* element);
    Room* parseRoom(TiXmlElement* element);
	Trigger* parseTrigger(TiXmlElement* element);
	Condition* parseCondition(TiXmlElement* element);
	Item* parseItem(TiXmlElement* element);
    std::tuple<std::string, std::string> parseBorder(TiXmlElement* element);
    Container* parseContainer(TiXmlElement* element);
    Turnon* parseTurnon(TiXmlElement* element);
    Creature* parseCreature(TiXmlElement* element);
    Attack* parseAttack(TiXmlElement* element);

public:
	/**
	 * Parses the given XML file as a list of students. The caller is responsible for freeing the memory associated with the students
	 * Note the return type does not have to be a vector, you can write a parsing method to return any object type you wish
	 */
	void parseXML(Game &game, std::string filename);
};

