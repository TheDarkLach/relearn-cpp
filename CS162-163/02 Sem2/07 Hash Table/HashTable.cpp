/*
Hash Table

Create a hash table and a random student generator                                        

Why are we doing this?  Hash Tables are efficient ways to access data.  If you have a good hash function, it can be efficient to store information in one of these.

Implementation:  Start from your student list program, meaning you need ADD, PRINT, DELETE, and QUIT. Change the way the students are stored; use a hash table. 
You should create a hash function using the student data which attempts to spread out data evenly through the table. It can be something you make up, or you may use a pre-existing hash formula. 
The hash table should start with at least 100 slots (of an array, not a vector).  It should be able to deal with collisions in a valid way. 
I recommend chaining, which means each entry is actually a linked list. (10 points) 
If you get more than 3 collisions when you are chaining (or the table is more than half full using other techniques), create a table to have double the number of slots, then rehash your students into the new table.  
(Your hash should alter based on the size of the table, by the way, and it should spread out the data as you resize the table.  Make it so.)  (10 points)

In addition to the hash table, create a random student generator.  You should have a file with a list of first names and a file with a list of last names.  Your student list program should be able to randomly generate new students by grabbing a random student first and last name from the corresponding files, incrementing the id number, adding a random GPA (much like real life), and adding it in.
Make sure you have a command that allows you to specify how many students to generate and add.  This will make debugging your project MUCH easier.  (10 points)

Comment. (5 points)

Total Points: 35
*/

/*
 * Author: Zareef Amyeen
 * Date: September 24th, 2018
 * Student List Project is an example of use of vectors and pointers
 * This project lets you use user input and from that user input you get to choose whether or not you want to add, print, delete or quit
 * The add prompt will add a student into the vector and will ask you for first name, last name, id, and gpa
 * The print prompt will print the students informations
 * The delete prompt will delete a student dependent on ID because no two students have the same ID
 * The quit prompt will exit you out of the game
 * Let's Learn C++ ~ Basics: 5 of 14 ~ References & Pointers: https://www.youtube.com/watch?v=DvUYbUn9uQ4 
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;

//Extra information about Structs came from: https://www.youtube.com/watch?v=DBQzxCHk9uI
//Intro to C++: Structs
struct Student {
  char firstname[10];
  char lastname[10];
  int id;
  float gpa;
};

class Node{
	public:
		Node(){
			next = NULL;
			chained = NULL;
			Empty = true;
			chainNumber = 0;
		}
		//Destructor is not needed
		Node* getNext(){
			return next;
		}
		Node* getChained(){
			return chained;
		}
		Student* getStudent(){
			return data;
		}
		bool isEmpty(){
			return Empty;
		}
		bool isNotEmpty(){
			return !Empty;
		}
		int getChainNumber(){
			return chainNumber;
		}
		void setStudent(Student* person){
			data = person;
		}
		void setNext(Node* newNext){
			next = newNext;
		}
		void setChained(Node* newChained){
			chained = newChained;
		}
		void setEmpty(){
			Empty = true;
		}
		void setNotEmpty(){
			Empty = false;
		}
		void setChainNumber(int newChainNumber){
			chainNumber = newChainNumber;
		}
		void remove(){
			Empty = true;
			Student* temp = data;
			delete temp;
			data = NULL;
		}
	private:
		Student* data;
		Node* next;
		Node* chained;
		int chainNumber;
		bool Empty;//Because the hash table functions as an absolute array the holes and non wholes are distinguished via empty and non empty
};

void printStudent (Student* person);
void printArray (char array[10]){
	for (int i = 0; i < strlen(array);i++){
		printf("%c",array[i]);
	}
}

void parseSpaceInput(char input[10000],vector<char*> &parsedInput);
//Super simple, just the mod of id and size
int getTableSize(Node* HashTable);
int numberofStudents(Node* HashTable);
Node* getIthNode(Node* HashTable, int i);
void deleteHashTable(Node* HashTable);
void createHashTable(Node* HashTable, int tableSize);
int hashf(int id,int size);
void doubleHashSize(Node* HashTable, int tableSize);
void reHash(Node* HashTable);

Student* createStudent();
Student* createRandomStudent(char FNFileName[100],char LNFileName[100]);
void addStudent(Node* HashTable, Student* person);

void deleteStudent(Node* HashTable);

void printHashTable(Node* HashTable);
int main (){
  bool stillPlaying = true;
  Node* HashTable = new Node();
  int tableSize = 100;
  createHashTable(HashTable, tableSize);
  while(stillPlaying){
    char input[100];
    printf("Please enter one of the following options:\n1.Add\n2.Delete\n3.Print\n4.Quit\n>>");
    cin >> input;
    //These if Statements run the Game
    if (strcmp(input,"Add") == 0 || strcmp(input,"1") == 0){
    	int input_1;
    	cout << "How would you like to add your students?\n1.Manually\n2.Via text file\n>>";
    	cin >> input_1;
    	if (input_1 == 1){
    		addStudent(HashTable, createStudent());
    	}
    	else if(input_1 == 2){
    		cout << "How many students would you like to randomly generate?\n>>";
    		int input_2;
    		cin >> input_2;
    		char FNFileName[100],LNFileName[100];
    		cout << "Two important notices:\n1.The text file must be space delimited and\n2.must have no return line at the end of the single line of names" << endl;
			cout << "Enter the name of the text file that contains the first names.\n>>";
    		cin >> FNFileName;
    		cout << "Enter the name of the text file that contains the last names.\n>>";
    		cin >> LNFileName;
    		for (int i = 0; i < input_2; i++){
    			std::this_thread::sleep_for( std::chrono::milliseconds(1259) ) ;
				addStudent(HashTable, createRandomStudent(FNFileName,LNFileName));    	    		
    		}
		}
    }
    else if (strcmp(input,"Delete") == 0 || strcmp(input,"2") == 0){
      deleteStudent(HashTable);
    }
    else if (strcmp(input,"Print") == 0 || strcmp(input,"3") == 0){
		cout << "Number of Student's in HashTable is: " << numberofStudents(HashTable) << " and it's size is: " <<
		getTableSize(HashTable) << endl;    	
		printHashTable(HashTable);
    }
    //End Game if QUIT is inputted
    else if (strcmp(input,"Quit") == 0 || strcmp(input,"4") == 0){
      stillPlaying = false;
      printf("Program has ended\n");
    }
  }
  return 0;
}
Node* getEndofChain(Node* randomNode){
	if (randomNode->isNotEmpty()){
		Node* next = randomNode;
		while (next->getChained() != NULL){
			next = next->getChained();
		}
		return next;
	}
	else{
		return randomNode;
	}
}
int numberinChain(Node* randomNode){
	int counter = 0;
	if (randomNode->isNotEmpty()){
		Node* next = randomNode;
		while(next->getChained() != NULL){
			next = next->getChained();
			counter++;
		}
		return counter;
	}
	else{
		return counter;
	}
}
int numberofStudents(Node* HashTable){
	int sCounter = 0;
	for (int i = 0; i < getTableSize(HashTable); i++){
		if (getIthNode(HashTable,i)->isNotEmpty()){
			sCounter++;
		}
	}
	return sCounter;
}
int getTableSize(Node* HashTable){
	Node* newNext = HashTable;
	int counter = 0;
	while (newNext->getNext() != NULL){
		newNext = newNext->getNext();
		counter++;
	}
	return counter;
}
//Makes it easy to go back a node
Node* getIthNode(Node* HashTable, int i){
	Node* nextNode = HashTable;
	for (int j = 0; j < i+1; j++){
		nextNode = nextNode->getNext();
	}
	return nextNode;
}
void createHashTable(Node* HashTable, int tableSize){
	Node* prevNode = HashTable;
	for (int i = 0; i < tableSize; i++){
		Node* newNode = new Node();
		prevNode->setNext(newNode);
		prevNode = prevNode->getNext();
	}	
}
void doubleHashSize(Node* HashTable, int tableSize){
	Node* next = HashTable;
	while (next->getNext() != NULL){
		next = next->getNext();
	}
	for (int i = 0; i < tableSize; i++){
		Node* newNode = new Node();
		next->setNext(newNode);
		next = next->getNext();
	}
}
void reHash(Node* HashTable){
	vector<Student*> Students;
	for (int i = 0; i < getTableSize(HashTable); i++){
		if (getIthNode(HashTable,i)->isNotEmpty()){
			//Check for chains
			Node* chain = getIthNode(HashTable,i);
			while (chain->getChained() != NULL){
				Node* temp = chain->getChained();
				//cout << "Student with ID: " << temp->getStudent()->id << " is being pushed into Student vector" << endl;
				//cout << "Name: " << temp->getStudent()->firstname << endl;
				Student* newStudent = new Student;
				newStudent->id = temp->getStudent()->id;
				newStudent->gpa = temp->getStudent()->gpa;
				strcpy(newStudent->firstname,temp->getStudent()->firstname);
				strcpy(newStudent->lastname,temp->getStudent()->lastname);
				Students.push_back(newStudent);
				chain->setChained(temp->getChained());
				delete temp;
			}
			//cout << "Pushing the Start Chain" << endl;
			Student* newStudent = new Student;
			newStudent->id = chain->getStudent()->id;
			newStudent->gpa = chain->getStudent()->gpa;
			strcpy(newStudent->firstname,chain->getStudent()->firstname);
			strcpy(newStudent->lastname,chain->getStudent()->lastname);
			Students.push_back(newStudent);
			chain->setStudent(NULL);
			chain->setEmpty();
			chain->setChainNumber(0);
		} 
	}
	//printHashTable(HashTable);
	if(Students.size() > getTableSize(HashTable)){
		//cout << "Doubling" << endl;
		doubleHashSize(HashTable,getTableSize(HashTable));
	}
	else{
		//cout << "Not doubling" << endl;
		doubleHashSize(HashTable,getTableSize(HashTable)/2+1);
	}
	for (vector<Student*>::iterator Sptr = Students.begin(); Sptr != Students.end(); ++Sptr){
		addStudent(HashTable,*Sptr);
	}
}
int hashf(int id, int size){
	return id%size;
}
//From Example
void printStudent(Student* person){
  printf("Student's First Name:");
  printArray(person->firstname);
  printf("\nStudent's Last Name:");
  printArray(person->lastname);
  printf("\nStudent's ID:%d\nStudent's GPA:%.2f\n",person->id,person->gpa);
}

//Manual Entry
Student* createStudent(){
	//cout << "Manual Create Student Call" << endl;
	Student* Sptr = new Student;
	printf("Enter Student's First Name:\n");
	cin >> Sptr->firstname;
	printf("Enter Student's Last Name:\n");
	cin >> Sptr->lastname;
	printf("Enter Student's ID:\n");
	cin >> Sptr->id;
	printf("Enter Student's GPA:\n");
	cin >> Sptr->gpa;
	//StudentClass.push_back(Sptr);
	return Sptr;
}

//Generates via random
Student* createRandomStudent(char FNFileName[100],char LNFileName[100]){
	Student* Sptr = new Student;
	srand (time(0));
	vector<char*> FirstNames;
	vector<char*> LastNames;
	ifstream FNFile;
	//cout << FNFileName << endl;
	FNFile.open(FNFileName);
		
	if (!FNFile){
		cout << "There is an error opening the file.\n";
		return 0;
	}
	else{
		char fileInput[10000];
		int i = 0;
		//https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
		while (!FNFile.eof()){
			fileInput[i] = FNFile.get();
			if (fileInput[i] == ' '){
				fileInput[i+1] = '\0';
			}
			i++;
		}
		fileInput[i-1] = '\0';
		FNFile.close();
		parseSpaceInput(fileInput,FirstNames);
		int random = rand()%FirstNames.size();
		strcpy(Sptr->firstname,FirstNames[random]);
		cout << Sptr->firstname << endl;
	}
	//cout << "Enter the  name of the text file that contains the last names." << endl;
	//char LNFileName[100];
	//cin >> LNFileName;
	ifstream LNFile;
	//cout << LNFileName << endl;
	LNFile.open(LNFileName);
	
	if (!LNFile){
		cout << "There is an error opening the file.\n";
		return 0;
	}
	else{
		char fileInput[10000];
		int i = 0;
		//https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
		while (!LNFile.eof()){
			fileInput[i] = LNFile.get();
			if (fileInput[i] == ' '){
				fileInput[i+1] = '\0';
			}
			i++;
		}
		fileInput[i-1] = '\0';
		LNFile.close();
		parseSpaceInput(fileInput,LastNames);
		int random = rand()%LastNames.size();
		strcpy(Sptr->lastname,LastNames[random]);
		cout << Sptr->lastname << endl;
	}
	Sptr->id = rand()%10 * pow(10,5) + rand()%10 * pow(10,4) + rand()%10 * pow(10,3) + rand()%10 * pow(10,2) + rand()%10 * pow(10,1) + rand()%10;
	
	Sptr->gpa = rand()%5 + rand()%10 * pow(10,-1) + rand()%10 * pow(10,-2);
	
	return Sptr;
}

void parseSpaceInput(char input[10000],vector<char*> &parsedInput){
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

void addStudent(Node* HashTable, Student* person){
	if (person == NULL){
		return;
	}
	int index = hashf(person->id,getTableSize(HashTable));
	//Chaining
	if (getIthNode(HashTable,index)->isNotEmpty()){
		//cout << "Student: " << person->firstname << " chaining." << endl;
		Node* insert = new Node();
		insert->setStudent(person);
		insert->setNotEmpty();
		getIthNode(HashTable,index)->setChainNumber(getIthNode(HashTable,index)->getChainNumber()+1);
		getEndofChain(getIthNode(HashTable,index))->setChained(insert);
	}
	//cout << "Inserting student at: " << index << " and the size of the table is: " << getTableSize(HashTable) << endl;
	//NonChain
	else{
		//cout << "Student: " << person->firstname << " NOT chaining." << endl;
		Node* insert = getIthNode(HashTable,index);
		insert->setChainNumber(1);
		insert->setStudent(person);
		insert->setNotEmpty();
	}
	if (2*numberofStudents(HashTable) > getTableSize(HashTable)){
		cout << "The Hash Table is more than half full and so will be reHashing" << endl;
		reHash(HashTable);
		return;
	}
	for(int i = 0; i < getTableSize(HashTable); i++){
		if (getIthNode(HashTable,i)->getChainNumber() > 3){
			cout << "There is more than 3 in a chain and so will be reHashing" << endl;
			reHash(HashTable);
			return;
		}
	}
}

void deleteStudent(Node* HashTable){
	cout << "What is the ID of the student that you want to remove?\n>>";
	int in;
	cin >> in;
	int index = hashf(in,getTableSize(HashTable));
	Node* chain = getIthNode(HashTable, index);
	if (chain->getStudent()->id == in){
		//Has a chain
		if (chain->getChained() != NULL){
			getIthNode(HashTable,index-1)->setNext(chain->getChained());
			chain->getChained()->setNext(chain->getNext());
			delete chain;
		}
		//Doesn't have a chain
		else{
			Node* substitute = new Node;
			getIthNode(HashTable,index-1)->setNext(substitute);
			substitute->setNext(chain->getNext());
			delete chain;
		}
	}
	else{
		Node* find = chain;
		while (find->getChained()->getStudent()->id != in){
			find = find->getChained();
		}
		if (find->getChained()->getChained() == NULL){
			Node* temp = find->getChained();
			delete temp;
			find->setChained(NULL);
		}
		else{
			Node* temp = find->getChained();
			find->setChained(temp->getChained());
			delete temp;
		}
	}
}

void printHashTable(Node* HashTable){
	int tableSize = getTableSize(HashTable);
	Node* next = HashTable;
	for (int i = 0; i < tableSize; i++){
		if (next->isNotEmpty()){
			cout << "Index: " << i << endl;
			printStudent(next->getStudent());
			cout << endl;
			Node* chain = next;
			while (chain->getChained() != NULL){
				printStudent(chain->getChained()->getStudent());
				cout << endl;
				chain = chain->getChained();
			}
		}
		next = next->getNext();
	}
}