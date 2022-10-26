//http://www.cplusplus.com/forum/beginner/129857/
#include <iostream>
#include "game.h"

using namespace std;

Game::Game(char* newTitle, int newYear, char* newPublisher /*Character Array Pointer*/,int newRating){
  title = newTitle;
  year = newYear;
  publisher = newPublisher;
  rating = newRating;
}

int Game::getType(){
  return 1;
}

char* Game::getTitle(){
  return title;
}

int Game::getYear(){
  return year;
}

char* Game::getPublisher(){
  return publisher;
}

int Game::getRating(){
  return rating;
}
