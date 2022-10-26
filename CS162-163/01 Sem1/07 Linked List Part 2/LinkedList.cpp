/*
 * Author: Zareef Amyeen
 * Date: January 15th, 2019
 * Linked List project is basically creating your own vector of Student pointers
 * It should be able to do everything that a Vector can do, ie these functions: ADD, PRINT, DELETE, AVERAGE and obviously to end the program QUIT
 * The ADD function will ADD a node into the list (Where the Linked List's ID is what sorts the ID)
 * The PRINT function will PRINT all the node's in a List
 * The DELETE function will DELETE the specified node with the specified ID. If there is no such ID, then the DELETE function will say so.
 * The AVERAGE function will AVERAGE all the Nodes GPA's  in the list and print it
*/

#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

void printStudent(Student* newStudent){
	cout << "First Name is: " << newStudent->getfirstname() << endl
	     << "Last Name is: " << newStudent->getlastname() << endl;
	printf("GPA is: %.2f\n", *(newStudent->getGPA()));
	cout << "ID is: " << *(newStudent->getID()) << endl;
}

void printNode(Node* newNode){
	printStudent(newNode->getStudent());
	cout << endl;
}

//Non Recursion Print Method NOT USED
void printList(Node* head){
	printf("Student List:\n");
	Node* next = head;
	int counter = 0;
	do{
		printNode(next);
		cout << endl;
		counter = counter + 1;
	}while((next = next->getnext()) != NULL);
	cout << "There were " << counter << " Students in the Student List" << endl;
}

void printList(Node* next,int counter){
	if (next != NULL){
		printNode(next);
		counter = counter + 1;
		printList(next->getnext(),counter);
	}
	else{
		cout << "There were " << counter << " Students in the Student List" << endl;
	}
}

Student* addStudent(){
	Student* newStudent = new Student;
	cin.ignore(10000,'\n');
	cout << "First Name: ";
	cin.get(newStudent->getfirstname(),11);
	cin.clear();
	cin.ignore(10000,'\n');
  
	cout << "Last Name: ";
	cin.get(newStudent->getlastname(),11);
	cin.clear();
	cin.ignore(10000,'\n');
	
	cout << "GPA: ";
	cin >> *newStudent->getGPA();
	
	cout << "ID: ";
	cin >> *newStudent->getID();
	
	return newStudent;
}

//The entirety of this method is from Mr. Galbraith's Linked List/Recursion Visualizer found here: https://goo.gl/od5Qeb
void addList(Node*& head, Node* previous, Student* newStudent){
	int ID = *newStudent->getID();
	if (head == NULL){
		cout << "FIRST IF " << endl;
		head = new Node();
		head->setStudent(newStudent);
	}
	else if (ID < *head->getStudent()->getID()){
		cout << "SECOND IF " << endl;
		Node* temp = new Node();
	        temp->setStudent(head->getStudent());
		temp->setnext(head->getnext());
		head->setStudent(newStudent);
		head->setnext(temp);
	}
	else if (previous->getnext() == NULL){
		cout << "THIRD IF " << endl;
		Node* newNode = new Node();
		newNode->setStudent(newStudent);
		previous->setnext(newNode);
	}
	else if (ID < *previous->getnext()->getStudent()->getID()){
		cout << "FOURTH IF " << endl;
		Node* newNode = new Node();
		newNode->setStudent(newStudent);
		newNode->setnext(previous->getnext());
		previous->setnext(newNode);
	}
	else{
		cout << "FIFTH IF " << endl;
		addList(head, previous->getnext(), newStudent);
	}
}

void deleteList (Node* &head, Node* previous,int ID){
	//Four Options: Linked List is Empty, We are deleting head, We are deleting any node within the middle of the linked list
	//Linked List is empty
	if (head == NULL){
		cout << "This is an empty list.";
		return;
	}
	//Deleting the Head
	//Deleting the Head has Two Different Options: Head's next == NULL, == another Node
	//next == another Node
	else if (ID == *head->getStudent()->getID()){
		if (head->getnext() != NULL){
			cout << "DELETING THE HEAD" << endl;
			Node* temp = head;	
			head = head->getnext();
			temp->~Node();
		} 
		//Empty List (next == NULL)
		else{
			cout << "DELETING THE HEAD (WHEN EMPTY)" << endl;
			head->~Node();
			head = NULL;//So that stuff can be added to it again
		}
	}
	//If the next node doesn't exist the list has successfully been traversed and no Node exists
	else if (previous->getnext() == NULL){
		cout << "The list has been traversed. There is no Node that exists that has that ID." << endl;
		return;
	}
	else if(ID == *previous->getnext()->getStudent()->getID()){
		cout << "DELETING A NODE WITHIN MIDDLE OF LIST" << endl;
		Node* temp = previous->getnext();
		previous->setnext(previous->getnext()->getnext());
		temp->~Node();
	}
	else{
		cout << "REPEAT" << endl;
		deleteList(head,previous->getnext(),ID);
	}
}

void averageList(Node* next,int counter,float average){
	if (next != NULL){
		counter += 1;
		average += *next->getStudent()->getGPA();
		averageList(next->getnext(),counter,average);
	}
	else{
		printf("%.2f\n",average/counter);
	}
}

int main(){

	Node* head = NULL;
	
	bool stillPlaying = true;
  	while(stillPlaying){
    	char input[10];
    	cout << "Please enter one of the following options: {ADD,PRINT,DELETE,AVERAGE,QUIT}" << endl;
    	cin >> input;
    	if (strcmp(input,"ADD") == 0){
    		Student* newStudent = new Student();
    		newStudent = addStudent();
    		addList(head,head,newStudent);
    		printf("ADDED\n");
    	}
    	else if (strcmp(input,"DELETE") == 0){
    		cout << "What is the ID that you want to Delete: " << endl;
    		int ID;
    		cin >> ID;
    		deleteList(head,head,ID);
    		printf("DELETED\n");
    	}
    	else if (strcmp(input,"AVERAGE") == 0){
    		averageList(head,0,0);
    		printf("AVERAGED\n");
    	}
    	else if (strcmp(input,"PRINT") == 0){
    		if (head != NULL){
    			cout << "LINKED LIST: " << endl;
    			printList(head,0);
    		}
    		else{
    			cout << "Your Linked List is empty!" << endl;
    		}
    		printf("PRINTED\n");
    	}
    	else if (strcmp(input,"QUIT") == 0){
   		 	stillPlaying = false;
    		printf("Program has ended\n");
    	}  
    }
}
