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

void generateShips(Map& computerMap){
    
    //ADD AIRCRAFT CARRIER
    if(!computerMap.containsItem("A")){
        bool freeSpace = true;
        do{
            int x = rand() % 10;
            int y = rand() % 10;
            

            
            //vertical
            if(rand() % 2){
                if(y > 5){
                    for(int i = 0; i != 5; i++){
                        if(computerMap.getItemAt(x,y-i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            computerMap.getItemAt(x, y - i) = *aircraftCarrier;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 5; i++){
                        if(computerMap.getItemAt(x,y+i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            computerMap.getItemAt(x, y + i) = *aircraftCarrier;
                        }
                    }
                }
            }
            //horizontal
            else{
                if(x > 5){
                    for(int i = 0; i != 5; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            computerMap.getItemAt(x-i, y) = *aircraftCarrier;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 5; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            computerMap.getItemAt(x-i, y) = *aircraftCarrier;
                        }
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD BATTLESHIP
    if(!computerMap.containsItem("S")){
        bool freeSpace = true;
        do{
            int x = rand() % 10;
            int y = rand() % 10;
            
            
            //vertical
            if(rand() % 2){
                if(y > 4){
                    for(int i = 0; i !=4; i++){
                        if(computerMap.getItemAt(x,y-i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(5, "B");
                            computerMap.getItemAt(x, y - i) = *battleship;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 4; i++){
                        if(computerMap.getItemAt(x,y+i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(5, "B");
                            computerMap.getItemAt(x, y + i) = *battleship;
                        }
                    }
                }
            }
            //horizontal
            else{
                if(x > 4){
                    for(int i = 0; i != 4; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(5, "B");
                            computerMap.getItemAt(x-i, y) = *battleship;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 4; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(4, "B");
                            computerMap.getItemAt(x-i, y) = *battleship;
                        }
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD SUBMARINE
    if(!computerMap.containsItem("S")){
        bool freeSpace = true;
        do{
            int x = rand() % 10;
            int y = rand() % 10;
            
            //vertical
            if(rand() % 2){
                if(y > 3){
                    for(int i = 0; i !=3; i++){
                        if(computerMap.getItemAt(x,y-i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(5, "S");
                            computerMap.getItemAt(x, y - i) = *submarine;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x,y+i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(5, "S");
                            computerMap.getItemAt(x, y + i) = *submarine;
                        }
                    }
                }
            }
            //horizontal
            else{
                if(x > 3){
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(5, "S");
                            computerMap.getItemAt(x-i, y) = *submarine;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(3, "S");
                            computerMap.getItemAt(x-i, y) = *submarine;
                        }
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD cruiser
    if(!computerMap.containsItem("C")){
        bool freeSpace = true;
        do{
            int x = rand() % 10;
            int y = rand() % 10;
            
            
            
            //vertical
            if(rand() % 2){
                if(y > 3){
                    for(int i = 0; i !=3; i++){
                        if(computerMap.getItemAt(x,y-i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(5, "C");
                            computerMap.getItemAt(x, y - i) = *cruiser;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x,y+i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(5, "C");
                            computerMap.getItemAt(x, y + i) = *cruiser;
                        }
                    }
                }
            }
            //horizontal
            else{
                if(x > 3){
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(5, "C");
                            computerMap.getItemAt(x-i, y) = *cruiser;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 3; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(3, "C");
                            computerMap.getItemAt(x-i, y) = *cruiser;
                        }
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD destroyer
    if(!computerMap.containsItem("D")){
        bool freeSpace = true;
        do{
            int x = rand() % 10;
            int y = rand() % 10;
            
            
            
            //vertical
            if(rand() % 2){
                if(y > 2){
                    for(int i = 0; i !=2; i++){
                        if(computerMap.getItemAt(x,y-i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(5, "D");
                            computerMap.getItemAt(x, y - i) = *destroyer;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 2; i++){
                        if(computerMap.getItemAt(x,y+i).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(5, "D");
                            computerMap.getItemAt(x, y + i) = *destroyer;
                        }
                    }
                }
            }
            //horizontal
            else{
                if(x > 2){
                    for(int i = 0; i != 2; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(5, "D");
                            computerMap.getItemAt(x-i, y) = *destroyer;
                        }
                    }
                }
                else{
                    for(int i = 0; i != 2; i++){
                        if(computerMap.getItemAt(x-i,y).getName() != "W"){
                            freeSpace = false;
                        }
                    }
                    if(freeSpace){
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(2, "D");
                            computerMap.getItemAt(x-i, y) = *destroyer;
                        }
                    }
                }
            }
        } while(!freeSpace);
    }
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

    Map* userMap = new Map();
    Map* computerMap = new Map();
    generateShips(*computerMap);
    computerGuess(*userMap, 0, 0);
    //put stuff here!
    
    
	//write to file at end of program
    ofstream out("likelihood.txt");
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            out << chanceArray[i][j] << " ";
        }
        out << endl;
    }
	
    return 0; 
}
