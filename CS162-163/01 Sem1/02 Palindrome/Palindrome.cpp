/*
 * Author: Zareef Amyeen
 * Date: September 12th, 2018
 * The Palindrome Project:
 * Is a project that takes a string (character array) and removes all spaces and punctuation (leaving behind only: letters and numbers)
 * It will print palindrome if the nonpunctuated string (character array) is the same backward as forward
 */
#include <iostream>
#include <cstring>
#include <array>
using namespace std;

int main (){
  char str[80];
  char removed[80];
  cout << "Enter in a String: " << endl;
  cin.get(str,80);
  char backward[80];
  int counter = 0;
  //This for loop puts the string that you entered into and enters it into a removed array if and only if the character in the string entered is a letter or number
  for (int i = 0; i < 80; i++){
    char check = tolower(str[i]);
    if (check != '\0'){
      //This idea was suggested by Cheng Feng Teng over isalnum()
      if ((check >= 48 && check <= 57) || (check >= 97 && check <= 122)){
	//cout << "I is: " << i << endl;
	//cout << "Counter is: " << counter << endl;
	removed[counter] = check;
	counter = counter + 1;
      }
    }
    else{
      removed[counter] = '\0';
      break;
    }
  }
  // cout << "Str is: " << str << endl;
  // cout << "Removed is: " << removed << endl;
  bool palindrome = true;
  int arraysize = strlen(removed);
  // cout << "Array Size is : " << arraysize << endl;
  //This for loop's function is to check from the front of the array and compare to the back of the array
  for (int i = 0; i < arraysize; i++){
    if (removed[i] != removed[arraysize-i-1]){
      palindrome = false;
    }
  }
  if (palindrome){
    cout << "Palindrome." << endl;
  }
  else{
    cout << "Not a Palindrome." << endl;
  }
  return 0;
}
