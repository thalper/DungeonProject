#pragma once
#include <vector>
#include <string>
#include "Activity.h"
#include "Course.h"
#include "Club.h"
#include "Student.h"
#include "tinyxml.h"

// The way this class is set up, you could easily use static methods or non-class C functions.
// I choose to use functions in a class to use something familar
class XMLParser {
private:
	/**
	 * Parses a list of students from the given element
	 * Expects the passed element to be a Students element, containing zero or more Student elements
	 */
	std::vector<Student*> parseStudents(TiXmlElement* element);

	/**
	 * Parses a student from the given element
	 * Expects the passed element to be a Student element, containing a name attribute and zero or more child activities
	 */
	Student* parseStudent(TiXmlElement* element);

	/**
	 * Parses an activity from the given element
	 * Expects the passed element to be an Activity element, containing a type attribute
	 */
	Activity* parseActivity(TiXmlElement* element);

	/**
	 * Parses a club from the given element
	 * Expects the passed element to be an Activity element, with a type attribute of "club"
	 */
	Club* parseClub(TiXmlElement* element);

	/**
	 * Parses a course from the given element
	 * Expects the passed element to be an Activity element, with a type attribute of "course"
	 */
	Course* parseCourse(TiXmlElement* element);

public:
	/**
	 * Parses the given XML file as a list of students. The caller is responsible for freeing the memory associated with the students
	 * Note the return type does not have to be a vector, you can write a parsing method to return any object type you wish
	 */
	std::vector<Student*> parseXML(std::string filename);
};

