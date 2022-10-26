#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

class Room{
public:
  void addBoss(Boss* newBoss){
    Bosses.push_back(newBoss);
  }
  void printBossesinRoom(){
    vector<Boss*>::iterator itr;
    for(itr = Bosses.begin(); itr != Bosses.end(); ++itr){
      cout << (*itr)->getName();
    }
    cout << endl;
  }
  Boss* takeItem(char* BossName){
    vector<Boss*>::iterator itr;
    for(itr = Bosses.begin(); itr != Bosses.end(); ++itr){
      if(strcmp((*itr)->getName(),BossName) == 0){
	Boss* Ew  = *itr;
	Bosses
	return itr;
      }
    }
  }
  void setExit(char newDirection, int newRoomNumber){
    Exits.insert(pair<char,int> (newDirection,newRoomNumber));
  }
  void printDescription(){
    cout << "You are in Room " << RoomNum << ".\nThere are exits:" << endl;
    map<char,int>::iterator itr;
    //https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
    for (itr = Exits.begin(); itr != Exits.end(); ++itr) { 
      cout << itr -> first << endl; 
    } 
  }
  
private:
  vector<Boss*> Bosses = new vector<Boss*>();
  map<char,int> Exits;
  int RoomNum;
  //Directions for Map are: N,E,S,W
  //Int is the Room Number
};

//This Class Replicates the Program's "Item's"
class Boss{
public:
  Boss(char* newName){
    strcpy(Name,newName);
  }
  char* getName(){
    return Name;
  }
  ~Boss();
private:
  //A Boss will have a Name
  char* Name;
};

int main(){
  vector<Room*> Rooms = new vector<Room*>();
  //Insert All Rooms/Bosses/Exits Here
  //Create Room
   vector<Boss*> SatchelofTrophies = new vector<Boss*>;
   Boss* Pit = new Boss("Pit");
   Boss* Lucario = new Boss("Lucario");
   Boss* IceClimbers = new Boss("Ice Climbers");
   Boss* Ike = new Boss("Ike");
   Boss* PokemonTrainer = new Boss("Pokemon Trainer");
   Boss* Zelda = new Boss("Zelda");
   Boss* Peach = new Boss("Peach");
   Boss* Wario = new Boss("Wario");
   Boss* Kirby = new Boss("Kirby");
   Boss* Link = new Boss("Link");
   Boss* Yoshi = new Boss("Yoshi");
   Boss* Marth = new Boss("Marth");
   Boss* Ganondorf = new Boss("Ganondorf");
   Boss* Mario = new Boss("Mario");
   Boss* Bowser = new Boss("Bowser");
   Boss* Falco = new Boss("Falco");
   Boss* KingDedede = new Boss("King Dedede");
   Boss* Fox = new Boss("Fox");
   Boss* Olimar = new Boss("Olimar");
   Boss* Pikachu = new Boss("Pikachu");
   Boss* Samus = new Boss("Samus");
   Boss* DonkeyKong = new Boss("Donkey Kong");
   Boss* DiddyKong = new Boss("Diddy Kong");
   Boss* Ness = new Boss("Ness");
   Boss* MetaKnight = new Boss("Meta Knight");
   Boss* Snake = new Boss("Snake");
   Boss* CaptainFalcon = new Boss("Captain Falcon");
   Boss* GameandWatch = new Boss("Game and Watch");
   Boss* ROB = new Boss("ROB");
  //Add Bosses, Add Exits

  //The Player has a current Room and has a Satchel of Trophies
  Room* currentRoom = new Room();
 
  /* You are in currently in Room 1.
   * There are exits:
   * NORTH EAST SOUTH WEST
   * There is a Boss to fight here:
   * Boss: Pit
   */
}
