#include "Club.h"
#include <iostream>

void Club::printData(std::string prefix) {
	std::cout << prefix << "Club" << std::endl;
	std::cout << prefix << "  Name: " << this->getName() << std::endl;
	std::cout << prefix << "  Meeting Day: " << this->getMeetingDay() << std::endl;
	std::cout << prefix << "  Meeting Time: " << this->getMeetingTime() << std::endl;
	std::cout << prefix << "  Location: " << this->getLocation() << std::endl;
}
