#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
/**
 *Write a C++ program to read in a phrase from the user. Swap the first and last letters of every word in the phrase. Display the resulting phrase from main. Do this 5 times. Use of a loop is required. Display your results from main.
 */

int main()
{
    //PLEASE PUT YOUR CODE HERE to call the function assigned
  char input[100];
  int spaceindex = 0;
  printf("Print out a Phrase:\n");
  int counter = 0;
  cin.get(input,100);
  for (int j = 0; j < strlen(input); j++){
    if (input[j] == ' '){
      counter = counter + 1;
      char swap = input[spaceindex];
      input[spaceindex] = input[j-1];
      input[j-1] = swap;
      spaceindex = j+1;
    }
  }
  cout << counter;
  if (counter != 0){
    for (int j = strlen(input); j > -1; j--){
      if(input[j] == ' '){
	char swap = input[strlen(input)-1];
	input[strlen(input-1)] = input[j+1];
	input[j+1] = swap;
      }
    }
  }
  else{
    char swap = input[0];
    input[0] = input[strlen(input)-1];
    input[strlen(input)-1] = input[0];
  }
  for (int i = 0; i < strlen(input); i++){
    cout << input[i];
  }
  return 0;
}
