/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is the header file for the database..
*/
#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include "Faculty.h"
#include "LazyBST.h"
#include <iostream>
#include <string>
#include <list>

class Database {
public:
  Database();
  ~Database();
  void printStudentsAscending();
  void printFacultyAscending();
  void displayStudentInfo(int studentid);
  void displayFacultyInfo(int facultyid);
  void addStudent();
  void deleteStudent(int id);
  void addFaculty();
  void deleteFaculty(int id);
  void changeAdvisor(int studentid, int facultyid);
  void removeAdvisee(int studentid, int facultyid);
  void studentsOutput();
  void studentsOutputHelper(TreeNode<Student>* n, std::ofstream& file);
  void facultyOutput();
  void facultyOutputHelper(TreeNode<Faculty>* n, std::ofstream& file);
  void createOutput();
  void system();
private:
  LazyBST<Student> studentBST;
  LazyBST<Faculty> facultyBST;
};
#endif
