/*
 * Author: Zareef Amyeen
 * Date of Creation: January 28, 2019
 * Date of Finish: February 14, 2019
 * Objective 1: Translate from Infix to Postfix
 * Example Input: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
 * Example Output: 3 4 2 * 1 5 − 2 3 ^ ^ / +
 * Objective 2: Make a Binary Expression Tree from a Binary Node Class 
 *    *
 *   4 2
 *  
 */
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <queue>
#include "Node.h"

using namespace std;

void infixtopostfix (vector<char*>& parsedInput, queue<char*>& Queue);
int precedence (char* op);

//Construct Tree function
void constructTree(stack <Node*>& Tree, queue <char*>& Queue);

//Evaluating/Printing Tree Functions
void Prefix(Node* Root);
void Infix(Node* Root);
void Postfix(Node* Root);

//Print Functions
void printQueue (queue <char*> Queue);
void printStack (stack <char*> Stack);
void printVector (vector <char*> parsedInput);
//Quality of Life so I don't have to rewrite so much code
//Digit or Number
bool isOperand(char* op);

void parseInput(vector<char*> &parsedInput, char input[100]);

int main(){
	queue <char*> Queue;
	char input[100];
	vector<char*> parsedInput;
	
	cout << "Enter an Infix Expression\n>>";
	cin.get(input,100);
	cin.clear();
	cin.ignore(10000,'\n');
	//cout << input << endl;
	parseInput(parsedInput,input);
	//printVector(parsedInput);
	infixtopostfix(parsedInput,Queue);
	//printQueue(Queue);
	
	stack <Node*> ExpressionTree;
	constructTree(ExpressionTree,Queue);
	
	cout << "What way would you like the expression to output? (Answer with 1,2, or 3) \n1.Prefix\n2.Infix\n3.Postfix\n>>";
	char in;
	cin >> in;
	//cout << endl;
	//while(in != '4'){
		if (in == '1'){
			cout << "Your Prefix Expression is: ";
			Prefix(ExpressionTree.top());
			cout << endl;
		}
		else if (in == '2'){
			cout << "Your Infix Expression is: ";
			Infix(ExpressionTree.top());
			cout << endl;
		}
		else if (in == '3'){
			cout << "Your Postfix Expression is: ";
			Postfix(ExpressionTree.top());
			cout << endl;
		}
		//cin >> in;
	//}
	
}

void parseInput(vector<char*> &parsedInput, char input[100]){
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
			//cout << "The String is: " << newArr << " and it's size is: " << strlen(newArr) << endl;
			
			//cout << "Seg begin at: " << spacePointers[0] << " Seg end at: " << spacePointers[1] << endl;
			parsedInput.push_back(newArr);
			spacePointers[0] = spacePointers[1];
		}
		i++;
	}
	char* newArr = new char[strlen(input) - spacePointers[0]];
	int j = 0;
	for (int i = spacePointers[0] + 1; i < strlen(input); i++){
		newArr[j] = input[i];
		j = j + 1;
	}
	newArr[j] = '\0';
	//cout << "The String is: " << newArr << " and it's size is: " << strlen(newArr) << endl;
	parsedInput.push_back(newArr);
	//printVector(parsedInput);
}

void constructTree(stack <Node*>& Tree, queue <char*>& Queue){
	while (!Queue.empty()){
		//Top of Queue is Operand
		if (isOperand(Queue.front())){
			//cout << "Front of Queue is an OPERAND and it's value is: " << Queue.front() << endl;
			Node* newNode = new Node();
			newNode->setValue(Queue.front());
			Queue.pop();
			Tree.push(newNode);
		}
		else{
			//cout << "Front of Queue is an OPERATOR and it's value is: " << Queue.front() << endl;
			Node* newNode = new Node();
			newNode->setValue(Queue.front());
			Queue.pop();

			//cout << "Setting Right value to: " << Tree.top()->getValue() << endl;
			newNode->setRight(Tree.top());//Order of operation?
			Tree.pop();
			//cout << "Setting Left value to: " << Tree.top()->getValue() << endl;
			newNode->setLeft(Tree.top());
			Tree.pop();
			
			Tree.push(newNode);
		}
	}
	//cout << "The size of the Stack is: " << Tree.size() << endl;
}

//Algorithm from Shunting Yard Algorithm on Wikipedia
void infixtopostfix (vector<char*> &parsedInput, queue<char*>& Queue){
	stack<char*> Stack;
	int i = 0;
	while (i < parsedInput.size()){
		if (strlen(parsedInput[i]) != 1 || isOperand(parsedInput[i])){
			//cout << parsedInput[i] << " IS NUMBER OR DIGIT" << endl;
			Queue.push(parsedInput[i]);
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		else if (strcmp(parsedInput[i],"(") == 0){
			//cout << parsedInput[i] << " IS A LEFT BRACKET" << endl;
			Stack.push(parsedInput[i]);
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		else if (strcmp(parsedInput[i],")") == 0){
			//cout << parsedInput[i] << " IS A RIGHT BRACKET" << endl;
			while (strcmp(Stack.top(),"(") != 0){
				Queue.push(Stack.top());
				Stack.pop();
				if (Stack.empty()){
					break;
				}
			}
			//Deleting the ')'
			Stack.pop();
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		else {
			if (!Stack.empty()){
			//cout << "STACK IS NOT EMPTY" << endl;
				while ( (precedence(Stack.top()) > precedence(parsedInput[i]) || ( (precedence(Stack.top()) == precedence(parsedInput[i])) && (strcmp(Stack.top(),"^") != 0) ) ) && (strcmp(Stack.top(),"(") != 0)){
					Queue.push(Stack.top());
					Stack.pop();
					if (Stack.empty()){
						break;
					}	 
				}
			}
			//cout << parsedInput[i] << " IS AN OPERATOR" << endl;
			
			Stack.push(parsedInput[i]);
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		i = i+1;
	}
		
	while (!Stack.empty()){
		Queue.push(Stack.top());
		Stack.pop();
		
		//printQueue(Queue);
		//printStack(Stack);
		//cout << endl;
	}
	//printQueue(Queue);
}

int precedence (char* op){
	if (strcmp(op,"(") == 0 || strcmp(op,")") == 0 ){
		return 4;
	}
	else if (strcmp(op,"^") == 0){
		return 3;
	}
	else if (strcmp(op,"*") == 0 || strcmp(op,"/") == 0){
		return 2;
	}
	else if (strcmp(op,"+") == 0 || strcmp(op,"-") == 0){
		return 1;
	}
	return 0;
}

bool isOperand(char* op){
	//Alnum = Digit or Number
	if (isalnum(op[0])){
		return true;
	}
	return false;
}

void printQueue (queue <char*> Queue){
	cout << "Printing Queue:" << endl;
	while(!Queue.empty()){
		cout << Queue.front() << " ";
		Queue.pop();
	}
	cout << endl;
}
void printStack(stack <char*> Stack){
	cout << "Printing Stack:" << endl;
	while (!Stack.empty()) { 
        cout << Stack.top() << " "; 
        Stack.pop(); 
    }
    cout << endl;
}
void printVector(vector <char*> parsedInput){
	cout << "Printing Vector: ";
	for (int i = 0; i < parsedInput.size(); i++){
		cout << parsedInput[i] << " ";
	}
	cout << endl;
}

void Prefix(Node* Root){
	
	/*Algorithm prefix (tree)
	Print the prefix expression for an expression tree.
 	Pre : tree is a pointer to an expression tree
 	Post: the prefix expression has been printed
 	if (tree not empty)
    	print (tree token)
    	prefix (tree left subtree)
   		 prefix (tree right subtree)
	end if
	end prefix*/
	
	if (Root!=NULL){//Indicates Tree is not empty
		cout << Root->getValue() << " ";
		Prefix(Root->getLeft());
		Prefix(Root->getRight());
	}
}
void Infix(Node* Root){
	
	/*Algorithm infix (tree)
	Print the infix expression for an expression tree.
	Pre : tree is a pointer to an expression tree
 	Post: the infix expression has been printed
 	if (tree not empty)
 	   if (tree token is operator)
 	      print (open parenthesis)
 	   end if
 	   infix (tree left subtree)
 	   print (tree token)
	    infix (tree right subtree)
		if (tree token is operator)
	       print (close parenthesis)
	    end if
	 end if
	end infix*/

	if (Root != NULL){
		if (!isOperand(Root->getValue())){
			cout << "( ";
		}
		Infix(Root->getLeft());
		cout << Root->getValue() << " ";
		Infix(Root->getRight());
		if (!isOperand(Root->getValue())){
			cout << ") ";
		}
	}
}
void Postfix(Node* Root){
	
	/*Algorithm postfix (tree)
	Print the postfix expression for an expression tree.
	Pre : tree is a pointer to an expression tree
	Post: the postfix expression has been printed
	if (tree not empty)
		postfix (tree left subtree)
	    postfix (tree right subtree)
	    print (tree token)
	end if
	end postfix*/
	
	if (Root != NULL){
		Postfix(Root->getLeft());
		Postfix(Root->getRight());
		cout << Root->getValue() << " ";
	}
}
