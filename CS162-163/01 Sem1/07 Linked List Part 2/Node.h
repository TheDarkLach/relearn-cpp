#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Student.h"

class Node
{
 public:
  Node();
  ~Node();
  void setStudent(Student* newStudent);
  Student* getStudent();
  void setnext(Node* newnext);
  Node* getnext();
 private:
  Student* student;
  Node* next;
};
#endif
