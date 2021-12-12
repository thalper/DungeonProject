#include "Student.h"

Student::~Student() {
	for (Activity* activity : activities) {
		delete activity;
	}
	activities.clear();
}

void Student::setName(std::string name) {
	this->name = name;
}

void Student::addActivity(Activity* activity) {
	activities.push_back(activity);
}

std::string Student::getName() {
	return name;
}

std::vector<Activity*> Student::getActivities() {
	return activities;
}
