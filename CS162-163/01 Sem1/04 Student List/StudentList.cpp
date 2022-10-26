/*
 * Author: Zareef Amyeen
 * Date: September 24th, 2018
 * Student List Project is an example of use of vectors and pointers
 * This project lets you use user input and from that user input you get to choose whether or not you want to add, print, delete or quit
 * The add prompt will add a student into the vector and will ask you for first name, last name, id, and gpa
 * The print prompt will print the students informations
 * The delete prompt will delete a student dependent on ID because no two students have the same ID
 * The quit prompt will exit you out of the game
 * Let's Learn C++ ~ Basics: 5 of 14 ~ References & Pointers: https://www.youtube.com/watch?v=DvUYbUn9uQ4 
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

//Extra information about Structs came from: https://www.youtube.com/watch?v=DBQzxCHk9uI
//Intro to C++: Structs
struct Student {
  char firstname[10];
  char lastname[10];
  int id;
  float gpa;
};

void printStudent (Student person);
void constructorStudent(Student& person, char firstname[10], char lastname[10], int id, float gpa);
void printArray(char array[100]);
void addStudent(vector<Student*> &StudentClass);
void printClass(vector<Student*> StudentClass);
void deleteStudent(vector<Student*> &StudentClass);

int main (){
  bool stillPlaying = true;
  vector<Student*> StudentClass;
  while(stillPlaying){
    char input[100];
    printf("Please enter one of the following options:\nADD\nDELETE\nPRINT\nQUIT\n");
    cin >> input;
    printf("Input is: \'");
    printArray(input);
    printf("\'\n");
    //These if Statements run the Game
    if (strcmp(input,"ADD") == 0){
      printf("ADDED\n");
      addStudent(StudentClass);
    }
    else if (strcmp(input,"DELETE") == 0){
      printf("DELETED\n");
      deleteStudent(StudentClass);
    }
    else if (strcmp(input,"PRINT") == 0){
      printf("PRINTED\n");
      printClass(StudentClass);
    }
    //End Game if QUIT is inputted
    else if (strcmp(input,"QUIT") == 0){
      stillPlaying = false;
      printf("Program has ended\n");
    }
  }
  return 0;
}

//From Example
void printStudent (Student person){
  cout << "First Name: " <<  person.firstname <<
   endl << "Last Name: " << person.lastname <<
    endl << "ID: " << person.id <<
    endl;
  printf("GPA: %.2f\n",person.gpa);
}

//From Example
void constructorStudent (Student& person, char firstname[10], char lastname[10],int id, float gpa){
  strcpy(person.firstname,firstname);
  strcpy(person.lastname,lastname);
  person.id = id;
  person.gpa = gpa;
}

//This method makes printing Arrays simple
void printArray(char array[10]){
  for (int i = 0; i < strlen(array);i++){
    printf("%c",array[i]);
  }
}

//returns Student pointer (which you will add into the vector of Student Pointers)
 void addStudent(vector<Student*> &StudentClass){
  Student* Sptr = new Student;
  printf("Enter Student's First Name:\n");
  cin >> (*Sptr).firstname;
  printf("Enter Student's Last Name:\n");
  cin >> (*Sptr).lastname;
  printf("Enter Student's ID:\n");
  cin >> (*Sptr).id;
  printf("Enter Student's GPA:\n");
  cin >> (*Sptr).gpa;
  StudentClass.push_back(Sptr);
}

//This method prints the vector using iterators
void printClass (vector<Student*> StudentClass) {
  for (vector<Student*>::iterator Sptr = StudentClass.begin(); Sptr != StudentClass.end(); ++Sptr){
    printf("\nStudent's First Name:");
    printArray((*Sptr) -> firstname);
    printf("\nStudent's Last Name:");
    printArray((*Sptr) ->lastname);
    printf("\nStudent's ID:%d\nStudent's GPA:%.2f\n",(*Sptr) -> id,(*Sptr) -> gpa);
  }
}

//This method deletes a Student from the vector, after asking for the ID that should be removed
void deleteStudent (vector<Student*> &StudentClass){
  printf("Enter the ID of the Student you want to Delete from the Class:\n");
  int ID;
  cin >> ID;
  int PositionInVector = 0;
  for (vector<Student*>::iterator Sptr = StudentClass.begin(); Sptr != StudentClass.end(); ++Sptr){
    if((*Sptr) -> id == ID){
      StudentClass.erase(StudentClass.begin() + PositionInVector);
      break;
    }
    else{
      PositionInVector++;
    }
  }
}
