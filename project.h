#ifndef PROJECT_H
#define PROJECT_H

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
    Item* board[10][10];
    string type;
public:
    Map(){
        setWater();
    };
    
    void setShip(int xIndex, int yIndex, Item& ship) {
        board[xIndex][yIndex] = &ship;
    }
    
    void setWater() {
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != 10; ++j) {
                Item* water = new Item(0, "W");
                board[j][i] = water;
            }
        }
    }
    
    Item getItemAt(int x, int y){
        return *board[x][y];
    }
    
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
    
    void print() {
        for (int i = 0; i != 10; ++i) {
            if(i == 0){
                cout <<"\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ" << endl;
            }
            cout << i + 1 << "\t";
            for (int j = 0; j != 10; ++j) {
                cout << board[i][j]->getName() << "\t";
            }
            cout << endl;
        }
    }
};

#endif
