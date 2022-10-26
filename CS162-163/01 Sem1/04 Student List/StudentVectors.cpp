#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

const char QUIT[4] = {'Q', 'U', 'I', 'T'};
const char ADD[3] = {'A', 'D', 'D'};
const char DELETE[6] = {'D', 'E', 'L', 'E', 'T', 'E'};
const char PRINT[5] = {'P', 'R', 'I', 'N', 'T'};

//Extra information about Structs came from: https://www.youtube.com/watch?v=DBQzxCHk9uI
//Intro to C++: Structs
struct Student {
  char firstname[10];
  char lastname[10];
  int id;
  float gpa;
};

void printArray(char array[10]);

int main(){
  //Format: vector<DataType> nameOfVector
  //myVector.push_back(value) --> adds an element to the END of the vector (also resizes it)
  //myVector.at(index) --> return element at specified index number
  //myVector.size() --> returns an unsigned int equal to the number of elements
  //myVector.begin() --> reads vector from first element (index 0)
  //myVector.insert(myVector.begin() + integer, new value)
  vector <Student*> Class;
  //Student S;
  //Student* Sptr = &S;
  Student* Sptr = new Student;
  printf("Enter Student's First Name:\n");
  cin >>(*Sptr).firstname;
  printf("Enter Student's Last Name:\n");
  cin >>(*Sptr).lastname;
  printf("Enter Student's ID:\n");
  cin >> (*Sptr).id;
  printf("Enter Student's GPA:\n");
  cin >> (*Sptr).gpa;
  printf("\nStudent's First Name:");
  printArray((*Sptr).firstname);
  printf("\nStudent's Last Name:");
  printArray((*Sptr).lastname);
  printf("\nStudent's ID:%d\nStudent's GPA:%.2f\n",(*Sptr).id,(*Sptr).gpa);
}

void printArray(char array[100]){
  for (int i = 0; i < strlen(array);i++){
    printf("%c",array[i]);
  }
}
