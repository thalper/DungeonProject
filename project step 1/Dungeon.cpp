#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XMLParser.h"


int main(int argc, char** args) {
   // prompt for XML file to parse
	std::string filename;
	bool shouldPause = true;

	// if given a second argument, use that as the XML file
	// means calling "XMLParseDemo studentActivity.xml" will parse the file "studentActivity.xml". The Makefile is set up to supply this argument when using on command line
	if (argc >= 2) {
		filename = args[1];
		shouldPause = false;
	}
	else {
		// if no argument, prompt for filename. This is the form used in running in Visual Studio
		std::cout << "Enter filename: ";
		std::cin >> filename;
		// remove the extra newline character from cin
		std::cin.get();
	}

    XMLParser parser;
    Game game;
    parser.parseXML(game, filename);
	game.printGame();
	
    if (shouldPause) std::cin.get();

	return 0;
}