/**
Graph Creator Description:

Graph creator with breadth first search.                 

Why are we doing this?  Graphs are a generalized form of trees, heaps, linked lists, etc.  They are useful in a variety of situations.

Implementation:  Create a program which can create graphs (we are using weighted edge, directed graphs), and it can search for the shortest path in the graph using Dijkstra's Algorithm (this is a famous algorithm you can go look up).  Use an adjacency table for the graph, which can be printed out. (You may assume that no more than 20 vertices will be in the table.) I HIGHLY recommend that you have the ability to print out the adjacency table, for debugging purposes.

Add Vertex: Enter a label for a vertex. Add it to the graph. (5 points)

Add Edge: Enter two node names and a weight (number). Add an edge between them, from the first node to the second node. (5 points)

Remove Vertex: Enter a vertex label and remove it from the graph. Remove all edges to that vertex.  (5 points)

Remove Edge: Enter two vertex labels, and remove an edge between them.  (5 points)

Find Shortest Path: Enter two vertex labels. Starting at the first label, use Dijkstra's algorithm to find a path between the first vertex and the last vertex. Return the shortest path (and total) if it exists, or return that no path exists.  (5 points)

Comments. (5 points)

Total points: 30 points
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

class Vertex{
public:
	//Getter does the same as Setter - This is bad coding practice, I know
	char* getName(){
		return name;
	}
	
private:
	char name[10];
};

class Edge{
public:
	Edge(){
		start = NULL;
		end = NULL;
	}
	~Edge(){
		start->~Vertex();
		end->~Vertex();
		delete[] name;
	}
	
	char* getName(){
		return name;
	}
	
	Vertex* getStart(){
		return start;
	}
	
	Vertex* getEnd(){
		return end;
	}
private:
	char* name;
	Vertex* start;
	Vertex* end;
};

void print1(vector<vector<int> > adj, vector<Vertex*> Vertices, int lvertexname);

int main(){
	vector< vector <int> > adjacency;
	vector<Vertex*> Vertices;
	cout << "Welcome to Graph Creator!" << endl;
	bool running = true;
	int lvertexname = 0;//Keeps track of the longest vertex name
	while (running){
		cout << "Would you like to:\n" << 
		"1. Add a Vertex\n" << 
		"2. Add an Edge (between two vertices)\n" <<
		"3. Remove a Vertex\n" <<
		"4. Remove an Edge\n" << 
		"5. Print the Adjacency Matrix\n" << 
		"6. Find the Shortest Path between two Vertices\n" <<
		"7. Quit\n>>";
		int in;
		cin >> in;
		if (in == 1){
			cout << "What is the name of the vertex that you want to add?\n>>";
			Vertex* newVertex = new Vertex();
			cin.ignore(10000,'\n');
			cin.get(newVertex->getName(),11);
			cin.clear();
			cin.ignore(10000,'\n');
			
			strlen(newVertex->getName()) > lvertexname ? lvertexname = strlen(newVertex->getName()) : lvertexname = lvertexname;
			cout << "Longest Vertex Name is: " << lvertexname << endl;
			//cout << newVertex->getName() << endl;
			Vertices.push_back(newVertex);
			//cout << Vertices.size() << endl;
			vector<int> newVector;
			for (int i = 0; i < Vertices.size();i++){
				newVector.push_back(0);
			}
			adjacency.push_back(newVector);
			cout << "Adjacency Size is: " << adjacency.size() << endl;
		}
		else if (in == 2){
			cout << "What is the name of the edge that you want to add?\n>>";
			
			cout << "What will the start vertex be?\n>>";
			
			cout << "What will the end vertex be?\n>>";
		}
		else if (in == 3){
			cout << "What is the name of the vertex that you want to remove?\n>>";
			char name[10];
			cin.ignore(10000,'\n');
			cin.get(name,11);
			cin.clear();
			cin.ignore(10000,'\n');
			for (int i = 0; i < Vertices.size();i++){
				if (strcmp(name,Vertices[i]->getName()) == 0){
					cout << "i is: " << i << endl;
					break;
				}
			}
		}
		else if (in == 4){
				cout << "What is the name of the start vertex?\n>>";
				
				cout << "What is the name of the end vertex?\n>>";
		}
		else if (in == 5){
			print1(adjacency, Vertices, lvertexname);
		}
		else if (in == 6){
			cout << "What is the name of the start vertex\n>>";
			
			cout << "What is the name of the end vertex\n>>";
		}
		else if (in == 7){
			cout << "Graph Creator has closed" << endl;
			running = false;
		}
		else{
			cout << "Please enter in a number 1 through 7" << endl;
		}
	}
}

/*void printArrayForm(int a){
			cout << "The Heap in Array Form is: " << endl;
			for (int i = 0; i < 14*a-1; i++){
				if (i%14 == 0){
					cout << "+";
				}
				else{
					cout << "-";
				}
			}
			cout << "-+";
			cout << endl << "| ";
			for (int i = 0; i < a; i++){
				printf("%7d(%2d) | ",heap[i],i);
			}
			cout << endl;
			for (int i = 0; i < 14*a-1; i++){
				if (i%14 == 0){
					cout << "+";
				}
				else{
					cout << "-";
				}
			}
			cout << "-+" << endl;
		}*/
/*void print2(vector<vector<int> > adj, vector<Vertex*> Vertices,int lvertexname){
	int chararraysize = ((adj.size()+1)*lvertexname) + (adj.size()+1);
}*/

void print1(vector<vector<int> > adj, vector<Vertex*> Vertices,int lvertexname){
	int chararraysize = ((adj.size()+1)*lvertexname) + (adj.size()+1);
	char output[chararraysize][chararraysize];
	for (int i = 0; i < strlen(output[0]); i++){
		for (int j = 0; j < strlen(output[0]); j++){
			if (j < 2 && i < lvertexname+1){
				output[j][i] = ' ';
			}
		}
	}
	for (int i = 0; i < strlen(output[0]); i++){
		for (int j = 0; j < strlen(output[0]); j++){
			cout << output[i][j];
		}
		cout << endl;
	}
}