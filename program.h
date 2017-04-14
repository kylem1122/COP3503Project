#ifndef PROGRAM_H
#define PROGRAM_H

//create classes
#include <iostream>
using namespace std; 

class Item {
protected:
	bool hit = false;
	int size = 0;
	string name;
public:
	Item();
	Item(bool hit, int size, string name);
	bool isHit(bool hit) {
	
	}
	string getName() {
		return name;
	}
	int getSize() {
		return size;
	}
	void setName(string newName) {
		name = newName;
	}
	void setSize(int newSize) {
		size = newSize;
	}
};

class Map{
	Item board[10][10];
	string type;
public:
	Map();
	void setType(string newtype) {
		type = newtype;
	}
	string getType() {
		return type;
	}
	void setShip(int xIndex, int yIndex, Item ship) {
		board[xIndex][yIndex] = ship;
	}

	void setWater() {
		for (int i = 0; i != 10; ++i) {
			for (int j = 0; j != 10; ++j) {
				board[j][i] = Item(false, 0, "W");
			}
		}
	}
	void print() {
		Item temp;
		string tempName;
		for (int i = 0; i != 10; ++i) {
			for (int j = 0; j != 10; ++j) {
				temp = board[j][i];
				tempName = temp.getName();
				cout << tempName << endl;
			}
		}

	}


};

//menu method
int menu(){
    cout<< "Welcome to War Boats"<< endl;
    int selection = 0;
    while(selection > 4 || selection < 0){
    cout<< "Please select an option"<< endl;
    cout<< "1. Start Game "<< endl;
    cout<< "2. Place Pieces" << endl;
    cout<< "3. Modify Pieces "<< endl;
    cout<< "4. Exit "<< endl;
    cin>> selection;
    }
    return selection;
}

//guess checking method
bool guess_check(int x, int y, int board[][]){
    boo isHit = false;
    if(board[x][y] == w){
        cout<< "Miss" << endl;
        return isHit;
    }
    else if(board[x][y] == s){
        cout<< "Hit"<< endl;
        isHit = true;
        return isHit;
    }
    else{
        cout<< "Invalid guess"<< endl;
        return isHit;
    }
}

#endif
