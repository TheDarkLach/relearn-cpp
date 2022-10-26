#include <iostream>
#include "Student.h"

using namespace std;

char* Student::getfirstname(){
    return firstname;
}

char* Student::getlastname(){
    return lastname;
}

int* Student::getid(){
    return &id;
}

float* Student::getgpa(){
    return &gpa;
}

Student::~Student(){
	delete[] firstname;
	delete[] lastname;
}
