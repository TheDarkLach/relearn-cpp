#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

class Node{
	public:
		Node();
		//Getters
		Node* getRight();
		Node* getLeft();
		char getValue();
		//Setters
		void setLeft(Node* newLeft);
		void setRight(Node* newRight);
		void setValue(char newValue);
	private:
		Node* left;
		Node* right;
		char value;
};

#endif