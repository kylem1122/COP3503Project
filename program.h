#ifndef PROGRAM_H
#define PROGRAM_H

//create classes
#include <iostream>
using namespace std; 

class Item {
protected:
    bool hit = false;
    bool shipOrNoShip = true;
    int size = 0;
    string name;
public:
    Item();
    Item(int size, string name){
        this->size = size;
        this->name = name;
        if(name == "W"){
            shipOrNoShip = false;
        }
    };
    
    bool isHit() {
        return this->hit;
    }
    
    void itemHit(){
        this->hit = true;
        this->name = "X";
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
    
    bool isShip(){
        return shipOrNoShip;
    }
};

class Map{
    Item board[10][10];
    string type;
public:
    Map();
    
    void setShip(int xIndex, int yIndex, Item ship) {
        board[xIndex][yIndex] = ship;
    }
    
    void setWater() {
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                board[j][i] = Item(0, "W");
            }
        }
    }
    
    Item getItemAt(int x, int y){
        return board[x][y];
    }
    
    bool containsItem(string name){
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                if(board[i][j].getName() == name){
                    return true;
                }
            }
        }
        return false;
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
