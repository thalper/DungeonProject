#include "Course.h"
#include <iostream>

void Course::setCredit(int credit) {
	this->credit = credit;
}

void Course::setInstructor(std::string instructor) {
	this->instructor = instructor;
}

void Course::setNumber(std::string number) {
	this->number = number;
}

int Course::getCredit() {
	return credit;
}

std::string Course::getInstructor() {
	return instructor;
}

std::string Course::getNumber() {
	return number;
}


void Course::printData(std::string prefix) {
	std::cout << prefix << "Course" << std::endl;
	std::cout << prefix << "  Name: " << this->getName() << std::endl;
	std::cout << prefix << "  Instructor: " << this->getInstructor() << std::endl;
	std::cout << prefix << "  Number: " << this->getNumber() << std::endl;
	std::cout << prefix << "  Credits: " << this->getCredit() << std::endl;
	std::cout << prefix << "  Meeting Day: " << this->getMeetingDay() << std::endl;
	std::cout << prefix << "  Meeting Time: " << this->getMeetingTime() << std::endl;
	std::cout << prefix << "  Location: " << this->getLocation() << std::endl;
}