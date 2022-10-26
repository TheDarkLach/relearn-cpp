#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node{
	public:
		Node(){
			left = NULL;
			right = NULL;
		}
		Node* getLeft(){
			return left;
		}
		Node* getRight(){
			return right;
		}
		char* getVar(){
			return var;
		}
		char* getVarArray(){
			return vararray; 
		}
	private:
		Node* left;
		Node* right;
		char* var;
		char vararray[20];
};

class RBT{
public:
	RBT(){
		right = NULL;
		left = NULL;
		parent = NULL;
		color = 0;//Initially starts Black
	}
	~RBT();
	
	RBT* getParent(){
		return parent;
	}
	RBT* getRight(){
		return right;
	}
	RBT* getLeft(){
		return left;
	}
	
	int getValue(){
		return value;
	}
	
	bool isBlack(){
		if (color == 0){
			return true;
		}
		return false;
	}
	bool isRed(){
		if (color == 1){
			return true;
		}
		return false;
	}
	
	
	void setParent(RBT* newParent){
		parent = newParent;
	}
	void setLeft(RBT* newLeft){
		left = newLeft;
	}
	void setRight(RBT* newRight){
		right = newRight;
	}
	
	void setValue(int newValue){
		value = newValue;
	}
	
	void setBlack(){
		color = 0;
	}
	void setRed(){
		color = 1;
	}
private:
	RBT* parent;
	RBT* left;
	RBT* right;
	int value;
	int color;	
};

void parseInput(vector<char*> parsedInput,char input[100]);
void parseNumbers(char input[1000],vector<int> &integers);
void printVector(vector<int> integers);

int main(){
	RBT* head = new RBT();
	RBT* NIL = new RBT();
	NIL->setBlack();
	NIL->setValue(-1);
	head->setLeft(NIL);
	head->setRight(NIL);
	NIL->setParent(head);
	head->setValue(5);
	cout << NIL->isBlack() << endl;
	if (NIL == NULL){
		cout << "NIL IS NULL" << endl;
	}
	else{
		cout << "NIL IS NOT NULL" << endl;
	}
	/*cout << "Enter a Input: (Using Character Array)\n>>";
	cin.get(node->getVarArray(),21);
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "The Node Array is: " << node->getVarArray() << " and it's size is: " << strlen(node->getVarArray()) << endl;
	*/
	
	/*cout << "Enter a second Input: (Using Character Pointer)\n>>";
	cin.get(node->getVar(),21);
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "The Node Array (with Char Pointer) is: " << node->getVar() << " and it's size is: " << strlen(node->getVar()) << endl;
	*/
	
	/*int spacePointer[2];
	spacePointer[0] = -1;
	spacePointer[1] = 2;
	//cout << spacePointer[1] - spacePointer[0] << endl;
	char newArr[spacePointer[1] - spacePointer[0]];
	newArr[0] = '2';
	newArr[1] = '\0';
	//cout << "Character Pointer size: " << strlen(spacePointer) << endl;
	cout << "Array size: " << (sizeof(spacePointer)/sizeof(*spacePointer)) << endl;
	*/
	
	//char name[]="siva";
    //printf("%-20s\n",name);
    //printf("%20s\n",name);
	/*vector<char*> parsedInput;
	char input[1000];
	cout << "Enter an Expression\n>>";
	cin.get(input,1000);
	cin.clear();
	cin.ignore(10000,'\n');
	//cout << input << endl;
	
	vector<int> integers;
	parseNumbers(input,integers);
	
	printVector(integers);*/
	/*
	for (int i = 0; i < parsedInput.size(); i++){
		Queue.push(parsedInput[i]);
	}
	
	queue <char*> Queue;
	stack <char> Stack;
	*/
	
	srand (time(NULL));
	for(int i = 0; i < 40; i++){
		cout << rand()%10 << endl;
	}
  	/* generate secret number between 1 and 10: */
  	int ID = rand()%10 * pow(10,5) + rand()%10 * pow(10,4) + rand()%10 * pow(10,3) + rand()%10 * pow(10,2) + rand()%10 * pow(10,1) + rand()%10;
	
	float GPA = rand()%5 + rand()%10 * pow(10,-1) + rand()%10 * pow(10,-2);
	
	cout << "ID is: " << ID << endl;
	cout << "GPA is: " << GPA << endl;
}

void printVector(vector<int> integers){
	cout << "Printing Vector: ";
	for (int i = 0; i < integers.size(); i++){
		cout << integers[i] << " ";
	}
	cout << endl;
}

void parseInput(vector<char*> parsedInput, char input[100]){
	int i = 1;
	int spacePointers[2];
	spacePointers[0] = -1;
	while (i < strlen(input)){
		if (input[i] == ' '){
			spacePointers[1] = i;
			int j = 0;
			char* newArr = new char[spacePointers[1] - spacePointers[0]];
			for (int i = spacePointers[0] + 1; i < spacePointers[1]; i++){
				newArr[j] = input[i];
				j = j + 1;
			}
			newArr[j] = '\0';
			cout << "The String is: " << newArr << " and it's size is: " << strlen(newArr) << endl;
			
			//cout << "Seg begin at: " << spacePointers[0] << " Seg end at: " << spacePointers[1] << endl;
			parsedInput.push_back(newArr);
			spacePointers[0] = spacePointers[1];
		}
		i++;
	}
	char newArr[strlen(input) - spacePointers[0]];
	int j = 0;
	for (int i = spacePointers[0] + 1; i < strlen(input); i++){
		newArr[j] = input[i];
		j = j + 1;
	}
	newArr[j] = '\0';
	cout << "The String is: " << newArr << " and it's size is: " << strlen(newArr) << endl;
	parsedInput.push_back(newArr);
	//printVector(parsedInput);
}

void parseNumbers(char input[1000], vector<int> &integers){
	int i = 1;//Index of Input
	int j = 0;//Index of Numbers
	int spacePointers[2];
	spacePointers[0] = -1;
	while (i < strlen(input)){
		if (input[i] == ','){
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


