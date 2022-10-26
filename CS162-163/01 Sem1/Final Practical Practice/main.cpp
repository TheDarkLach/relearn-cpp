#include "list.h"

using namespace std;

int main()
{
    node * head = NULL;
    build(head);
    display_all(head);

    //PLEASE PUT YOUR CODE HERE to call the function assigned
    removeFirst(head);
    twoSmallest(head);

    node* next = head;
    while (next->next != NULL){
      next = next->next;
    }
    node* newHead = new node;
    newHead->data = head->data;
    //cout << newHead->data << endl;
    node* newTail = new node;
    newTail->data = next->data;
    newHead->next = newTail;

    display_all(newHead);
    display_all(head);
    
    return 0;
}
