#pragma once
#include <string>

class Activity {
private:
	std::string name;
	std::string meetingDay;
	std::string meetingTime;
	std::string location;

public:
	// while unused in this example, note that the deconstructor is made virtual
	// this means calling delete on an Activity* will call the proper deconstructor from Club or Course if relevant
	virtual ~Activity();

	// Setters
	void setName(std::string name);
	void setMeetingDay(std::string day);
	void setMeetingTime(std::string time);
	void setLocation(std::string location);

	// Getters
	std::string getName();
	std::string getMeetingDay();
	std::string getMeetingTime();
	std::string getLocation();

	// prints the data stored in this object to cout, prefixing it for indentation
	virtual void printData(std::string prefix);
};

