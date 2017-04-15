#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "project.h"

using namespace std;

bool previousHit = false;
bool previousPreviousHit = false;
int chanceArray [10][10];


bool computerGuess(map& userMap) {
    bool hitShip = false;
    int max_x = 0;
    int max_y = 0;
    int max = 0;
    
    
    //find first open index
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(!userMap.getItemAt(i,j).isHit()){
                max_x = i;
                max_y = j;
                max = chanceArray[i][j];
                break;
            }
        }
    }
    
    
    //find max index
    for(int i = max_x; i < 10; i++){
        for(int j = 0; j <10; j++){
            if(chanceArray[i][j] > max){
                if(rand()%2 && !userMap.getItemAt(i,j).isHit()){
                    max_x = i;
                    max_y = j;
                    max = chanceArray[i][i];
                }
            }
            else if(chanceArray[i][j] == max && !userMap.getItemAt(i,j).isHit()){
                if(rand()%2){
                    if(rand()%2){
                        if(rand()%2){
                            max_x = i;
                            max_y = j;
                            max = chanceArray[i][i];
                        }
                    }
                }
            }
        }
    }
    
    if(previousHit){
        //do something
    }
    else{
        userMap.getItemAt(max_x, max_y).itemHit();
        if(userMap.getItemAt(max_x, max_y).isShip()){
            hitShip = true;
        }
    }
    
    return hitShip;
}

bool nextGuess(int x, int y){
    return true;
}


int main(int argc, char ** argv){
  	string fileLoad;
  	transform(fileLoad.begin(), fileLoad.end(), fileLoad.begin(), ::tolower);

	if (argc >= 2) {
	    fileLoad = argv[1];
	}
	else {
		cout << "Invalid choice. Try again." << endl;
		return 1;
	}
	if(fileLoad != "erase" || fileLoad != "load"){
		cout << "Invalid choice. Try again." << endl;
		return 1;
	}
	
	int chanceArray [10][10];
    //load file into array
	if(fileLoad == "load"){
        ifstream in;
        string file = "likelihood.txt";
        
        in.open(file.c_str());
        
        if (!in.is_open()) {
            cerr << "Missing file" << endl;
            return 1;
        }
        
        int num;
        int chanceArray [10][10];
        int a = 0;
        int b = 0;
        
        while (in >> num){
            chanceArray[a][b] = num;
            b++;
            if(b == 10){
                a++;
                b = 0;
            }
            if(a == 10){
                break;
            }
        }
        
        for(int i = 0; i <10; i++){
            for(int j = 0; j < 10; j++){
                cout<< chanceArray[i][j] << " ";
            }
            cout << endl;
        }
        
        in.close();
	}
	else{
		for(int i = 0; i <10; i++){
			for(int j = 0; j < 10; j++){
				chanceArray[i][j] = 1;
			}
		}
	}

	map* userMap = new map();
    computerGuess(*userMap);
    //put stuff here!
    
    
    return 0; 
}
