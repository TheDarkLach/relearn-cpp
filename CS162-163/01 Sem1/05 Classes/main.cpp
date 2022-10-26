#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main(){
  vector<Media*>* AllMedia = new vector<Media*>;
  bool isRunning = true;
  while (isRunning){
    char input[100];
    
    cin >> input;
    else if (strcmp(input,"QUIT") == 0){
      printf("CLASSES PROJECT HAS ENDED\n");
      isRunning = false;
    }
    else{
    	printf("Type in one of the commands prompted: ADD, DELETE");
    }
  }
}
