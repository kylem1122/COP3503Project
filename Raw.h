#ifndef PROJECT_H
#define PROJECT_H

//create classes
#include <iostream>
using namespace std;

//placeable item object
class Item {
//variables for ship & hit identifying / name & size of item
protected:
    bool hit = false;
    bool shipOrNoShip = true;
    int size = 0;
    string name;
public:
    Item(); 	//default constructor
    Item(int size, string name, bool hit){ 		//constructor to set size, name, hit
        this->size = size;
        this->name = name;
        this->hit = hit;
        if(name == "~"){
            shipOrNoShip = false; 	//if water, set to not being ship
        }
    };
    
    bool isHit() { 		//checks if spot has been shot before - getter method
        return this->hit;
    }
    
    void itemHit(){		//decides if place where shot is a ship to change names to show hit or miss
        this->hit = true;
        if(this->isShip()){
            this->name = "X";
        }
        else{
            this->name = "O";
        }
    }
    
    string getName() {		//return name - getter method
        return name;
    }
    
    int getSize() {		//return size - getter method
        return size;
    }
    
    void setName(string newName) {		//change name of item - setter method
        name = newName;
    }
    
    void setSize(int newSize) {		//change size of items - setter method
        size = newSize;
    }
    
    bool isShip(){		//checks to see if item is a placed ship - getter method
        return shipOrNoShip;
    }
};

//gameboard that game uses to place items on
class Map{
private:
    Item* board[10][10];	//standard battleship board and name of board
    string type;
public:
    Map(){		//default constructor - board full of empty "water" spaces
        setWater();
    };
    
    void setShip(int xIndex, int yIndex, Item& ship) {		//places a ship object on a specific index of the board - overrides water on spot to ship
        board[xIndex][yIndex] = &ship;
    }
    
    void setWater() {		//sets place on board to empty water item repeated to go fully through board
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                Item* water = new Item(0, "~", false);
                board[j][i] = water;
            }
        }
    }
    
    Item getItemAt(int x, int y){		//getter method - returns specific item from input index
        return *board[x][y];
    }
    
    void setItemAt(int x, int y, Item newItem){		//setter method - change item at index to specified item
        *board[x][y] = newItem;
    }
    
    bool containsItem(string name){		//iterates through entire array to check if a name is present at any index in array
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                if(board[i][j]->getName() == name){
                    return true;
                }
            }
        }
        return false;
    }
    
    void print() {		//prints maps other than the player's ship map
        for (int i = 0; i != 10; ++i) {
            if(i == 0){
                cout <<"\t\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ" << endl;
                cout <<"\t---------------------------------------------------------------------------------" << endl;
            }
            cout << i + 1 << "\t|\t";
            for (int j = 0; j != 10; ++j) {
                cout << board[i][j]->getName() << "\t";
            }
            cout << endl;
        }
    }
    
    void printGameMap() {		//prints out map of player's ships w/ names
        for (int i = 0; i != 10; ++i) {
            if(i == 0){
                cout <<"\t\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ" << endl;
                cout <<"\t---------------------------------------------------------------------------------" << endl;
            }
            cout << i + 1 << "\t|\t";
            for (int j = 0; j != 10; ++j) {
                if(board[i][j]->isShip() && !board[i][j]->isHit()){
                    cout << "~" << "\t";
                }
                else{
                    cout << board[i][j]->getName() << "\t";
                }
            }
            cout << endl;
        }
    }
};

#endif
