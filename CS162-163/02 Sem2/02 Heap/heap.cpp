/*
 * Date of Creation: February 15th, 2019
 * Date of Finish: March 11th, 2019
 * The heap is a data structure that follows the following property:
 * Each parent must be greater than or equal to it's child
 * The program takes input either manually or from a space-separated text file and heapify's the array in which it stores the numbers
 * After it has completed the heapify, it will then remove each node from the heap by taking out the root (which is the largest number in the tree)
 * The removal of nodes should print out the sorted list because the heap will be heapified after removing each root (making it so that the root is always the largest in the tree
 * My program does not have an efficient or good way of printing parent-child relationships but the heap array is correct
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdio.h>

using namespace std;

class Heap{
	public:
		Heap(int newSize){
			heap = new int[newSize];
			size = newSize;
			for (int i = 0; i < size; i++){
				heap[i] = -1;
			}
			
		}
		int Size(){
			return size;
		}
		void printArrayForm(int a){
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
		}
		void insert(int a, int index){
			heap[index] = a;
		}
		void swap(int a, int b){
			int temp = heap[a];
			heap[a] = heap[b];
			heap[b] = temp;
		}
		int valueAt(int index){
			return heap[index];
		}
		void printTreeForm(){
			
		}
		void printPyramidForm(){
			int level = 1;
			for(int i = 0; i < size; i++){
				if (i == (pow(2,level)-1)){
					cout << endl;
					level++;
				}
				printf("%7d ", heap[i]);
			}
			cout << endl;
		}
	private:
		int* heap;
		int size;		
};

void parseNumbers(char input[], vector<int> &integers);
void printVector(vector<int> integers);

void heapify(Heap* heap, int n, int i);
void heapSort(Heap* heap, int n);

void removeAll(Heap* heap);

int main(){
	cout << "How would you like to enter your numbers? (Answer with 1 or 2) \n1.Manually through the console\n2.Through a text file\n>>";
	int in;
	cin >> in;
	
	vector<int> integers;
	//Manually
	if (in == 1){
		char input[1000];
		cin.ignore(10000,'\n');
		cout << "Enter in your Numbers Separated by a Space:\n>>";
		cin.get(input,1000);
		cin.clear();
		cin.ignore(10000,'\n');
		//cout << input << endl;
		
		parseNumbers(input,integers);
		//printVector(integers);
		
		Heap* newHeap = new Heap(integers.size());
		//cout << "Heap Class Size is: " << newHeap->Size() << endl;
		//newHeap->printArrayForm();
		for(int i = 0; i < integers.size(); i++){
			newHeap->insert(integers[i],i);
		}
		heapSort(newHeap, newHeap->Size());
			
		newHeap->printArrayForm(newHeap->Size());
		//newHeap->printPyramidForm();
		
		removeAll(newHeap);
	}
	//Through Text File
	else if (in == 2){
		cin.ignore(10000,'\n');
		cout << "Please enter the name of your Text File: \n>>";
		char input[100];
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
			char fileInput[10000];
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
			//cout << fileInput << endl;
			myfile.close();
			
			parseNumbers(fileInput, integers);
			//printVector(integers);
			
			Heap* newHeap = new Heap(integers.size());
			for(int i = 0; i < integers.size(); i++){
				newHeap->insert(integers[i],i);
			}
			//newHeap->printArrayForm();
			//newHeap->printPyramidForm();
			//cout << "The Size of the Heap is: " << newHeap->Size() << endl;
			heapSort(newHeap, newHeap->Size());
			
			newHeap->printArrayForm(newHeap->Size());
			//newHeap->printPyramidForm();
			
			removeAll(newHeap);
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
void printVector(vector<int> integers){
	cout << "Printing Vector:\n";
	for (int i = 0; i < integers.size(); i++){
		cout << i+1 << ". " << integers[i] << endl;
	}
	cout << endl;
}

//This function comes from https://www.geeksforgeeks.org/heap-sort/
//Heap is the array (but enclosed within the class
//n is size of heap
//i is an index in the heap
void heapify(Heap* heap, int n, int i){
	int largest = i;
	int l = 2*i+1;//Left Index
	int r = 2*i+2;//Right Index
	/*cout << "Root Index is: " << largest << " and it's value is: " << heap->valueAt(largest) 
	<< endl << "Left Index is: " << l << " and it's value is: " << heap->valueAt(l) 
	<< endl << "Right Index is: " << r << " and it's value is: " << heap->valueAt(r) << endl;*/
	// If left child is larger than root 
    if (l < n && heap->valueAt(l) > heap->valueAt(largest)) {
    	//cout << "Left Child is larger than root" << endl;
        largest = l; 
  	}
    // If right child is larger than root
    if (r < n && heap->valueAt(r) > heap->valueAt(largest)) {
    	//cout << "Right Child is larger than root" << endl;
        largest = r; 
  	}
    // If largest is not root 
    
    if (largest != i) { 
        heap->swap(i, largest); 
  		//heap->printArrayForm();
        // Recursively heapify the affected sub-tree 
        heapify(heap, n, largest); 
    }
    /*else{
    	heap->printArrayForm();
    } */
}
//This function also comes from https://www.geeksforgeeks.org/heap-sort/
//Heap is the array enclosed within the class
//n is the size of the heap
void heapSort(Heap* heap, int n){
// Build heap (rearrange array) 
    for (int i = (n/2) - 1; i >= 0; i--) {
        heapify(heap, n, i); 
  	}
}

void removeAll(Heap* heap){
	cout << "REMOVAL" << endl;
	for (int i=heap->Size()-1; i>=0; i--) { 
        // Move current root to end
        cout << heap->valueAt(0) << " "; 
        heap->swap(0, i); 
        // call max heapify on the reduced heap 
        heapify(heap, i, 0);
        if (i == 0){
        	//heap->printArrayForm(i);
        	cout << endl;
        }
    } 
}
