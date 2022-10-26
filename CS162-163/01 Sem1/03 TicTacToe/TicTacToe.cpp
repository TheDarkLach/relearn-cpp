/*
 * Author: Zareef Amyeen
 * Date: September 12th, 2018
 * Tic Tac Toe Project: This game will have the user input in pieces to play tic tac toe until there is a tie or a win
 * At the end it will ask you whether or not you want to play again
 * If yes it will clear the board and restart if no it will print the final score and end the program
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

const int BLANK = -1;
const int X_MOVE = 1;
const int O_MOVE = 0;
const int X_TURN = 0;
const int O_TURN = 1;
//I learned how to make global constants from ChengFengTeng

bool playAgain(bool stillPlaying);
void clearBoard(int board[3][3]);
void printBoard (int board[3][3]);
bool checkWin(int board[3][3], int player);
bool checkTie(int board[3][3]);

//-std=c++11
//This program requires C++11 to run
int main(){
  cout << "Hello! Welcome to Tic Tac Toe!" << endl;
  bool stillPlaying = true;
  int turn = X_TURN;
  int board[3][3];
  int Xcounter = 0;
  int Ocounter = 0;
  while (stillPlaying){
    clearBoard(board);
    cout << "Enter a letter followed by a number to indicate where to put your piece." << endl;
    while (checkWin(board,X_MOVE) != true && checkWin(board,O_MOVE) != true && checkTie(board) != true){
      printBoard(board);
      char input[100];
      cin >> input;
      if (strlen(input) != 2) {
	cout << "Enter a letter followed by a number" << endl;
      }
      else if (input[0] != 'a' && input[0] != 'b' && input[0] != 'c'){
	cout << "Row must be an a, b, or c." << endl;
      }
      else if (input[1] != '1' && input[1] != '2' && input[1] != '3'){
	cout << "Column must be 1, 2, or 3." << endl;
      }
      else{
	int row = input[0] - 'a';
	int column = input[1] - '1';
	//cout << "(" << row << "," << column << ")";
	if (board[row][column] == BLANK){
	  if (turn == X_TURN) {
	    board[row][column] = X_MOVE;
	    turn = O_TURN;
	  }
	  else{
	    board[row][column] = O_MOVE;
	    turn = X_TURN;
	  }
	}
	else{
	  cout << "There is a piece there!";
	}
      }
    }
    if (checkWin(board,X_MOVE) == true){
      cout << "X wins!" << endl;
      Xcounter = Xcounter + 1;
      cout << "Current score is: " << endl <<  "X: " << Xcounter << endl << "O: " << Ocounter << endl;
      printBoard(board);
      stillPlaying = playAgain(stillPlaying);
      turn = X_TURN;
    }
    if (checkWin(board,O_MOVE) == true){
      cout << "O wins!" << endl;
      Ocounter = Ocounter + 1;
      cout << "Current score is: " << endl << "X: " << Xcounter << endl << "O: " << Ocounter << endl;
      printBoard(board);
      stillPlaying = playAgain(stillPlaying);
      turn = X_TURN;
    }
    else if (checkTie(board)){
      cout << "There is a tie!" << endl << "Current score is: " << endl << "X: " << Xcounter << endl << "O: " << Ocounter << endl;
      printBoard(board);
      stillPlaying = playAgain(stillPlaying);
    }
  }
}
//This method checks if someone has won
bool checkWin(int board[3][3], int player){
  if (board[0][0] == player && board[0][1] == player && board[0][2] == player) {
    return true;
  }
  else if (board[1][0] == player && board[1][1] == player && board[1][2] == player) {
    return true;
  }
  else if (board[2][0] == player && board[2][1] == player && board[2][2] == player) {
    return true;
  }
  else if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
    return true;
  }
  else if (board[2][0] == player && board[1][1] == player && board[0][2] == player) {
    return true;
  }
  else if (board[0][0] == player && board[1][0] == player && board[2][0] == player) {
    return true;
  }
  else if (board[0][1] == player && board[1][1] == player && board[2][1] == player) {
    return true;
  }
  else if (board[0][2] == player && board[1][2] == player && board[2][2] == player) {
    return true;
  }
  return false;
}

//This method checks for Tie (meaning that no one has won at the end of a game)
bool checkTie(int board[3][3]){
  for (int row = 0; row < 3; row++){
    for (int column = 0; column < 3; column++){
      if (board[row][column] == BLANK){
	return false;
      }
    }
  }
  return true;
}

  //This method asks if you want to play again, if yes restarts the game, if no ends the game and prints out the final score
  bool playAgain(bool stillPlaying){
    cout << "Do you want to Play Again? (Y or N)" << endl;
    char yesno[2];
    cin >> yesno;
    if (yesno[0] == 'y' || yesno[0] == 'Y'){
      cout << "IN";
      return true;
    }
    else {
      cout << "Thanks for Playing! Game has Ended." << endl;
      return false;
    }
  }

//This method prints the board every turn
  void printBoard(int board[3][3]){
    cout << "  1  2  3" << endl;
    for (int row = 0; row < 3; row++){
      char currentrow = 'a' + row;
      cout << currentrow << " ";
      for (int column = 0; column < 3; column++){
	if (board[row][column] == BLANK){
	  cout << "-  ";
	}
	else if (board[row][column] == X_MOVE){
	  cout << "X  ";
	}
	else if (board[row][column] == O_MOVE){
	  cout << "O  ";
	}
      }
      cout << endl;
    }
  }



  //This method is used at the end of each game if you say yes you want to play again so you can start with a new board
  void clearBoard(int board[3][3]){
    for (int row = 0; row < 3; row++){
      for (int column = 0; column < 3; column ++){
	board[row][column] = BLANK;
      }
    }

    
  }

