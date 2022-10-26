//Header Guard
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
public:
  char* getfirstname();
  char* getlastname();
  int* getid();
  float* getgpa();
  ~Student();
private:
  char firstname[10];
  char lastname[10];
  int id;
  float gpa;
};

#endif 
