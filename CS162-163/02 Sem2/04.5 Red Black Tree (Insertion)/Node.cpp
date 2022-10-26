//
//  Node.cpp
//  Red Black Tree
//
//  Created by Zareef Amyeen on 3/30/19.
//  Copyright © 2019 Zareef Amyeen. All rights reserved.
//

#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(){
    right = NULL;
    left = NULL;
    parent = NULL;
    color = 1;//Red
}
Node::~Node(){
}

//Getters
Node* Node::getParent(){
    return parent;
}
Node* Node::getRight(){
    return right;
}
Node* Node::getLeft(){
    return left;
}

int Node::getValue(){
    return value;
}

bool Node::isBlack(){
	if (color == 0){
		return true;
	}
	return false;
}
bool Node::isRed(){
	if (color == 1){
		return true;
	}
	return false;
}

//Setters
void Node::setParent(Node* newParent){
    parent = newParent;
}
void Node::setLeft(Node* newLeft){
    left = newLeft;
}
void Node::setRight(Node* newRight){
    right = newRight;
}

void Node::setValue(int newValue){
    value = newValue;
}

void Node::setBlack(){
	color = 0;
}
void Node::setRed(){
	color = 1;
}