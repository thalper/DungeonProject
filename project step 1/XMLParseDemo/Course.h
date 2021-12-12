#pragma once
#include "Activity.h"
#include <string>

class Course : public Activity {
private:
	int credit = 0;
	std::string instructor;
	std::string number;

public:
	// setters
	void setCredit(int credit);
	void setInstructor(std::string instructor);
	void setNumber(std::string number);

	// getters
	int getCredit();
	std::string getInstructor();
	std::string getNumber();

	virtual void printData(std::string prefix);
};

