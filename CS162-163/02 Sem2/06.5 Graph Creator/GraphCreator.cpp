/**
Name: Zareef Amyeen
Date: June 14th, 2019
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
#include <math.h>
#include <iomanip>
#include <queue>
#include <cstring>
using namespace std;

int main(){
	
	vector<char*> Vertices;

	//Adjacency Matrix
	int adj[20][20];
	//Initialization of the Matrix (all values as -1)
	for(int columns = 0; columns <= 19; columns++){
		for (int rows = 0; rows <= 19; rows++){
			adj[columns][rows] = -1;
		}
	}
  	bool running = true;
  	cout << "Welcome to Graph Creator" << endl;
	while (running ){
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
		cin.get();
		
		if (in == 1){
			cout << "What is the name of the vertex that you want to add?\n>>";

			char* input = new char[100];
			cin.get(input,100);
			cin.get();

			//Not empty
			if(Vertices.size() != 0){
				int z;
				for(z = 0; z <= Vertices.size()-1; z++){
					if (strcmp(Vertices[z],input) == 0){	      
						break;
					}
				}
				if (z <= Vertices.size()-1){
						cout << "Node already exists" << endl;
				}
				else{
						cout << "Vertex " << input << " is created. " << endl;
						Vertices.push_back(input); // put this in the vector of all nodes
						adj[Vertices.size()-1][Vertices.size()-1] = 0; //the distance of a node to itsself is always 0
				}  
			}
			else{
				cout << "Vertex " << input << " is created. " << endl;
				Vertices.push_back(input); // put this in the vector of all nodes
				adj[Vertices.size()-1][Vertices.size()-1] = 0; //the distance of a node to itsself is always 0
			}
		}
		else if (in == 2){
			char* start = new char[100];
			char* end = new char[100];
			int weight = 0;
			cout << "What's the name of the starting vertex?\n>>";

			cin.get(start,100);
			cin.get();
			
			cout << "What's the name of the ending vertex?\n>>";
			
			cin.get(end,100);
			cin.get();
			
			cout<< "What's the weight of the edge going from " << start << " to " << end << " ?\n>>";

			cin >> weight;
			cin.get();
			
			if (strcmp(start,end) == 0){
				cout << "Can't connect a node with itself."  << endl;
			}
			else{
				int column; // column
				for(column = 0; column <= Vertices.size()-1; column++){
					if (strcmp(Vertices[column] , start) == 0){
						break;
					}
				}
				int row; //row
				for(row = 0; row <= Vertices.size()-1; row++){
					if (strcmp(Vertices[row],end) == 0){
						break;
					}
				}
	      /*
		cout << q << endl;
		cout << w << endl;
		cout << vertex.size() -1 << endl;*/
				if (column > Vertices.size()-1){
					cout << "No such start vertex exists" << endl;
				}
				else if (row > Vertices.size()-1){
					cout << "No such end vertex exists" << endl;
				}
				else{
					adj[column][row] = weight;

					cout << "The weight that goes from "<< start << " to " << end << " is: " << weight << endl;
				}
			}
		}
		else if (in == 3 ){
			//delete a vertex
			cout << "What's the name of the vertex that you would like to delete?\n>>";

			char* input = new char[100];
			cin.get(input,100);
			cin.get();

			if(Vertices.size() != 0){
				int z = 0;
				for(z = 0; z <= Vertices.size()-1; z++){
					if (strcmp(Vertices[z],input) == 0){	      
						break;
					}
				}
				if ((z <= Vertices.size()-1)){
					cout << "Vertex " << input << " has been deleted" << endl;
					
					Vertices.erase(Vertices.begin() + z);
					for(int i = 0; i < Vertices.size(); i++ ){
						cout << Vertices.at(i) << endl;
					}
					cout << z << endl;
					//if deleted vertex is the last one in the list, then just set that row and column to -1
					if (z == Vertices.size()){
						for(int row = 0; row<Vertices.size(); row++){
							adj[z][row] = -1;
						}
						for(int column = 0; column < Vertices.size(); column++){
							adj[column][z] = -1;
						}
					}
				//else fill the blank with stuff afterward
				else{
					for(int g = 0; g < z;g++){
						for(int i = z+1; i <= Vertices.size();i++){
							adj[i-1][g]=adj[i][g];
							adj[i][g] = -1;
						}
					}
					for(int g = 0; g < z; g++){
						for(int i = z+1; i <= Vertices.size(); i++){
							adj[g][i-1]=adj[g][i];
							adj[g][i] = -1;
						}
					}
					for(int g = z+1; g <= Vertices.size(); g++ ){
						for(int i = z+1; i <= Vertices.size(); i++ ){
							adj[i-1][g-1]=adj[i][g];
							adj[i][g] = -1;
						}
					}
					for(int i = Vertices.size();i< 20; i++){
						for(int g = 0; g < 20; g++){
							adj[i][g] = -1;
						}
					}
					for(int g = Vertices.size(); g< 20; g++){
						for(int i = 0; i < 20; i++){
							adj[i][g] = -1;
						}
					}
					for(int i = 0; i < 20; i++){
						adj[i][i] = 0;
					}
				}
			}
				else{
					cout << "Vertex " << input << " doesn't exist." << endl;
				}
			}
			else{
				cout << "There is no such vertex at all! " << endl;
			}
		}
		else if (in == 4){
			char* start = new char[100];
			char* end = new char[100];
			int weight = 0;
			cout << "What's the name of the starting vertex?\n>>";

			cin.get(start,100);
			cin.get();
			cout << "What's the name of the ending vertex?\n>>";
			
			cin.get(end,100);
			cin.get();
			if (strcmp(start,end) == 0){
				cout << "Can't delete a Node's connection to itself. "  << endl;
			}
			else{
				int q; // column
				for(q = 0; q <= Vertices.size()-1; q++){
					if (strcmp(Vertices[q],start) == 0){
						break;
					}
				}
				int w ; //row
				for(w = 0; w <= Vertices.size()-1; w++){
					if (strcmp(Vertices[w],end) == 0){
						break;
					}
				}
	      		/*
		cout << q << endl;
		cout << w << endl;
		cout << vertex.size() -1 << endl;*/
				if (q > Vertices.size()-1){
					cout << "The starting vertex could not be found" << endl;
				}
				else if (w > Vertices.size()-1){
					cout << "The ending vertex could not be found" << endl;
				}
				else{
					adj[q][w] = -1;
					cout << "The weight that goes from "<< start << " to " << end << " is deleted" << endl;
				}
			}
		}
		else if (in == 5){

			// print the a b c on top
			for(vector<char*>::iterator v = Vertices.begin(); v != Vertices.end(); v++ ){
				cout << *v << " ";
			}
			cout << endl;
			// print a and all of A's distance to abc...
			//then move on to B's distanec to abc... for a range of the numbers of vertex - 1 as index
			vector<char*> :: iterator b = Vertices.begin();
			for (int a = 0; a<= Vertices.size()-1; a++){
				cout << *b << " ";
				for (int c = 0; c<= Vertices.size()-1; c++){
					cout << adj[a][c] << " ";
				}
				cout << endl;
				b++;
			}
		}
		else if (in == 6){
			char* start = new char[100];
			char* end = new char[100];
			int weight = 0;
			cout << "What's the name of the starting vertex?\n>>"; 
			
			cin.get(start,100);
			cin.get();
			cout << "What's the name of the ending vertex?\n>>";
			cin.get(end,100);
			cin.get();	 
			if (strcmp(start,end) == 0){
				cout << "A node's distance to itself is always 0. "  << endl;
			}
			else{
				int q ; // column
				for( q = 0; q <= Vertices.size()-1; q++){
					if (strcmp(Vertices[q],start) == 0){
						break;
					}
				}
				int w ; //row
				for(w = 0; w <= Vertices.size()-1; w++){
					if (strcmp(Vertices[w],end) == 0){
						break;
					}
				}
	      		/*
		cout << q << endl;
		cout << w << endl;
		cout << vertex.size() -1 << endl;*/
				if (q > Vertices.size()-1){
					cout << "Could not find the start vertex" << endl;
				}
				else if (w > Vertices.size()-1){
					cout << "Could not find the end vertex" << endl;
				}
				else{
					// a queue for all the path
					int size = Vertices.size();
					int arra [size][size];
					int go = q;
					int stop = w;
					for(int i = 0; i< size; i++){
						for(int k = 0; k< size; k++){
							arra[i][k] = -1;
						}  
					}
					int shortest = 0;
					int index = go;
					int indexx = 0;
					vector <int> whereihavebeen;
					for(int i=0; i<size; i++){
						for(int k = 0; k < size; k++){
							if(adj[index][k] != -1){
								if ((i == 0) || (arra[i-1][k] == -1)){
									arra[indexx][k] = adj[index][k] + shortest;
									// cout << arr[index][k] <<" + " << shortest << " = " << arra[i][k] << endl;
								}
								else{
									arra[indexx][k] = adj[index][k] + shortest;
									//cout << arr[index][k] <<" + " << shortest << " = " << arra[i][k] << endl;
									if (arra[indexx][k] > arra[indexx-1][k]){
										arra[indexx][k] = arra[indexx-1][k];
										//      cout << "same as last row" << endl;
									}
								}
							}
							else if (i != 0){
								arra[indexx][k] = arra[i-1][k];
							//  cout << "same as last row: " << arra[i-1][k] << endl;
							}
						}	
						whereihavebeen.push_back(index);
						shortest = 999;
						int yesno = 0;
						for(int k = 0; k < size; k++){
							yesno = 0;
							for (int gg = 0; gg < whereihavebeen.size(); gg++ ){
								if (k - (whereihavebeen.at(gg)) == 0 ){
									yesno = 1;
								}
							}		  
							if ((arra[indexx][k] > 0 ) && (arra[indexx][k] < shortest) && (yesno == 0)){
								shortest = arra[indexx][k];
								index = k;
								//cout << "new shortest " << shortest << " at " << index << endl;
							}
					else if ((arra[indexx][k] > 0) && (shortest == 999 ) && (yesno == 0)){
						shortest = arra[indexx][k];
						index = k;
						//  cout << "new shortest " << shortest << " at " << index << endl;
					}
				} 
				indexx++;
						}     
					for(int i = 0; i< size; i++){
							cout << endl;
						}
					if (arra[size-1][stop] == -1){
							cout << "No possible path" << endl; 
						}
					else{
							int weight = 9999999;
							cout << Vertices.at(go); 
							for(int l = 0; l < whereihavebeen.size(); l++){
								if (l == 0){
									weight =  arra[l][stop];
								}
								else{
									if (arra[l][stop] != arra[l-1][stop]){
										cout << "->" << Vertices.at(whereihavebeen.at(l));
										weight = arra[l][stop];
									}
								}
							}
							cout << "->" << Vertices.at(stop);
							cout << " Weight: " << weight << endl;
						}
				}
			}
		}
		else if (in == 7){
			running = false;
		}
		else{
			cout << "Invalid input. Please enter in a number 1 through 7" << endl;
		}
    }
}