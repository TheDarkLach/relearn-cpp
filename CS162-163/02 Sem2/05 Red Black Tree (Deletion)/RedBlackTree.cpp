/*
//  main.cpp
//  Red Black Tree
// The Red Black Tree is 
//	1) Every node has a color either red or black.
//	2) Root of tree is always black.
//	3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).
//	4) Every path from a node (including root) to any of its descendant NULL node has the same number of black nodes.
//  Created by Zareef Amyeen on 3/30/19.
//  Copyright © 2019 Zareef Amyeen. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "Node.h"

using namespace std;

//Helper Node Family Functions
Node* grandParent(Node* Root){
	Node* Parent = Root->getParent();
	if (Parent == NULL){
		return NULL;
	}
	else{
		return Parent->getParent();
	}
}
Node* Sibling(Node* Root){
	Node* Parent = Root->getParent();
	if (Parent == NULL){
		return NULL;
	}
	if (Parent->getLeft() == Root){
		return Parent->getRight();
	}
	else if(Parent->getRight() == Root){
		return Parent->getLeft();
	}
	return NULL;
}
Node* Uncle(Node* Root){
	Node* Parent = Root->getParent();
	Node* GrandParent = grandParent(Root);
	
	if (GrandParent == NULL){
		return NULL;
	}
	return Sibling(Parent);
}
bool isBlack(Node* Root){
	if (Root == NULL){
		return true;
	}
	if (Root->isBlack()){
		return true;
	}
	else{
		return false;
	}
}
bool isRed(Node* Root){
	if (Root == NULL){
		return false;
	}
	if (Root->isRed()){
		return true;
	}
	else{
		return false;
	}
}
bool isRightChild(Node* Root){
	if (Root == NULL){
		return false;
	}
	if (Root->getParent()->getRight() == Root){
		return true;
	}
	if (Root->getParent()->getLeft() == Root){
		return false;
	}
	return false;
}
bool isLeftChild(Node* Root){
	if (Root == NULL){
		return false;
	}
	if (Root->getParent()->getLeft() == Root){
		return true;
	}
	if (Root->getParent()->getRight() == Root){
		return false;
	}
	return false;
}

void LeftRotate(Node* Root);
void RightRotate(Node* Root);

void parseCommaInput(char input[], vector<int> &integers);
void parseSpaceInput(char input[], vector<int> &integers);

//Information about each function is below
Node* insert(Node* Root, Node* newNode);
void insertRecurse(Node* Root, Node* newNode);
void insertRepair(Node* newNode);
void insertCase1(Node* Root);
void insertCase2(Node* Root);
void insertCase3(Node* Root);
void insertCase4(Node* Root);
void insertCase4Step2(Node* Root);

Node* remove(Node* Root,int del);
Node* removeOneChild(Node* c);
void removeCase1(Node* c,Node* Root);
void removeCase2(Node* c,Node* Root);
void removeCase3(Node* c,Node* Root);
void removeCase4(Node* c,Node* Root);
void removeCase5(Node* c,Node* Root);
void removeCase6(Node* c,Node* Root);


void replaceNode(Node* delNode, Node* c);
Node* findRoot(Node* anyNode){
	//cout << "Entered Find Root" << endl;
	if (anyNode == NULL){
		//cout << "That Node is NULL" << endl;
		return anyNode;
	}
	while (anyNode->getParent() != NULL){
		anyNode = anyNode->getParent();
	}
	return anyNode;
}
void print(char prefix[], Node* Root, bool isLeft);
void bPrint(Node* Root){
	char* str = new char[100];
	str[0] = '\0';
	print(str,Root,false);
	delete []str;
}

void search(Node* Root,int del,Node* searched);
Node* nonRecurseSearch(Node* Root,int del);
Node* inOrderSuccessor(Node* Root);
Node* findSmallest(Node* Root);

int main(){
	Node* Root = NULL;
	cout << "How would you like to enter your list? (Answer with 1 or 2) \n" <<
	"1.Manually through the Console\n" <<
	"2.Through a Text File\n>>";
	int in;
	cin >> in;
	
	//Console Insertion
	vector<int> integers;
	if (in == 1){
		cout << "How would you like to enter your Numbers? (Answer with 1 or 2) \n" <<
		"1. Space Separated\n" <<
		"2. Comma Separated\n>>";
		in = 0;
		cin >> in;
		//Space Separated
		if (in == 1){
			char input[100];
			cin.ignore(10000,'\n');
			cout << "Enter in your Numbers Separated by a Space\n>>";
			cin.get(input,1000);
			cin.clear();
			cin.ignore(10000,'\n');
			
			//cout << input << endl;
			parseSpaceInput(input, integers);
			for (int i = 0; i < integers.size();i++){
				//cout << "Inserting: " << integers[i] << endl;
				Node* newNode = new Node();
				newNode->setValue(integers[i]);
				Root = insert(Root, newNode);
			}
			for (int i = 0; i < integers.size(); i++){
				//cout << integers[i] << endl;
			}
		}
		//Comma Separated
		else if (in == 2){
			char input[100];
			cin.ignore(10000,'\n');
			cout << "Enter in your Numbers Separated by a Comma w/no Spaces\n>>";
			cin.get(input,1000);
			cin.clear();
			cin.ignore(10000,'\n');
			
			int length = strlen(input);
			input[length] = ',';
			input[length+1] = '\0';
			/*cout << input << endl;
			for (int i = 0; i < strlen(input); i++){
				cout << i;
			}
			cout << endl;
			cout << "Length of String Length is: " << strlen(input) << endl;
			cout << "Entering parseCommaInput" << endl;
			*/
			parseCommaInput(input,integers);
			for (int i = 0;i < integers.size(); i++){
				//cout << "Inserting: " << integers[i] << endl;
				Node* newNode = new Node();
				newNode->setValue(integers[i]);
				Root = insert(Root, newNode);
			}
			for (int i = 0; i < integers.size(); i++){
				//cout << integers[i] << endl;
			}
		}
	}
	//Text File Input
	else if(in == 2){
		cout << "Is the Text File... \n" <<
		"1. Space Separated\n" <<
		"2. Comma Separated\n>>";
		in = 0;
		cin >> in;
		//Space Separated
		if (in == 1){
			cin.ignore(10000,'\n');
			cout << "Please enter the name of your Text File: \n>>";
			char input[1000];
			cin.get(input,100);
			cin.clear();
			cin.ignore(10000,'\n');
		
		
			ifstream myfile;
			myfile.open(input);
		
			if (!myfile){
				cout << "There is an error opening the file.\n";
				return 0;
			}
			else{
				char fileInput[100000];
				int i = 0;
				//https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
				while (!myfile.eof()){
					//myfile >> fileInput[i];
					fileInput[i] = myfile.get();
					if (fileInput[i] == ' '){
						fileInput[i+1] = '\0';
						//cout << fileInput << endl;
					}
					i++;
				}
				fileInput[i-1] = '\0';
				myfile.close();
				//cout << fileInput << endl;
				/*for (int i = 0; i < strlen(fileInput); i++){
					cout << i;
				}
				cout << endl;*/
				parseSpaceInput(fileInput,integers);
				for (int i = 0; i < integers.size();i++){
					Node* newNode = new Node();
					newNode->setValue(integers[i]);
					Root = insert(Root, newNode);
				}
				/*for(int i = 0; i < integers.size();i++){
					cout << integers[i] << endl;
					//Root = insert(Root, integers[i]);
				}*/
				
		}
		}
		//Comma Separated
		else if (in == 2){
			cin.ignore(10000,'\n');
			cout << "Please enter the name of your Text File: \n>>";
			char input[1000];
			cin.get(input,100);
			cin.clear();
			cin.ignore(10000,'\n');
		
		
			ifstream myfile;
			myfile.open(input);
		
			if (!myfile){
				cout << "There is an error opening the file.\n";
				return 0;
			}
			else{
				char fileInput[100000];
				int i = 0;
				//https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
				while (!myfile.eof()){
					//myfile >> fileInput[i];
					fileInput[i] = myfile.get();
					//cout << "i is: " << i << " and my value is: " << fileInput[i] << endl;
					if (fileInput[i] == ','){
						fileInput[i+1] = '\0';
						//cout << fileInput << endl;
					}
					i++;
				}
				//cout << "i is: " << i << endl;
				int length = strlen(fileInput);
				//cout << "Length of File Input is: " << strlen(fileInput) << endl;
				fileInput[length-2] = ',';
				fileInput[length-1] = '\0';
				myfile.close();
				/*cout << fileInput << endl;
				for (int i = 0; i < strlen(fileInput); i++){
					cout << i;
				}
				cout << endl;*/
				parseCommaInput(fileInput,integers);
				for (int i = 0; i < integers.size();i++){
					//cout << "Inserting: " << integers[i] << endl;
					Node* newNode = new Node();
					newNode->setValue(integers[i]);
					Root = insert(Root, newNode);
				}
			}
		}
	}
	
	bool stillPlaying = true;
	while (stillPlaying){
		cout << "Would you like to: (Answer with 1,2,3,4 or 5)\n" <<
		"1. Insert\n" <<
		"2. Print\n" <<
		"3. Delete\n" <<
		"4. Search\n" <<
		"5. Quit\n>>";
		cin >> in;
		//Insert
		if (in == 1){
			cout << "Please enter in one integer\n>>";
			int newInt;
			cin >> newInt;
			Node* newNode = new Node();
			newNode->setValue(newInt);
			Root = insert(Root,newNode);
		}
		//Print
		else if (in == 2){
			//cout << Root->getRight()->getValue() << endl;
			char* str = new char[100];
			str[0] = '\0';
			print(str,Root,false);
			delete []str;
		}
		//Delete
		else if (in == 3){
			//cout << "Sorry, currently unavailable." << endl;
			cout << "Which value would you like to delete within the tree?\n>>";
			int del;
			cin >> del;
			
			Root = remove(Root,del);
			
		}
		//Search
		else if (in == 4){
			cout << "Which value are you searching for?\n>>";
			int s;
			cin >> s;
			
			//Node* searched = nonRecurseSearch(Root,s);
			//cout << "Searched Value is: " << searched->getValue() << endl;
			if (nonRecurseSearch(Root,s) == NULL){
				cout << "This Node does not exist" << endl;
			}
			/*if(searched == NULL){
				cout << "This Node does not exist" << endl;
			}*/
			else{
				cout << "This Node exists" << endl;
			}
		}
		//Quit
		else if (in == 5){
			stillPlaying = false;
		}
		else{
			cout << "Please enter in 1,2,3,4 or 5" << endl;
		}
	}

}

void LeftRotate(Node* Root){
	Node* Right = Root->getRight();
	Node* Parent = Root->getParent();
	Root->setRight(Right->getLeft());
	Right->setLeft(Root);
	Root->setParent(Right);
	if (Root->getRight() != NULL){
		Root->getRight()->setParent(Root);
	}
	if (Parent != NULL){
		if (Root == Parent->getLeft()){
			Parent->setLeft(Right);
		}
		else if (Root == Parent->getRight()){
			Parent->setRight(Right);
		}
	}
	Right->setParent(Parent);
}
void RightRotate(Node* Root){
	Node* Left = Root->getLeft();
	Node* LRight = Left->getRight();
	Node* Parent = Root->getParent();
	Root->setLeft(Left->getRight());
	Left->setRight(Root);
	Root->setParent(Left);
	if (Root->getLeft() != NULL){
		Root->getLeft()->setParent(Root);
	}
	if (Parent != NULL){
		if (Root == Parent->getLeft()){
			Parent->setLeft(Left);
		}
		else if (Root == Parent->getRight()){
			Parent->setRight(Left);
		}
	}
	Left->setParent(Parent);
}

Node* insert(Node* Root, Node* newNode){
	///cout << "Insert Recurse" << endl;
	insertRecurse(Root, newNode);
	//cout << "Insert Repair" << endl;
	insertRepair(newNode);
	
	//This portion does not have anything to do with insertion but instead to return the Root of the tree
	Root = newNode;
	while (Root->getParent() != NULL){
		Root = Root->getParent();
	}
	/*char* str = new char[100];
	str[0] = '\0';
	print(str,Root,false);*/
	return Root;
}
void insertRecurse(Node* Root, Node* newNode){
	if (Root != NULL){
		//cout << "Current Root value is: " << Root->getValue() << endl;
	}
	if (Root != NULL && newNode->getValue() < Root->getValue()){
		if(Root->getLeft() != NULL){
			//cout << "Going Left" << endl;
			insertRecurse(Root->getLeft(),newNode);
			return;
		}
		else{
			//cout << "Set Left of: " << Root->getValue() << endl; 
			Root->setLeft(newNode);
		}
	}
	else if(Root != NULL){
		if (Root->getRight() != NULL){
			//cout << "Going Right" << endl;
			insertRecurse(Root->getRight(),newNode);
			return;
		}
		else{
			//cout << "Set Right of: " << Root->getValue() << endl;
			Root->setRight(newNode);
		}
	}
	newNode->setParent(Root);
}
void insertRepair(Node* newNode){
	//Case 1: If you're adding something into the Root of the tree
	if (newNode->getParent() == NULL){
		//cout << "Case 1" << endl << "The new Node is the Root of the Tree and needs to be Black." << endl << "It will be turned Black" << endl;
		insertCase1(newNode);
	}
	//Case 2: If the Parent is Black then nothing is violated
	else if (newNode->getParent()->isBlack()){
		//cout << "Case 2" << endl << "Parent is Black" << endl << "Nothing will be changed" << endl;
		insertCase2(newNode);
	}
	//Case 3: Parent and Uncle are Red (Red cannot have Red Child)
	//Note I am not checking that the Parent is Red because the other if loops have already checked for me
	else if (Uncle(newNode) != NULL && Uncle(newNode)->isRed()){
		//cout << "Case 3" << endl << "Parent and Uncle are Red" << endl << "They will be turned black and grandParent will be recursively be called upon" << endl;
		insertCase3(newNode);
	}
	//If we are down here we know that Parent exists and is red (This violating 4)
	//We also know that the Uncle either A) Doesn't exist, or B) is black (This violating 5)
	else{
		//cout << "Case 4" << endl << "Parent is Red, Uncle is Black" << endl << "Rotate and Set GrandParent to Red, Set Parent to Black" << endl;
		insertCase4(newNode);
	}
}
void insertCase1(Node* Root){
	//Turn the Root to Black
	Root->setBlack();
}
void insertCase2(Node* Root){
	//Change nothing
	return;
}
void insertCase3(Node* Root){
	//Change the Uncle and the Parent to Black, and make grandparent Red.
	//This may cause a violating in grandparent and so you must call on insertRepair on grandParent

	Root->getParent()->setBlack();
	Uncle(Root)->setBlack();
	grandParent(Root)->setRed();
	insertRepair(grandParent(Root));
}
void insertCase4(Node* Root){
	//There are two cases, either the parent is larger or smaller than it's node
	Node* Parent = Root->getParent();
	Node* GrandParent = grandParent(Root);
	//Parent is Smaller than Child
	if (Root == Parent->getRight() && Parent == GrandParent->getLeft()){
		LeftRotate(Parent);
		Root = Root->getLeft();
	}
	//Parent is Larger than child
	else if (Root == Parent->getLeft() && Parent == GrandParent->getRight()){
		RightRotate(Parent);
		Root = Root->getRight();
	}
	insertCase4Step2(Root);
}
void insertCase4Step2(Node* Root){
	Node* Parent = Root->getParent();
	Node* GrandParent = grandParent(Root);
	if (Root == Parent->getLeft()){
		RightRotate(GrandParent);
	}
	else{
		LeftRotate(GrandParent);
	}
	Parent->setBlack();
	GrandParent->setRed();
}

void parseCommaInput(char input[], vector<int> &integers){
	int i = 1;//Index of Input
	int spacePointers[2];
	spacePointers[0] = -1;
	//cout << strlen(input) << endl;
	while (i < strlen(input)){
		//cout << "i is: " << i << " and input[i] is: " << input[i] << endl;
		if (input[i] == ','){
			spacePointers[1] = i;
			//cout << "spacePointers[0] is: " << spacePointers[0] << endl << "spacePointers[1] is: " << spacePointers[1] << endl;
			int number = 0;
			int exponent = 0;
			for (int k = spacePointers[1] - 1; k > spacePointers[0]; k--){
				//cout << "input[k] - 48: " << (int)(input[k] - 48) << endl;
				//cout << "Exponent: " << pow(10,exponent) << endl;
				number += (input[k] - 48) * pow(10,exponent);
				exponent++;
			}
			//cout << "Number is: " << number << endl << endl;
			integers.push_back(number);
			spacePointers[0] = spacePointers[1];
			
		}
		i++;
	}
}
void parseSpaceInput(char input[], vector<int> &integers){
	int i = 1;//Index of Input
	int j = 0;//Index of Numbers
	int spacePointers[2];
	spacePointers[0] = -1;
	while (i < strlen(input)){
		if (input[i] == ' '){
			spacePointers[1] = i;
			int number = 0;
			int exponent = 0;
			for (int k = spacePointers[1] - 1; k > spacePointers[0]; k--){
				//cout << "input[k] - 48: " << (int)(input[k] - 48) << endl;
				//cout << "Exponent: " << pow(10,exponent) << endl;
				number += (input[k] - 48) * pow(10,exponent);
				exponent++;
			}
			//cout << "Number is: " << number << endl << endl;
			integers.push_back(number);
			spacePointers[0] = spacePointers[1];
		}
		i++;
	}
	int number = 0;
	int exponent = 0;
	for (int k = strlen(input)-1; k > spacePointers[0]; k--){
			//cout << "input[k] - 48: " << (int)(input[k] - 48) << endl;
			//cout << "Exponent: " << pow(10,exponent) << endl;
			number += (input[k] - 48) * pow(10,exponent);
			exponent++;
	}
	//cout << "Number is: " << number << endl << endl;
	integers.push_back(number);
}

//Does not work - leads to seg fault
void search(Node* Root,int del,Node* searched){
	if (Root == NULL){
		//cout << "Root is NULL" << endl;
		searched = NULL;
		return;
	}
	else if (del > Root->getValue()){
		//cout << "Going Right of Root (" << Root->getValue() << ")" << endl;
		search(Root->getRight(),del,searched);
	}
	else if (del < Root->getValue()){
		//cout << "Going Left of Root (" << Root->getValue() << ")" << endl;
		search(Root->getLeft(),del,searched);
	}
	else if (del == Root->getValue()){
		//cout << "Delete has been found. Current value (" << Root->getValue() << ")" << endl;
		searched = Root;
		return;
	}
}
Node* nonRecurseSearch(Node* Root,int del){
	Node* search = Root;
	while(search != NULL){
		if (del < search->getValue()){
			search = search->getLeft();
		}
		else if (del > search->getValue()){
			search = search->getRight();
		}
		else if(del == search->getValue()){
			return search;
		}
	}
	return NULL;
}
Node* inOrderSuccessor(Node* Root){
	//cout << "Root's value is: " << Root->getValue() << endl;
	if (Root->getRight() != NULL){
		//cout << "Right of Root is not equal to NULL" << endl;
		Root = Root->getRight();
		while (Root->getLeft() != NULL){
			Root = Root->getLeft();
		}
		return Root;
	}
	if (Root->getLeft() != NULL){
		return Root->getLeft();
	}	
	return Root;
}
Node* findSmallest(Node* Root){
	Node* Left = Root;
	while (Left->getLeft() != NULL){
		Left = Left->getLeft();
	}
	return Left;
}

void replaceNode(Node* delNode, Node* c){
	c->setParent(delNode->getParent());
	if (delNode->getParent() == NULL){
		return;
	}
	if (delNode == delNode->getParent()->getLeft()){
		delNode->getParent()->setLeft(c);
	}
	else{
		delNode->getParent()->setRight(c);
	}
}

Node* remove(Node* Root, int del){
	if (nonRecurseSearch(Root,del) == NULL){
		cout << "The Node that you want to delete does not exist within the tree" << endl;
		return findRoot(Root);
	}
	else{
		//cout << "The Node that you want to delete exists" << endl;
		Node* delNode = new Node();
		delNode = nonRecurseSearch(Root,del);
		if (delNode->getLeft() == NULL || delNode->getRight() == NULL){
			cout << "Removing delNode(" << delNode->getValue() << ")" << endl;
			return removeOneChild(delNode);
		}
		else{
			//Effectively does the same thing as inOrderSuccessor 
			//Note that with this method, the left child of Deleted Node can NOT be NULL because of the previous if statement
			Node* iOSNode = findSmallest(delNode->getRight());
			delNode->setValue(iOSNode->getValue());
			remove(delNode->getRight(),iOSNode->getValue());
		}		
	}
	return findRoot(Root);
}

/*
		Node* iOSNode = inOrderSuccessor(delNode);
		//Simple Case 1: Deleting a Red Node (that Must have Two NIL Children)
		if (isRed(iOSNode)){
			cout << "Simple Case 1: Deleting a Red Node (that Must have Two NIL children)" << endl;
			Node* p = delNode->getParent();
			p->getRight() == delNode ? p->setRight(NULL) : p->setLeft(NULL);
			delNode->~Node();
			return Root;
		}
		//Simple Case 2: Deleting a Black Node with a Single Red Child (The Red Child must have Two NIL children)
		else if ( isBlack(iOSNode) && isRed(iOSNode->getRight()) ){
			cout << "Simple Case 2: Deleting a Black Node(" << iOSNode->getValue() << ") with a Single Red Child (" << iOSNode->getRight()->getValue() << "). (The Red Child must have Two NIL children)" << endl;
			delNode->setValue(iOSNode->getValue());
			Node* p = iOSNode->getParent();
			Node* c = iOSNode->getRight();
			p->getRight() == iOSNode ? p->setRight(c) : p->setLeft(c);
			c->setParent(p);
			c->setBlack();
			iOSNode->~Node();
			return Root;
		}
		//Double Black Use Cases
		cout << "Moving on to Check Cases" << endl;
		if (iOSNode == delNode->getLeft()){
			delNode->setValue(iOSNode->getValue());
			delNode->setLeft(NULL);
			iOSNode->~Node();
			return findRoot(delNode);
		}
		delNode->setValue(iOSNode->getValue());
		cout << "iOS is : " << iOSNode->getValue() << endl;
		Node* p = iOSNode->getParent();
		Node* c = iOSNode->getRight();
		if (c == NULL){
			c = new Node();
			c->setValue(-1);
			c->setParent(p);
		}
		p->getRight() == iOSNode ? p->setRight(c) : p->setLeft(c);
		iOSNode->~Node();
		cout << "C's value is: " << c->getValue() << endl;
		removeCase1(c,Root);
		if (c->getValue() == -1){
			p->getRight() == c ? p->setRight(NULL) : p->setLeft(NULL);
			return findRoot(c);
			c->~Node();
		}
		return findRoot(c);
	}
}
*/
Node* removeOneChild(Node* delNode){
	//Child could be NULL
	Node* c = new Node();
	//delNode->getLeft() != NULL ? c = delNode->getLeft() : c = delNode->getRight();
	if (delNode->getLeft() != NULL){
		c = delNode->getLeft();
		//cout << "Using Left Child of Del Node: " << c->getValue() << endl;
	}
	else if (delNode->getRight() != NULL){
		c = delNode->getRight();
		//cout << "Using Right Child of Del Node: " << c->getValue() << endl;
	}
	else{
		c->setValue(-1);
		c->setBlack();
		//cout << "Del Node has no Children and so it's value is made to be: " << c->getValue() << endl; 
	}
	replaceNode(delNode,c);
	if (isBlack(delNode)){
		if (isRed(c)){
			//cout << "C is red and so just set C to black" << endl;
			c->setBlack();
		}
		else{
			//cout << "Entering Case 1" << endl;
			removeCase1(c,findRoot(c));
		}
	}
	else{
		//cout << "Del Node is Red and so MUST have two NIL Children" << endl;
	}
	//cout << "Replace Node and Do Nothing Else" << endl;
	//cout << "Haven't found Root yet" << endl;
	if (c->getValue() == -1 && c->getParent() == NULL){
		return NULL;
	}
	Node* root = findRoot(c);
	if (c->getValue() == -1){
		c->getParent()->getLeft() == c ? c->getParent()->setLeft(NULL) : c->getParent()->setRight(NULL);
		c->~Node();
	}
	delNode->~Node();
	return root;
}
void removeCase1(Node* c,Node* Root){
	if (c->getParent() != NULL){
		//cout << "Going into Case 2" << endl;
		removeCase2(c,Root);
		return;
	}
	cout << "Case 1" << endl;
	cout << "C(" << c->getValue() << ") is the new Root" << endl;
	cout << "Do Nothing" << endl;
	return;
}
void removeCase2(Node* c,Node* Root){
	Node* s = Sibling(c);
	//cout << "Entered Case 2" << endl;
	if (isRed(s)){
		//bPrint(findRoot(c));
		cout << "Case 2" << endl;
		cout << "Sibling(" << s->getValue() << ") is Red" << endl;
		cout << "Recoloring Parent(" << c->getParent()->getValue() << ") to Red and Sibling(" << s->getValue() << ") to Black.";
		c->getParent()->setRed();
		s->setBlack();
		if (c == c->getParent()->getLeft()){
			cout << "Rotating Left on C(" << c->getValue() << ")" << endl;
			LeftRotate(c->getParent());
		}
		else if (c == c->getParent()->getRight()){
			cout << "Rotating Right on C(" << c->getValue() << ")" << endl;
			RightRotate(c->getParent());
		}
		//bPrint(findRoot(c));
	}
	//cout << "Going into Case 3" << endl;
	removeCase3(c,Root);
}
void removeCase3(Node* c,Node* Root){
	Node* s = Sibling(c);
	//cout << "Entered Case 3" << endl;
	if (isBlack(c->getParent()) && isBlack(s) && isBlack(s->getLeft()) && isBlack(s->getRight()) ){
			//bPrint(findRoot(c));
			cout << "Case 3" << endl;
			cout << "If Parent(" << c->getParent()->getValue() << "), Sibling(" << s->getValue() << "), and Sibling's Children are Black" << endl;
			cout << "Paint Sibling Red." << endl;
			s->setRed();
			//bPrint(findRoot(c));
			//cout << "Going into Case 1" << endl;
			removeCase1(c->getParent(),Root);
	}
	else{
		//cout << "Going into Case 4" << endl;
		removeCase4(c,Root);
	}
}
void removeCase4(Node* c,Node* Root){
	Node* s = Sibling(c);
	//cout << "Entered Case 4" << endl;
	if ( isRed(c->getParent()) && isBlack(s) && isBlack(s->getLeft()) && isBlack(s->getRight())){
		//bPrint(findRoot(c));
		cout << "Case 4" << endl;
		cout << "Parent(" << c->getParent()->getValue() << ") is Red. Sibling(" << s->getValue() << ") and it's Children are Black." << endl;
		cout << "Parent(" << c->getParent()->getValue() << ") is made Black, Sibling is made Red." << endl;
		s->setRed();
		c->getParent()->setBlack();
		//bPrint(findRoot(c));
	}
	else{
		//cout << "Going into Case 5" << endl;
		removeCase5(c,Root);
	}
}
void removeCase5(Node* c,Node* Root){
	Node* s = Sibling(c);
	//cout << "Entered Case 5" << endl;
	if (isBlack(s)){
		
		if( (c == c->getParent()->getLeft()) && (isBlack(s->getRight())) && (isRed(s->getLeft())) ){
			//bPrint(findRoot(c));
			cout << "Case 5" << endl;
			cout << "Sibling(" << s->getValue() << ") is Black, and Child(" << c->getValue() << ") is Left Child of Parent(" << c->getParent()->getValue() << "). S's Right Child is Red" << endl;
			cout << "Sibling is made Red, Sibling's Left Child is made Black and there is a Right Rotation on Sibling" << endl;
			s->setRed();
			s->getLeft()->setBlack();
			RightRotate(s);
			//bPrint(findRoot(c));
		}		
		else if ( (c == c->getParent()->getRight()) && (isBlack(s->getLeft())) && (isRed(s->getRight())) ){
			//bPrint(findRoot(c));
			cout << "Case 5" << endl;
			cout << "Sibling(" << s->getValue() << ") is Black, and Child(" << c->getValue() << ") is Right Child of Parent. S's Right Child is Red" << endl;
			cout << "Sibling is made Red, Sibling's Right Child is made Black and there is a Left Rotation on Sibling" << endl;
			s->setRed();
			s->getRight()->setBlack();
			LeftRotate(s);
			//bPrint(findRoot(c));
		}
	}
	//cout << "Going into Case 6" << endl;
	removeCase6(c,Root);
}
void removeCase6(Node* c,Node* Root){
	Node* s = Sibling(c);
	//cout << "Entered Case 6" << endl;
	//bPrint(findRoot(c));
	cout << "Case 6" << endl;
	cout << "Sibling(" << s->getValue() << ") is Black and Sibling's Right Child is Red. C(" << c->getValue() << ") is the Left Child of Parent(" << c->getParent()->getValue() << ")." << endl;
	cout << "Swap Sibling and Parent(" << c->getParent()->getValue() << ")'s Colors.";
	isBlack(c->getParent()) ? s->setBlack() : s->setRed();
	c->getParent()->setBlack();
	
	if(c == c->getParent()->getLeft()){
		cout << "If C is Left Child of Parent(" << c->getParent()->getValue() << ") set Sibling's Right Child to Black and Left Rotate on C's Parent" << endl;
		s->getRight()->setBlack();
		LeftRotate(c->getParent());
	}
	else{
		cout << "If C is Right Child of Parent(" << c->getParent()->getValue() << ") set Sibling's Left Child to Black and Right Rotate on C's Parent" << endl;
		s->getLeft()->setBlack();
		RightRotate(c->getParent());
	}
	//bPrint(findRoot(c));
}

void print(char prefix[], Node* Root, bool isLeft){
	//This Print Method came from Stack Overflow:
	//https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram?noredirect=1&lq=1
	char* Prefix = NULL;
	if (Root != NULL){
		cout << prefix << (isLeft ? "|-- " : "\\-- ");
		if (Root->isBlack()){
			cout << Root->getValue() << endl;
		}
		else if (Root->isRed()){
			cout << "\033[1;31m" << Root->getValue() << " \033[0m" << endl;
		}
		if (Prefix != NULL){
			delete []Prefix;
		}
		Prefix = new char[100];
		Prefix = strcpy(Prefix,prefix);
		print(strcat(prefix,(isLeft ? "|   " : "    ")), Root->getLeft(), true);
		print(strcat(Prefix,(isLeft ? "|   " : "    ")), Root->getRight(), false);
	}
}

