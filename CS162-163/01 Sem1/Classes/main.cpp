/*Classes in one File
 *In each respective cpp and header file you write:
 *CPP: The body of each function
 *HEADER: The public (the function prototypes) and the private 
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

void addMedia (vector<Media*>* DataBase);

class Media{
private:
  	int year;
  	char title[20];
public:
	Media();
	~Media();//Destructor
	int* getYear(){
    return &year;
  }
	char* getTitle(){
    return &title;
  }
	virtual int getType(){
    return 0;
  }
};

class VideoGames : public Media{
private:
	char publisher[20];
	float rating;
  	//int year; (From Media)
  	//int title; (From Media)
public:
	VideoGames
	~VideoGames();
  	char* getPublisher(){
    	return &publisher;
	}
  	float* getRating(){
    	return rating;
  	}
  	virtual int getType(){
  		return 1;
  	}
};

class Music : public Media{
private:
	char artist[20];
  	int duration;//Number of Seconds
  	char publisher[20];
public:
	~Music();
  	char getArtist(){
    	return artist;
  	}
  	int getDuration(){
    	return duration;
  	}
  	char getPublisher(){
    	return publisher;
  	}
};

class Movies : public Media{
private:
  int duration;//Time in minutes
  char director;
  float rating;//Out of 10
public:
  ~Movies();
  void setDuration(int newDuration){
    duration = newDuration;
  }
  void setDirector(char newDirector){
    director = newDirector;
  }
  void setRating(float newRating){
    rating = newRating;
  }
  int getDuration(){
    return duration;
  }
  char getDirector(){
    return director;
  }
  float getRating(){
    return rating;
  }
};
  
int main(){
  vector<Media*>* DataBase = new vector<Media*>;
  bool stillPlaying = true;
  while(stillPlaying){
    char input[10];
    cout << "Please enter one of the following options:" << endl << "ADD" << endl << "DELETE" << endl << "SEARCH" << endl << "QUIT" << endl;
    cin >> input;
    if (strcmp(input,"ADD") == 0){
      printf("ADDED\n");
    }
    else if (strcmp(input,"DELETE") == 0){
      printf("DELETED\n");
    }
    else if (strcmp(input,"SEARCH") == 0){
      printf("PRINTED\n");
    }
    //End Game if QUIT is inputted
    else if (strcmp(input,"QUIT") == 0){
      stillPlaying = false;
      printf("Program has ended\n");
    }  
  }//stillPlaying while loop
} //End of int(main)

void addMedia (vector<Media*>* DataBase){
  cout << "What type of Media do you want to add to the Database?" << endl << "Add one of the following: ['MUSIC','VIDEOGAME','MOVIE']" << endl;
  char type[10];
  if (strcmp(type,"MUSIC") == 0){
    Music* addMusic;
    cout << "A Music Media has information: [Title,Year,Artist,Duration,Publisher]" << endl;
    cout << "Enter your Title: " << endl;
    DataBase->push_back(addMusic);
  }
  else if (strcmp(type,"VIDEOGAME") == 0){
    VideoGame addVideoGame;
  }
  else if (strcmp(type,"MOVIE") == 0){
    Movie addMovie;
  }
}
