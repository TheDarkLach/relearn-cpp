#include <stdio.h>
#include <iostream>
#include <cstring>

#include "media.h"
#include "game.h"

using namespace std;

//:: - Is an element of
Media::Media(){
	cout << "The Media was created";
};

int getType(){
  return 0;
}

char* getTitle(){
  return title;
  //Same as return &title[0]
}

 int getYear(){
  return year;
}

void setYear(int newYear){
  year = newYear;
}

void setTitle(char* newTitle){
  strcpy(title,newTitle);
}
