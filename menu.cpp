#include <iostream>
using namespace std;



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
