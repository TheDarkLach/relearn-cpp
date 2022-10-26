#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(){
    next = NULL;
}

Node::~Node(){
  delete student;
}

void Node::setStudent(Student* newStudent){
    student = newStudent;
}

Student* Node::getStudent(){
    return student;
}

void Node::setNext(Node* newNode){
    next = newNode;
}

Node* Node::getNode(){
    return next;
}
