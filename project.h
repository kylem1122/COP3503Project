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
    Item(int size, string name, bool hit){
        this->size = size;
        this->name = name;
        this->hit = hit;
        if(name == "~"){
            shipOrNoShip = false;
        }
    };
    
    bool isHit() {
        return this->hit;
    }
    
    void itemHit(){
        this->hit = true;
        if(this->isShip()){
            this->name = "X";
        }
        else{
            this->name = "O";
        }
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
                Item* water = new Item(0, "~", false);
                board[j][i] = water;
            }
        }
    }
    
    Item getItemAt(int x, int y){
        return *board[x][y];
    }
    
    void setItemAt(int x, int y, Item newItem){
        *board[x][y] = newItem;
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
    
    void printGameMap() {
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
