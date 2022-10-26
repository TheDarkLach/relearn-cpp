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

void print(char prefix[], Node* Root, bool isLeft);

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
				cout << "Inserting: " << integers[i] << endl;
				Node* newNode = new Node();
				newNode->setValue(integers[i]);
				Root = insert(Root, newNode);
				char* str = new char[100];
				str[0] = '\0';
				print(str,Root,false);
				delete []str;
			}
			for (int i = 0; i < integers.size(); i++){
				cout << integers[i] << endl;
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
				cout << "Inserting: " << integers[i] << endl;
				Node* newNode = new Node();
				newNode->setValue(integers[i]);
				Root = insert(Root, newNode);
				char* str = new char[100];
				str[0] = '\0';
				print(str,Root,false);
				delete []str;
			}
			for (int i = 0; i < integers.size(); i++){
				cout << integers[i] << endl;
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
				cout << fileInput << endl;
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
				for(int i = 0; i < integers.size();i++){
					cout << integers[i] << endl;
					//Root = insert(Root, integers[i]);
				}
				
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
					cout << "Inserting: " << integers[i] << endl;
					Node* newNode = new Node();
					newNode->setValue(integers[i]);
					Root = insert(Root, newNode);
				}
				for(int i = 0; i < integers.size();i++){
					cout << integers[i] << endl;
				}
			}
		}
	}
	
	bool stillPlaying = true;
	while (stillPlaying){
		cout << "Would you like to: (Answer with 1,2,3 or 4)\n" <<
		"1. Insert\n" <<
		"2. Print\n" <<
		"3. Delete\n" <<
		"4. Quit\n>>";
		cin >> in;
		if (in == 1){
			cout << "Please enter in one integer\n>>";
			int newInt;
			cin >> newInt;
			Node* newNode = new Node();
			newNode->setValue(newInt);
			Root = insert(Root,newNode);
		}
		else if (in == 2){
			//cout << Root->getRight()->getValue() << endl;
			char* str = new char[100];
			str[0] = '\0';
			print(str,Root,false);
			delete []str;
		}
		else if (in == 3){
			cout << "Sorry, currently unavailable." << endl;
			//cout << "Which value would you like to delete within the tree?\n>>";
		}
		else if (in == 4){
			stillPlaying = false;
			cout << "Program has ended" << endl;
		}
		else{
			//cout << "Please enter in 1,2,3 or 4" << endl;
			char* str = new char[100];
			str[0] = '\0';
			char* out = new char[100];
			out[0] = '\0';
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
	char* str = new char[100];
	str[0] = '\0';
	print(str,Root,false);
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
			cout << "Set Left of: " << Root->getValue() << endl; 
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
			cout << "Set Right of: " << Root->getValue() << endl;
			Root->setRight(newNode);
		}
	}
	newNode->setParent(Root);
}
void insertRepair(Node* newNode){
	//Case 1: If you're adding something into the Root of the tree
	if (newNode->getParent() == NULL){
		cout << "Case 1" << endl << "The new Node is the Root of the Tree and needs to be Black." << endl << "It will be turned Black" << endl;
		insertCase1(newNode);
	}
	//Case 2: If the Parent is Black then nothing is violated
	else if (newNode->getParent()->isBlack()){
		cout << "Case 2" << endl << "Parent is Black" << endl << "Nothing will be changed" << endl;
		insertCase2(newNode);
	}
	//Case 3: Parent and Uncle are Red (Red cannot have Red Child)
	//Note I am not checking that the Parent is Red because the other if loops have already checked for me
	else if (Uncle(newNode) != NULL && Uncle(newNode)->isRed()){
		cout << "Case 3" << endl << "Parent and Uncle are Red" << endl << "They will be turned black and grandParent will be recursively be called upon" << endl;
		insertCase3(newNode);
	}
	//If we are down here we know that Parent exists and is red (This violating 4)
	//We also know that the Uncle either A) Doesn't exist, or B) is black (This violating 5)
	else{
		cout << "Case 4" << endl << "Parent is Red, Uncle is Black" << endl << "Rotate and Set GrandParent to Red, Set Parent to Black" << endl;
		insertCase4(newNode);
	}
}
//Turn the Root to Black
void insertCase1(Node* Root){
	Root->setBlack();
}
//Change nothing
void insertCase2(Node* Root){
	return;
}
//Change the Uncle and the Parent to Black, and make grandparent Red.
//This may cause a violating in grandparent and so you must call on insertRepair on grandParent
void insertCase3(Node* Root){
	Root->getParent()->setBlack();
	Uncle(Root)->setBlack();
	grandParent(Root)->setRed();
	insertRepair(grandParent(Root));
}
//There are two cases, either the parent is larger or smaller than it's node
void insertCase4(Node* Root){
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
//This Print Method came from Stack Overflow:
//https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram?noredirect=1&lq=1
void print(char prefix[], Node* Root, bool isLeft){
	char* Prefix = NULL;
	if (Root!=NULL){
		cout << prefix << (isLeft ? "|__ " : "\\__ ");
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

