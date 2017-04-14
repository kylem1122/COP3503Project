#ifndef PROGRAM_H
#define PROGRAM_H

//create classes
#include <iostream>
using namespace std; 

//menu method
int menu(){
    int selection = 0;
    while(selection > 4 || selection < 0){
    cout<< "Welcome to War Boats"<< endl;
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
