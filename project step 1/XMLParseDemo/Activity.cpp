#include "Activity.h"
#include <iostream>

Activity::~Activity() {
}

void Activity::setName(std::string name) {
	this->name = name;
}

void Activity::setMeetingDay(std::string day) {
	this->meetingDay = day;
}

void Activity::setMeetingTime(std::string time) {
	this->meetingTime = time;
}

void Activity::setLocation(std::string location) {
	this->location = location;
}

std::string Activity::getName() {
	return name;
}

std::string Activity::getMeetingDay() {
	return meetingDay;
}

std::string Activity::getMeetingTime() {
	return meetingTime;
}

std::string Activity::getLocation() {
	return location;
}

void Activity::printData(std::string prefix) {
	std::cout << prefix << "Activity" << std::endl;
	std::cout << prefix << "  Name: " << this->getName() << std::endl;
	std::cout << prefix << "  Meeting Day: " << this->getMeetingDay() << std::endl;
	std::cout << prefix << "  Meeting Time: " << this->getMeetingTime() << std::endl;
	std::cout << prefix << "  Location: " << this->getLocation() << std::endl;
}


