#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "project.h"

using namespace std;


bool previousHit = false;
int chanceArray [10][10];


bool computerGuess(Map& userMap, int x, int y){
    bool hitShip = false;
    
    if(previousHit){
        int max_x = 0;
        int max_y = 0;
        int max = 0;
        
        if(!userMap.getItemAt(x,y-1).isHit() && chanceArray[x][y-1] > max){
            max_x = x;
            max_y = y-1;
            max = chanceArray[max_x][max_y];
        }
        
        if(!userMap.getItemAt(x,y+1).isHit() && chanceArray[x][y+1] > max){
            max_x = x;
            max_y = y+1;
            max = chanceArray[max_x][max_y];
        }
        
        if(!userMap.getItemAt(x-1,y).isHit() && chanceArray[x-1][y] > max){
            max_x = x-1;
            max_y = y;
            max = chanceArray[max_x][max_y];
        }
        
        if(!userMap.getItemAt(x+1,y).isHit() && chanceArray[x+1][y] > max){
            max_x = x+1;
            max_y = y;
            max = chanceArray[max_x][max_y];
        }
        
        if(max == 0){
            previousHit = false;
        }
        
        if(previousHit){
            userMap.getItemAt(max_x, max_y).itemHit();
            if(userMap.getItemAt(max_x, max_y).isShip()){
                hitShip = true;
                previousHit = true;
                
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 10; j++){
                        if(i == x){
                            chanceArray[i][j]++;
                        }
                        if(j == y){
                            chanceArray[i][j]++;
                        }
                    }
                }
            }
        }
    }
    
    if(!previousHit){
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
        
        userMap.getItemAt(max_x, max_y).itemHit();
        if(userMap.getItemAt(max_x, max_y).isShip()){
            hitShip = true;
            previousHit = true;
            
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(i == x){
                        chanceArray[i][j]++;
                    }
                    if(j == y){
                        chanceArray[i][j]++;
                    }
                }
            }
        }
    }
    return hitShip;
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
