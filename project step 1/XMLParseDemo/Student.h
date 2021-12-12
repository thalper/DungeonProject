#pragma once
#include <string>
#include <vector>
#include "Activity.h"

class Student {
private:
	std::string name;
	std::vector<Activity*> activities;

public:
	virtual ~Student();

	void setName(std::string name);
	void addActivity(Activity* activity);
	std::string getName();
	std::vector<Activity*> getActivities();
};

