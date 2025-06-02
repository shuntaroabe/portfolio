/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is the implementation of the Database, which manages Students and Faculty data.
*/
#include "Student.h"
#include "Faculty.h"
#include "LazyBST.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

#include "Database.h"

Database::Database() {}

Database::~Database() {}

//option 1
void Database::printStudentsAscending() {
    if(studentBST.size() == 0){
      std::cout << "No students to be printed." << std::endl;
    }
    studentBST.printInOrder();
    return;
}
//option 2
void Database::printFacultyAscending() {
    if(facultyBST.size() == 0){
      std::cout << "No faculty to be printed." << std::endl;
    }
    facultyBST.printInOrder();
    return;
}
//option 3
void Database::displayStudentInfo(int studentid) {
    Student* student = studentBST.get(studentid);
    if(student == nullptr){
      std::cout << "Student not found." << std::endl;
    }
    else{
      std::cout << *student << std::endl;
    }
    return;
}
//option 4
void Database::displayFacultyInfo(int facultyid) {
    Faculty* faculty = facultyBST.get(facultyid);
    if(faculty == nullptr){
      std::cout << "Faculty not found." << std::endl;
    }
    else{
      std::cout << *faculty << std::endl;
    }
    return;
}
//option 5
void Database::addStudent() {
  int id;
  std::string name;
  std::string level;
  std::string major;
  double gpa;
  int advisor;

  std::cout << "Enter student ID: ";
  std::cin >> id;

  std::cin.ignore();

  std::cout << "Enter student name: ";
  std::getline(std::cin, name);

  std::cout << "Enter student level: ";
  std::getline(std::cin, level);

  std::cout << "Enter student major: ";
  std::getline(std::cin, major);

  std::cout << "Enter student GPA: ";
  std::cin >> gpa;

  std::cout << "Enter advisor ID: ";
  std::cin >> advisor;

  Faculty* theirAdvisor = facultyBST.get(advisor);
  if(theirAdvisor == nullptr){
    std::cout << "Advisor with id " << advisor << "not found. Cancelling Student creation." << std::endl;
  }
  else{
    Student newStudent(id, name, level, major, gpa, advisor);
    studentBST.insert(newStudent);

    theirAdvisor->advisees.push_back(id);
    std::cout << "Student added successfully. Student added to " << advisor << "advisee list." << std::endl;
  }
}
//option 6
void Database::deleteStudent(int id) {
  Student* student = studentBST.get(id);
  if(student == nullptr){
    std::cout << "Student with ID " << id << " not found." << std::endl;
    return;
  }
  int advisorID = student->advisor;
  //std::cout << "SEG FAULT B4 STUDENTBSTREMOVE" << std::endl;
  studentBST.remove(*student);

  Faculty* advisor = facultyBST.get(advisorID);
  if(advisor != nullptr){
    //std::cout << "B4 ADVISEES REMOVE" << std::endl;
    advisor->advisees.remove(id);
    //std::cout << "AFTER ADVISEES REMOVE" << std::endl;
    std::cout << "Student removed successfully. Also removed from advisor's advisee list." << std::endl;
  }
  else{
    std::cout << "Student removed successfully. Advisor not found." << std::endl;
  }
}
//option 7
void Database::addFaculty() {
  int id;
  std::string name;
  std::string level;
  std::string department;
  std::list<int> advisees;
  int adviseeID;
  char yesorno;

  std::cout << "Enter faculty ID: ";
  std::cin >> id;
  std::cin.ignore();

  std::cout << "Enter faculty name: ";
  std::getline(std::cin, name);

  std::cout << "Enter faculty level: ";
  std::getline(std::cin, level);

  std::cout << "Enter faculty department: ";
  std::getline(std::cin, department);

  do {
    std::cout << "Enter advisees ID (enter 0, if 0/no more advisees): ";
    std::cin >> adviseeID;
    if(adviseeID == 0){
      std::cout << "0 entered. Stopping advisee entry. " << std::endl;
      break;
    }
    Student* theirStudent = studentBST.get(adviseeID);
    if(theirStudent !=nullptr){
      advisees.push_back(adviseeID);
      theirStudent->advisor = id;
      std::cout << "Student with id " << adviseeID << " added as advisee." << std::endl;
    }
    else{
      std::cout << "No student found with id" << adviseeID << std::endl;
      continue;
    }
    std::cout << "Enter Y to enter another advisee. Enter N to stop adding advisees: ";
    std::cin >> yesorno;
    std::cin.ignore();
  } while(yesorno == 'Y' || yesorno == 'y');

  Faculty newFaculty(id, name, level, department, advisees);
  facultyBST.insert(newFaculty);
  std::cout << newFaculty << std::endl;

  std::cout << "Faculty member added successfully." << std::endl;
}
//option 8
void Database::deleteFaculty(int id) {
  Faculty* faculty = facultyBST.get(id);
  if(faculty == nullptr){
    std::cout << "Faculty with ID" << id << " not found. " << std::endl;
    return;
  }
  std::list<int> advisees = faculty->advisees;
  facultyBST.remove(*faculty);
  for(int adviseeID : advisees){
    Student* student = studentBST.get(adviseeID);
    if(student != nullptr){
      int newAdvisorID = 0;
      Faculty* newAdvisor = facultyBST.min();
      if(newAdvisor != nullptr && newAdvisor->id != id){
        newAdvisorID = newAdvisor->id;
      }
      student->advisor = newAdvisorID;
      std::cout << "Student with ID " << adviseeID << "had advisor changed to ID " << newAdvisorID << std::endl;
    }
  }
  std::cout << "Faculty deleted successfully" << std::endl;
}
//option 9
void Database::changeAdvisor(int studentid, int facultyid) {
    Student* student = studentBST.get(studentid);
    if(student == nullptr){
      std::cout << "Student with id" << studentid << " not found. " << std::endl;
      return;
    }
    Faculty* faculty = facultyBST.get(facultyid);
    if(faculty == nullptr){
      std::cout << "Faculty with id" << facultyid << " not found. " << std::endl;
      return;
    }
    int oldAdvisorID = student->advisor;
    Faculty* oldAdvisor = facultyBST.get(oldAdvisorID);
    if(oldAdvisor != nullptr){
      oldAdvisor->advisees.remove(studentid);
      std::cout << "Student with id" << studentid << " removed from old advisor's advisee list." << std::endl;
    }
    student->advisor = facultyid;
    std::cout << "Advisor for student " << studentid << "changed to advisor id " << facultyid << std::endl;
    faculty->advisees.push_back(studentid);
}
//option 0
void Database::removeAdvisee(int studentid, int facultyid) {
    Faculty* faculty = facultyBST.get(facultyid);
    if(faculty == nullptr){
      std::cout << "Faculty with ID " << facultyid << " not found." << std::endl;
      return;
    }
    std::list<int>& advisees = faculty->advisees;
    if(std::find(advisees.begin(),advisees.end(),studentid) == advisees.end()){
      std::cout << "Student with id " << studentid << "is not an advisee of advisor with id " << facultyid << std::endl;
      return;
    }
    advisees.remove(studentid);
    std::cout << "Student removed from advisee list. " << std::endl;
    Student* student = studentBST.get(studentid);
    if(student != nullptr){
      int newAdvisorID = 0;
      student->advisor = newAdvisorID;
      Faculty* newAdvisor = facultyBST.min();
      if(newAdvisor != nullptr && newAdvisor->id != facultyid){
        newAdvisorID = newAdvisor->id;
      }
      student->advisor = newAdvisorID;
      std::cout << "Student with ID " << studentid << "had advisor changed to ID " << newAdvisorID << std::endl;
    }
}

void Database::studentsOutput(){
  std::ofstream file("log.txt",std::ios::app);
  if(studentBST.size() == 0){
    file << "No students in the database.\n";
  }
  else{
    file << "Students:\n";
    studentsOutputHelper(studentBST.getRoot(),file);
  }
  file.close();
}
void Database::studentsOutputHelper(TreeNode<Student>* n, std::ofstream& file){
  if(n != nullptr){
    studentsOutputHelper(n->getLeft(),file);
    file << n->getData() << "\n";
    studentsOutputHelper(n->getRight(),file);
  }
}
void Database::facultyOutput(){
  std::ofstream file("log.txt",std::ios::app);
  if(facultyBST.size() == 0){
    file << "No faculty in the database.\n";
  }
  else{
    file << "Faculty:\n";
    facultyOutputHelper(facultyBST.getRoot(),file);
  }
  file.close();
}
void Database::facultyOutputHelper(TreeNode<Faculty>* n, std::ofstream& file){
  if(n!= nullptr){
    facultyOutputHelper(n->getLeft(),file);
    file << n->getData() << "\n";
    facultyOutputHelper(n->getRight(),file);
  }
}
void Database::createOutput(){ //outputs to file
  studentsOutput();
  facultyOutput();
}

void Database::system(){//the system
  while(true){
    std::cout << "Select an option:\n"
                      << "1. Print all students and their information (sorted by ascending id #)\n"
                      << "2. Print all faculty and their information (sorted by ascending id #)\n"
                      << "3. Find and display student information given the student id\n"
                      << "4. Find and display faculty information given the faculty id\n"
                      << "5. Add a new student (only if advisor exists)\n"
                      << "6. Delete a student given the id\n"
                      << "7. Add a new faculty member\n"
                      << "8. Delete a faculty member given the id\n"
                      << "9. Change a student’s advisor given the student id and the new faculty id\n"
                      << "10. Remove an advisee from a faculty member given the ids\n"
                      << "11. Exit\n"
                      << "Enter a #1-11: ";
    int choice;
    std::cin >> choice;
    switch(choice){
      case 1:
        printStudentsAscending();
        break;
      case 2:
        printFacultyAscending();
        break;
      case 3:
        int studentidC3;
        std::cout << "Enter the ID of student to display: " << std::endl;
        std::cin >> studentidC3;
        displayStudentInfo(studentidC3);
        break;
      case 4:
        int facultyidC4;
        std::cout << "Enter the ID of faculty to display: " << std::endl;
        std::cin >> facultyidC4;
        displayFacultyInfo(facultyidC4);
        break;
      case 5:
        addStudent();
        break;
      case 6:
        int studenttodeleteC6;
        std::cout << "Enter the ID of student to delete: " << std::endl;
        std::cin >> studenttodeleteC6;
        deleteStudent(studenttodeleteC6);
        break;
      case 7:
        addFaculty();
        break;
      case 8:
        int facultytodeleteC8;
        std::cout << "Enter the ID of faculty to delete: " << std::endl;
        std::cin >> facultytodeleteC8;
        deleteFaculty(facultytodeleteC8);
        break;
      case 9:
        int studentidC9;
        int newFacultyidC9;
        std::cout << "Enter the ID of Student to change: " << std::endl;
        std::cin >> studentidC9;
        std::cout << "Enter the ID of new Advisor" << std::endl;
        std::cin >> newFacultyidC9;
        changeAdvisor(studentidC9,newFacultyidC9);
        break;
      case 10:
        int studentidC10;
        int facultyidC10;
        std::cout << "Enter the ID of student to be removed: " << std::endl;
        std::cin >> studentidC10;
        std::cout << "Enter the ID of Faculty who will have an advisee removed: " << std::endl;
        std::cin >> facultyidC10;
        removeAdvisee(studentidC10,facultyidC10);
        break;
      case 11:
        createOutput();
        std::cout << "Output file 'log.txt' created. Exitting database." << std::endl;
        return;
    }
  }
}
