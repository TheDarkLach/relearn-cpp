#include <iostream>
#include "Student.h"

using namespace std;

char* Student::getfirstname(){
    return firstname;
}

char* Student::getlastname(){
    return lastname;
}

int* Student::getID(){
    return &ID;
}

float* Student::getGPA(){
    return &GPA;
}

