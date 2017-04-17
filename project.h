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
    Item();             //default constructor
    Item(int size, string name, bool hit){          //constructor to set size, name, hit
        this->size = size;
        this->name = name;
        this->hit = hit;
        if(name == "~"){
            //if water, set the variable as not being a ship
            shipOrNoShip = false;
        }
    };
    
    //checks if spot has been shot before -- getter method
    bool isHit() {
        return this->hit;
    }
    
    
    //returns item name -- getter method
    string getName() {
        return name;
    }
    
    //returns item size -- getter method
    int getSize() {
        return size;
    }
    
    //changes the name of item -- setter method
    void setName(string newName) {
        name = newName;
    }
    
    //changes the size of the item -- setter method
    void setSize(int newSize) {
        size = newSize;
    }
    
    //checks to see if the item is a placed ship -- getter method
    bool isShip(){
        return shipOrNoShip;
    }
};


//gameboard that game uses to place items on
class Map{
    //standard battleship board
    Item* board[10][10];
public:
    //default constructor
    Map(){
        //automatically fills the baord with water
        setWater();
    };
    
    //sets the ship with an item at a specific index
    void setShip(int xIndex, int yIndex, Item& ship) {
        delete board[xIndex][yIndex];
        board[xIndex][yIndex] = &ship;
    }
    
    //sets the entire board with water
    void setWater() {
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                Item* water = new Item(0, "~", false);
                board[j][i] = water;
            }
        }
    }
    
    //returns the item at a specific index on the board
    Item getItemAt(int x, int y){
        return *board[x][y];
    }
    
    //allows the user to set an item at an index
    void setItemAt(int x, int y, Item newItem){
        *board[x][y] = newItem;
    }
    
    //checks if the board contains an item, returns true if it does
    bool containsItem(string name){
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                if(board[i][j]->getName() == name){
                    return true;
                }
            }
        }
        return false;
    }
    
    //prints out the board
    void print() {
        
        const char separator    = ' ';
        for (int i = 0; i != 10; ++i) {
            if(i == 0){
                cout << right << setw(12) << setfill(separator) << "A";
                cout << right << setw(4) << setfill(separator) << "B";
                cout << right << setw(4) << setfill(separator) << "C";
                cout << right << setw(4) << setfill(separator) << "D";
                cout << right << setw(4) << setfill(separator) << "E";
                cout << right << setw(4) << setfill(separator) << "F";
                cout << right << setw(4) << setfill(separator) << "G";
                cout << right << setw(4) << setfill(separator) << "H";
                cout << right << setw(4) << setfill(separator) << "I";
                cout << right << setw(4) << setfill(separator) << "J" << endl;
                cout << right << setw(8) << setfill(separator) << "---------------------------------------------------" << endl;
            }
            cout << right << setw(4) << setfill(separator) << i+1;
            cout << right << setw(4) << setfill(separator) << "|";
            for (int j = 0; j != 10; ++j) {
                cout << right << setw(4) << setfill(separator) << board[i][j]->getName();
            }
            cout << endl;
        }
    }
    
    //prints out the board with the ships hidden so the user doesn't know where they are located
    void printGameMap() {
        const char separator    = ' ';
        for (int i = 0; i != 10; ++i) {
            if(i == 0){
                cout << right << setw(12) << setfill(separator) << "A";
                cout << right << setw(4) << setfill(separator) << "B";
                cout << right << setw(4) << setfill(separator) << "C";
                cout << right << setw(4) << setfill(separator) << "D";
                cout << right << setw(4) << setfill(separator) << "E";
                cout << right << setw(4) << setfill(separator) << "F";
                cout << right << setw(4) << setfill(separator) << "G";
                cout << right << setw(4) << setfill(separator) << "H";
                cout << right << setw(4) << setfill(separator) << "I";
                cout << right << setw(4) << setfill(separator) << "J" << endl;
                cout << right << setw(8) << setfill(separator) << "---------------------------------------------------" << endl;
            }
            cout << right << setw(4) << setfill(separator) << i+1;
            cout << right << setw(4) << setfill(separator) << "|";
            for (int j = 0; j != 10; ++j) {
                if(board[i][j]->isShip() && !board[i][j]->isHit()){
                    cout << right << setw(4) << setfill(separator) << "~";
                }
                else{
                    cout << right << setw(4) << setfill(separator) << board[i][j]->getName();
                }
            }
            cout << endl;
        }
    }
};

#endif
