#include <iostream>

#include "Node.h"
#include "Student.h"

using namespace std;

int main(){
  
  Student* newStudent = new Student;//Creates a new Student on the Heap

  cout << "First Name: ";
  cin.get(newStudent->getfirstname(),11);
  cin.clear();
  cin.ignore(10000,'\n');
  

  cout << "Last Name: ";
  cin.get(newStudent->getlastname(),11);
  cin.clear();
  cin.ignore(10000,'\n');
  
  
  cout << "GPA: ";
  cin >> *newStudent->getgpa();

  cout << "ID: ";
  cin >> *newStudent->getid();

  cout << "First Name is: " << newStudent->getfirstname() << endl;
  cout << "Last Name is: " << newStudent->getlastname() << endl;
  printf("GPA is: %.2f\n", *newStudent->getgpa());
  cout << "ID is: " << *newStudent->getid() << endl << "END OF FIRST STUDENT" << endl;

  Student* newSecondStudent = new Student;//Creates a new Student on the Heap
  
  cin.clear();
  cin.ignore(10000, '\n');
  
  cout << "First Name: ";
  cin.get(newSecondStudent->getfirstname(),11);
  cin.clear();
  cin.ignore(10000,'\n');

  cout << "Last Name: ";
  cin.get(newSecondStudent->getlastname(),11);
  cin.clear();
  cin.ignore(10000,'\n');
  
  cout << "GPA: ";
  cin >> *newSecondStudent->getgpa();  
  
  cout << "ID: ";
  cin >> *newSecondStudent->getid();

  cout << "First Name is: " << newSecondStudent->getfirstname() << endl;
  cout << "Last Name is: " << newSecondStudent->getlastname() << endl;
  printf("GPA is: %.2f\n", *newSecondStudent->getgpa());
  cout << "ID is: " << *newSecondStudent->getid();
  Node* newNode = new Node();
  
  newNode->setStudent(newStudent);

  Node* newSecondNode = new Node();

  newSecondNode->setStudent(newSecondStudent);
  newNode->setNext(newSecondNode);
  
  cout << "\nEND\n";
}
