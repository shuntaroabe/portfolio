/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is the Student class that stores Student data.
*/
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student{
public:
  int id;
  std::string name;
  std::string level;
  std::string majorField;
  double gpa;
  int advisor;
  Student() : id(0), name(""), level(""), majorField(""), gpa(0.0), advisor(0) {} //def con
  Student(int id, std::string name, std::string level, std::string majorField, double gpa, int advisor) : id(id), name(name), level(level), majorField(majorField), gpa(gpa), advisor(advisor) {}//overloaded con

  Student(const Student& other)//copy constructor
    : id(other.id), name(other.name), level(other.level), majorField(other.majorField), gpa(other.gpa), advisor(other.advisor) {}

  Student& operator=(const Student& other) { //assignment operator
    if (this != &other) {
        id = other.id;
        name = other.name;
        level = other.level;
        majorField = other.majorField;
        gpa = other.gpa;
        advisor = other.advisor;
    }
    return *this;
  }
  //below is all the overloaded operators
  bool operator==(const Student& other) const {
    return id == other.id;
  }
  bool operator<(const Student& other) const {
    return id < other.id;
  }
  bool operator>(const Student& other) const {
    return id > other.id;
  }
  bool operator!=(const Student& other) const {
        return id != other.id;
  }
  friend std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "ID: " << student.id
       << ", Name: " << student.name
       << ", Level: " << student.level
       << ", Major: " << student.majorField
       << ", GPA: " << student.gpa
       << ", Advisor ID: " << student.advisor;
    return os;
  }
};
#endif
