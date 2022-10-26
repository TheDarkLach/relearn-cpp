/*
 * Author: Zareef Amyeen
 * Date of Creation: January 28, 2019
 * Date of Finish: February 1, 2019
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

//Infix to Postfix functions
void infixtopostfix (char input[100],stack <char>& Stack, queue <char>& Queue);
int precedence(char op);

//Construct Tree function
void constructTree(stack <Node*>& ExpressionTree, queue <char> Queue);

//Evaluating/Printing Tree Functions
void Prefix(Node* Root);
void Infix(Node* Root);
void Postfix(Node* Root);

//Print Functions
void printQueue(queue <char> Queue);
void printStack(stack <char> Stack);

//Quality of Life so I don't have to rewrite so much code
bool isOperand(char op);

int main(){
	stack <char> Stack;
	queue <char> Queue;
	char input[100];
	
	
	cout << "Enter an Expression\n>>";
	cin.get(input,100);
	cin.clear();
	cin.ignore(10000,'\n');
	//cout << input << endl;
	
	infixtopostfix(input,Stack,Queue);
	//printQueue(Queue);
	
	stack <Node*> ExpressionTree;
	constructTree(ExpressionTree,Queue);
	
	cout << "What way would you like the expression to output? (Answer with 1,2, or 3) \n1.Prefix\n2.Infix\n3.Postfix\n>>";
	char in;
	cin >> in;
	//cout << endl;
	while(in != '4'){
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
		cin >> in;
	}
	
}

//An Operand is a Digit or a Letter
bool isOperand(char op){
	//Alnum = Digit or Number
	if (isalnum(op)){
		return true;
	}
	return false;
}

void printQueue (queue <char> Queue){
	cout << "Printing Postfix Expression:" << endl;
	while(!Queue.empty()){
		cout << Queue.front() << " ";
		Queue.pop();
	}
	cout << endl;
}

void printStack(stack <char> Stack){
	cout << "Printing Stack:" << endl;
	while (!Stack.empty()) { 
        cout << Stack.top() << " "; 
        Stack.pop(); 
    }
    cout << endl;
}

//Algorithm from Shunting Yard Algorithm on Wikipedia
void infixtopostfix (char input[100],stack <char>& Stack, queue<char>& Queue){
	int i = 0;
	while (i < strlen(input)){
		if (input[i] == ' '){}
		//Operands
		else if (isalnum(input[i])){
			//cout << input[i] << " IS NUMBER OR DIGIT" << endl;
			Queue.push(input[i]);
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		else if (input[i] == '('){
			//cout << input[i] << " IS A LEFT BRACKET" << endl;
			Stack.push(input[i]);
			
			//printQueue(Queue);
			//printStack(Stack);
			//cout << endl;
		}
		else if (input[i] == ')'){
			//cout << input[i] << " IS A RIGHT BRACKET" << endl;
			while (Stack.top() != '('){
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
				while ((precedence(Stack.top()) > precedence(input[i]) || ((precedence(Stack.top()) == precedence(input[i])) && (Stack.top() != '^'))) && (Stack.top() != '(')){
					//cout << "PRECEDENCE STUFF" << endl;
					Queue.push(Stack.top());
					Stack.pop();
					if (Stack.empty()){
						break;
					}
				}
			}
			//cout << input[i] << " IS AN OPERATOR" << endl;
			Stack.push(input[i]);
			
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

int precedence (char op){
	if (op == '(' || op == ')'){
		return 4;
	}
	else if (op == '^'){
		return 3;
	}
	else if (op == '*' || op == '/'){
		return 2;
	}
	else if (op == '+' || op == '-'){
		return 1;
	}
	return 0;
}

void constructTree(stack <Node*>& Tree, queue <char> Queue){
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
