/**
 *Author: Zareef Amyeen
 *Date: September 6th, 2018
 *The Guessing Game Project is a Computer Question Based Game.
 *This game will have the user guess a number between 1 and 100
 *When asking it will also tell you if the number is too large or too small
 *Once you have correctly guessed the random number, the game will ask if you want to play agai  */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
  //Creates a seed of the Random Number
  srand(time(NULL));
  bool stillPlaying = true;
  cout << "Welcome to Guessing Game!" << endl;
  //This while loop runs while the game is running
  while (stillPlaying){
    cout << "Enter in a guess between 0 and 100:" << endl;
    int guess = -1;
    int counter = 1;
    int RandomNum = rand() % 101;
    //cout << "Random Number Generated: " << RandomNum << endl;
    //Keeps the game running while the guess is not the same as the Guess.
    while (guess != RandomNum){
      cin >> guess;
      if (guess > RandomNum){
	cout << "Your guess is too large. Try Again." << endl;
	counter = counter + 1;
      }
      else if (guess < RandomNum){
	cout << "Your guess is too small. Try again." << endl;
	counter = counter + 1;
      }
      else {
	cout << "Your guess is right!\n"<< endl;
	if (counter == 1){
	  cout << "You took 1 guess!" << endl;
	}
	else{
	  cout << "You took " << counter << " guesses!" << endl;
	}
      }
    }
    cout << "Would you like to play again? (Answer with Y or N)" << endl;
    char yesno = 'a';
    cin >> yesno;
    if (yesno == 'y' || yesno == 'Y'){
      stillPlaying = true;
    }
    if (yesno == 'n' || yesno == 'N'){
      stillPlaying = false;
      cout << "Thanks for playing! Game has ended." << endl;
    }
  }
}
