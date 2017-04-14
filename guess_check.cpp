#include <iostream>
using namespace std;

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