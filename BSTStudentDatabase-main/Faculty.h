/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is the Faculty class that stores Faculty data.
*/
#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include <list>

class Faculty{
public:
  int id;
  std::string name;
  std::string level;
  std::string department;
  std::list<int> advisees;
  //all the same as Student
  Faculty() : id(0), name(""), level(""), department(""), advisees() {}
  Faculty(int id, std::string name, std::string level, std::string department, std::list<int> advisees) : id(id), name(name), level(level), department(department),advisees(advisees) {}

  Faculty(const Faculty& other)
    : id(other.id), name(other.name), level(other.level), department(other.department), advisees(other.advisees) {}

  Faculty& operator=(const Faculty& other) {
          if (this != &other) {
              id = other.id;
              name = other.name;
              level = other.level;
              department = other.department;
              advisees = other.advisees;
          }
          return *this;
  }
  bool operator==(const Faculty& other) const {
    return id == other.id;
  }
  bool operator<(const Faculty& other) const {
    return id < other.id;
  }
  bool operator>(const Faculty& other) const {
    return id > other.id;
  }
  bool operator!=(const Faculty& other) const {
        return id != other.id;
  }
  friend std::ostream& operator<<(std::ostream& os, const Faculty& faculty) {
    os << "ID: " << faculty.id
       << ", Name: " << faculty.name
       << ", Level: " << faculty.level
       << ", Department: " << faculty.department
       << ", Advisee IDs: ";
    for(int advisee : faculty.advisees){
      os << advisee << " ";
    }
    return os;
  }
};
#endif
