//
//  Node.hpp
//  Red Black Tree
//
//  Created by Zareef Amyeen on 3/30/19.
//  Copyright © 2019 Zareef Amyeen. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <iostream>

using namespace std;

class Node{
public:
	Node();
	~Node();
	
	//Getters
	Node* getParent();
	Node* getRight();
	Node* getLeft();
	
	int getValue();
	
	bool isBlack();
	bool isRed();
	
	//Setters
	void setParent(Node* newParent);
	void setLeft(Node* newLeft);
	void setRight(Node* newRight);
	
	void setValue(int newValue);
	
	void setBlack();
	void setRed();
private:
	Node* parent;
	Node* left;
	Node* right;
	int value;
	int color;
};

#endif
