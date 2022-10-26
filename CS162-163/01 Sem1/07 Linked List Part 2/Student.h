#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
public:
  char* getfirstname();
  char* getlastname();
  int* getID();
  float* getGPA();
private:
  char firstname[10];
  char lastname[10];
  int ID;
  float GPA;
};

#endif 
