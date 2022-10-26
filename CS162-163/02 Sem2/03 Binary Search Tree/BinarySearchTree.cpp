/*
 * Date of Creation: March 13th, 2019
 *
 *
 */
 
 #include <iostream>
 #include <fstream>
 #include <vector>
 #include <stdio.h>
 #include <cmath>
 #include <string.h>
 #include "Node.h"
 
 using namespace std;
 
 void parseNumbers(char input[], vector<int> &integers);
 
 Node* insert(Node* Root, int integer);
 
 void print(char prefix[], Node* Root, bool isLeft);
 
 Node* deleteNode(Node* Root,int value);
 
 int main(){
 	Node* Root = NULL;
 	cout << "How would you like to enter your list? (Answer with 1 or 2) \n" << 
 	"1.Manually through the console\n" << 
 	"2.Through a text file\n>>";
 	int in;
	cin >> in;
	
	//First Insertion Stage
	vector<int> integers;
	if (in == 1){
		char input[100];
		cin.ignore(10000,'\n');
		cout << "Enter in your Numbers Separated by a Space:\n>>";
		cin.get(input,1000);
		cin.clear();
		cin.ignore(10000,'\n');
		
		//cout << input << endl;
		parseNumbers(input,integers);
		for(int i = 0; i < integers.size();i++){
				//cout << integers[i] << endl;
				Root = insert(Root, integers[i]);
		}
	}
	else if(in == 2){
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
			parseNumbers(fileInput,integers);
			for(int i = 0; i < integers.size();i++){
				//cout << integers[i] << endl;
				Root = insert(Root, integers[i]);
			}
			//cout << Root->getValue() << endl;
			//cout << Root->getLeft()->getValue() << endl;
			//cout << Root->getRight()->getValue() << endl;
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
			Root = insert(Root,newInt);
		}
		else if (in == 2){
			//cout << Root->getRight()->getValue() << endl;
			char* str = new char[100];
			str[0] = '\0';
			print(str,Root,false);
			delete []str;
		}
		else if (in == 3){
			cout << "Which value would you like to delete within the tree?\n>>";
			int deleteValue;
			cin >> deleteValue;
			Root = deleteNode(Root,deleteValue); 
		}
		else if (in == 4){
			stillPlaying = false;
			cout << "Program has ended" << endl;
		}
	}
}

void parseNumbers(char input[], vector<int> &integers){
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
			cout << "Number is: " << number << endl << endl;
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
	cout << "Number is: " << number << endl << endl;
	integers.push_back(number);
}

Node* insert(Node* Root, int integer){
	//cout << "Entered Function" << endl;
	if (Root == NULL){
		//cout << "Setting Value" << endl;
		Root = new Node();
		Root->setValue(integer);
		return Root;
	}
	else if (integer == Root->getValue()){
		cout << "Sorry, you cannot input two of the identical number." << endl;
	}
	else if (integer < Root->getValue()){
		//cout << "GOING LEFT" << endl;
		Root->setLeft(insert(Root->getLeft(),integer));
	}
	else if (integer > Root->getValue()){
		//cout << "GOING RIGHT" << endl;
		Root->setRight(insert(Root->getRight(),integer));
	}
	return Root;
}

//This Print Method came from Stack Overflow: 
//https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram?noredirect=1&lq=1
void print(char prefix[], Node* Root, bool isLeft){
	char* Prefix = NULL;
	if (Root!=NULL){
		cout << prefix << (isLeft ? "├── " : "└── ") << Root->getValue() << endl;
		if (Prefix != NULL){
			delete []Prefix;
		}
		Prefix = new char[100];
		Prefix = strcpy(Prefix,prefix);
		print(strcat(prefix,(isLeft ? "│   " : "    ")), Root->getLeft(), true);
		print(strcat(Prefix,(isLeft ? "│   " : "    ")), Root->getRight(), false);
	}
}

Node* deleteNode(Node* Root,int value){
	if (Root == NULL){
		//cout << "No such value exists within the tree" << endl;
		return Root;
	}
	else if (value < Root->getValue()){
		//cout << "Node has value: " << Root->getValue() << " which is greater than the Node we are searching for, with value: " << value << endl;
		Root->setLeft(deleteNode(Root->getLeft(),value));
	}
	else if (value > Root->getValue()){
		//cout << "Node has value: " << Root->getValue() << " which is less than the Node we are searching for, with value: " << value << endl;
		Root->setRight(deleteNode(Root->getRight(),value));
	}
	else{
		//cout << "Node has value: " << Root->getValue() << endl;
		if (Root->getLeft() == NULL){
			//cout << "Node has no Left Child, or No Children" << endl;
			Node* temp = new Node();
			temp = Root->getRight();
			Root->~Node();
			return temp;
		}
		else if (Root->getRight() == NULL){
			//cout << "Node has no Right Child" << endl;
			Node* temp = new Node();
			temp = Root->getLeft();
			Root->~Node();
			return temp;
		}
		else{
			//cout << "Node has two Children" << endl;
			Node* parent = Root->getRight(); 
			
			// Find Minimum Node
			Node* child = Root->getRight(); 
			
			while (child->getLeft() != NULL) { 
				parent = child; 
				child = child->getLeft(); 
			}
			if (parent != NULL){
				//cout << "Parent is: " << parent->getValue() << endl;
			}
			if (child != NULL){
				//cout << "Child is: " << child->getValue() << endl;
			}
			if (parent == child){
				//cout << "Parent is Child" << endl;
				Root->setRight(NULL);
				Root->setValue(child->getValue());
			}
			else{
				//cout << "Parent is not Child" << endl;
				parent->setLeft(child->getRight());
				Root->setValue(child->getValue());
			}
			return Root;
		}
	}
	return Root;
}
