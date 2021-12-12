#include <string>
#include <vector>
#include <iostream>
#include "XMLParser.h"
#include "tinyxml.h"

// for a couple of concepts in parsing, TinyXML converts an XML file into a tree structure containing nodes
// a node for our uses will either be an element node (for example, <Student>...</Student>) or a text node (the "Prof. Midkiff" in <name>Prof. Midkiff</name>)

// in parsing the XML file, there are a few cases where there are multiple methods to perform the same task, so I tried to show both ways in this code
// in those cases, there should be comments pointing to the other methods to perform the task, so choose whichever method you like the best

Course* XMLParser::parseCourse(TiXmlElement* element) {
	// there are two different ways to parse the values contained in nested elements
	// this function iterates all the elements child nodes nodes, and if an element matches one of the expected names then set the cooresponding attribute
	// see parseClub for the other method
	Course* course = new Course();

	// iterate child nodes using IterateChildren in a for loop. This method is a bit more verbose than the while loop used by `parseStudents`, but it is also much easier to read
	// `parseStudent` shows a cleaner way of using a for loop via FirstChild and NextSibling instead. You could also mix the two methods, using FirstChild and IterateChildren for instance
	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// ValueStr gets the name of the element type
			std::string name = childElement->ValueStr();
			// this method gets the text contained inside the node
			std::string value = childElement->GetText();

			// need a condition for each attribute we want to parse. Any unknown attributes are ignored
			if (name == "instructor") {
				course->setInstructor(value);
			}
			else if (name == "credit") {
				course->setCredit(std::stoi(value));
			}
			else if (name == "name") {
				course->setName(value);
			}
			else if (name == "meetingTime") {
				course->setMeetingTime(value);
			}
			else if (name == "meetingDay") {
				course->setMeetingDay(value);
			}
			else if (name == "number") {
				course->setNumber(value);
			}
			else if (name == "location") {
				course->setLocation(value);
			}
		}
	}

	return course;
}

/**
 * Helper function to get the text contained within the element with the given name
 * If the passed element has a child element with the given name, this method returns the text contained in the element
 * If the passed element does not have a child element with the given name, or the child has no text, an empty string is returned
 */
std::string getTextFromNamedChild(TiXmlElement* element, std::string name) {
	TiXmlElement* child = element->FirstChildElement(name);
	if (child != NULL) {
		// we could use GetText instead of getting the child and calling ToText, but I wanted to show another method of parsing the child node
		TiXmlNode* grandchild = child->FirstChild();
		if (grandchild != NULL) {
			// similar to ToElement, this returns null if the node is not a text node
			TiXmlText* text = grandchild->ToText();
			if (text != NULL) {
				return text->ValueStr();
			}
		}
	}
	return "";
}

Club* XMLParser::parseClub(TiXmlElement* element) {
	Club* club = new Club();

	// there are two different ways to parse the attributes in nested elements
	// this function uses the method to fetch a child element by name, if present
	club->setName(getTextFromNamedChild(element, "name"));
	club->setMeetingDay(getTextFromNamedChild(element, "meetingDay"));
	club->setMeetingTime(getTextFromNamedChild(element, "meetingTime"));
	club->setLocation(getTextFromNamedChild(element, "location"));

	return club;
}

Activity* XMLParser::parseActivity(TiXmlElement* element) {
	// activity has two different subclasses, which are selected based on the type attribue
	std::string type = element->Attribute("type");
	if (type == "course") {
		return parseCourse(element);
	}
	if (type == "club") {
		return parseClub(element);
	}
	return NULL;
}

Student* XMLParser::parseStudent(TiXmlElement* element) {
	// fetch the name attribute as a string, if defined 
	Student* student = new Student();
	student->setName(element->Attribute("name"));

	// if we wanted, we could make use of activities to set sizes for arrays and alike
	// however, for this example we are just using vectors which resize automatically so its not needed
	int numActivities = -1;
	element->Attribute("numActivities", &numActivities);

	// this is the method of iterating nodes that is the cleanest in my opinion. Essentially nodes in TinyXML are a linked list, so we are iterating through a linked list
	// parseStudents shows how to iterate decendents using the element IterateChildren method, which is more compact but also harder to read
	for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
		// the ToElement function returns null if the node is not an element
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// if the element type is one we recognize, handle with the proper function
			// note with more if statements, we could parse multiple different child types, for instance we could include Address or Advisor as another element nested inside Student
			if (childElement->ValueStr() == "Activity") {
				// if we successfully parse an activity, add it to the student
				Activity* activity = parseActivity(childElement);
				if (activity != NULL) {
					student->addActivity(activity);
				}
			}
		}
	}

	if ((unsigned int)numActivities != student->getActivities().size()) {
		std::cerr << "Wrong number of activities parsed for student " << student->getName() << std::endl;
	}

	return student;
}

std::vector<Student*> XMLParser::parseStudents(TiXmlElement* element) {
	std::vector<Student*> students;

	// this method of iterating child nodes uses the IterateChildren method as recommended in the TinyXML docs. It is overall the most compact, but it requires a complex while loop condition
	// I would advise against using this unless you understand exactly what it is doing
	// parseCourse shows this same method written as a for loop which might help with understanding this method
	// alternatively, parseStudent shows a cleaner for loop approach using FirstChild and NextSibling to iterate a linked list of child nodes
	TiXmlNode* node = NULL;
	while ((node = element->IterateChildren(node)) != NULL) {
		// this function will cast the node if its a TiXmlElement, or returh NULL if it is not
		// there is also a ToText function to get a TiXmlText, which represents raw text inside an XML element
		TiXmlElement* childElement = node->ToElement();
		if (childElement->ValueStr() == "Student") {
			students.push_back(parseStudent(childElement));
		}
	}

	return students;
}

/**
 * Parses the XML file for the given filename. Returns a vector of students if successful
 * If failed, prints an error and returns an empty vector
 */
std::vector<Student*> XMLParser::parseXML(std::string filename) {
	// start parsing XML, we first need to create a TiXmlDocument and read it
	TiXmlDocument doc(filename);
	doc.LoadFile();

	// fetch the top level element, this should be the students array
	TiXmlElement* rootElement = doc.RootElement();
	// null check handles the case where the filename is not a valid XML file
	// there may be a way to get more info (determine whether the file is missing or just contains invalid XML), but for the example this is good enough
	if (rootElement == NULL) {
		std::cerr << "Invalid XML file, contains no data" << std::endl;
		return std::vector<Student*>();
	}
	// this validation is not strictly needed, but its can help avoid the problem of accidently using an XML file from the wrong source
	if (rootElement->ValueStr() != "Students") {
		std::cerr << "Invalid XML file, should start with a Students array" << std::endl;
		return std::vector<Student*>();
	}
	// found the proper root element, so call the relevant parsing function
	return parseStudents(rootElement);
}
