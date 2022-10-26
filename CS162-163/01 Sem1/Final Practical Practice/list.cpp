//list.cpp
#include "list.h"
#include <cstring>
#include <stdio.h>

using namespace std;

void removeFirst(node* &head){
  //cout << "Entered into Remove First Program" << endl;
  node* temp = head;
  head = head->next;
  delete temp;
}

void twoSmallest(node* head){
  int first,second;
  first = Largest(head);
  second = Largest(head);
  node* next = head;
  //cout << "Entered twoSmallest" << endl;
  while (next->next != NULL){
    if (next->data < first){
      first = next->data;
    }
    else if (next->data < second && next->data != first){
      second = next->data;
    }
    next = next->next;
  }
  printf("Smallest: %d,Second Smallest: %d\n", first,second);
}

int Largest (node* head){
  node* next = head;
  int largest = 0;
  //cout << "Entered Largest" <<endl;
  while (next->next != NULL){
    if (next->data > largest){
      largest = next->data;
    }
    next = next->next;
  }
  //cout << "Largest is: " << largest << endl;
  return largest;
}



