#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "project.h"

using namespace std;

//menu method
int menu(){
    cout<< endl << "Welcome to War Boats"<< endl;
    int selection = 0;
    do{
        cout<< endl << "Please select an option:"<< endl;
        cout<< "1 - Start Game "<< endl;
        cout<< "2 - Place Pieces" << endl;
        cout<< "3 - Modify Pieces "<< endl;
        cout<< "4 - Print Current Map" << endl;
        cout<< "5 - Exit "<< endl;
        cin>> selection;
        if(cin.fail() || selection > 5 || selection < 1){
            cin.clear();
            cout << "ERROR: Invalid selection. Try again." << endl << endl;
        }
    }while(cin.fail() || selection > 5 || selection < 1);
    return selection;
}

//LET THE USER ADD SHIPS
void userAddShip(Map& userMap){
    string choice = "";
    cout << endl <<"Your current board is:" << endl << endl;
    userMap.print();
    do{
        const char separator    = ' ';
        cout << endl << "Which ship would you like to place?" << endl << endl;
        cout << left << setw(10) << setfill(separator) << "Symbol";
        cout << left << setw(18) << setfill(separator) << "Name";
        cout << left << setw(10) << setfill(separator) << "Length";
        cout << endl;
        cout << "-----------------------------------" << endl;
        cout << left << setw(10) << setfill(separator) << "A";
        cout << left << setw(18) << setfill(separator) << "Aircraft Carrier";
        cout << left << setw(10) << setfill(separator) << "5";
        cout << endl;
        cout << left << setw(10) << setfill(separator) << "B";
        cout << left << setw(18) << setfill(separator) << "Battleship";
        cout << left << setw(10) << setfill(separator) << "4";
        cout << endl;
        cout << left << setw(10) << setfill(separator) << "S";
        cout << left << setw(18) << setfill(separator) << "Submarine";
        cout << left << setw(10) << setfill(separator) << "3";
        cout << endl;
        cout << left << setw(10) << setfill(separator) << "C";
        cout << left << setw(18) << setfill(separator) << "Cruiser";
        cout << left << setw(10) << setfill(separator) << "3";
        cout << endl;
        cout << left << setw(10) << setfill(separator) << "D";
        cout << left << setw(18) << setfill(separator) << "Destroyer";
        cout << left << setw(10) << setfill(separator) << "2";
        cout << endl << endl << "Choose a symbol: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        
        if(choice == "a"){
            cout << endl << endl << "You chose to add an Aircraft Carrier" << endl;
            cout << "The length of an Aircraft Carrier is 5" << endl;
            cout << "Which direction would you like your ship?" << endl;
            cout << "H - Horizontal" << endl;
            cout << "V - Vertical" << endl;
            cout << "Choice: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "horizontal" || choice == "h"){
                cout << endl << "Where would you like to place the farthest left edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'g'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() == 3){
                            if(choice[2] == '0'){
                                row = 9;
                            }
                            else{
                                cout << "Invalid selection." << endl << endl;
                                return;
                            }
                        }
                        else if(choice.size() > 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0';
                        }
                        
                        for(int i = 0; i != 5; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            userMap.setItemAt(row, column+i, *aircraftCarrier);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else if(choice == "vertical" || choice == "v"){
                cout << endl << "Where would you like to place the topmost edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'k'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '6'){
                        if(choice.size() >= 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 5; i++){
                            if(userMap.getItemAt(row+i,column).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 5; i++){
                            Item* aircraftCarrier = new Item(5, "A");
                            userMap.setItemAt(row+i, column, *aircraftCarrier);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else{
                cout << endl << "ERROR: Invalid choice" << endl;
                return;
            }
            cout << "Would you like to add another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        else if(choice == "b"){
            cout << endl << endl << "You chose to add a Battleship" << endl;
            cout << "The length of a Battleship is 4" << endl;
            cout << "Which direction would you like your ship?" << endl;
            cout << "H - Horizontal" << endl;
            cout << "V - Vertical" << endl;
            cout << "Choice: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "horizontal" || choice == "h"){
                cout << endl << "Where would you like to place the farthest left edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'h'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() == 3){
                            if(choice[2] == '0'){
                                row = 9;
                            }
                            else{
                                cout << "Invalid selection." << endl << endl;
                                return;
                            }
                        }
                        else if(choice.size() > 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 4; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(4, "B");
                            userMap.setItemAt(row, column+i, *battleship);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else if(choice == "vertical" || choice == "v"){
                cout << endl << "Where would you like to place the topmost edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'k'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '7'){
                        if(choice.size() >= 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 4; i++){
                            if(userMap.getItemAt(row+i,column).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 4; i++){
                            Item* battleship = new Item(4, "B");
                            userMap.setItemAt(row+i, column, *battleship);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else{
                cout << endl << "ERROR: Invalid choice" << endl;
                return;
            }
            cout << "Would you like to add another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            
        }
        
        //ADD SUBMARINE
        else if (choice == "s"){
            cout << endl << endl << "You chose to add a Submarine" << endl;
            cout << "The length of a Submarine is 3" << endl;
            cout << "Which direction would you like your ship?" << endl;
            cout << "H - Horizontal" << endl;
            cout << "V - Vertical" << endl;
            cout << "Choice: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "horizontal" || choice == "h"){
                cout << endl << "Where would you like to place the farthest left edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'i'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() == 3){
                            if(choice[2] == '0'){
                                row = 9;
                            }
                            else{
                                cout << "Invalid selection." << endl << endl;
                                return;
                            }
                        }
                        else if(choice.size() > 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 3; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(3, "S");
                            userMap.setItemAt(row, column+i, *submarine);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else if(choice == "vertical" || choice == "v"){
                cout << endl << "Where would you like to place the topmost edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'k'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '8'){
                        if(choice.size() >= 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 3; i++){
                            if(userMap.getItemAt(row+i,column).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 3; i++){
                            Item* submarine = new Item(3, "S");
                            userMap.setItemAt(row+i, column, *submarine);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else{
                cout << endl << "ERROR: Invalid choice" << endl;
                return;
            }
            cout << "Would you like to add another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        
        //ADD CRUISER
        else if (choice == "c"){
            cout << endl << endl << "You chose to add a Cruiser" << endl;
            cout << "The length of a Cruiser is 3" << endl;
            cout << "Which direction would you like your ship?" << endl;
            cout << "H - Horizontal" << endl;
            cout << "V - Vertical" << endl;
            cout << "Choice: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "horizontal" || choice == "h"){
                cout << endl << "Where would you like to place the farthest left edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'i'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() == 3){
                            if(choice[2] == '0'){
                                row = 9;
                            }
                            else{
                                cout << "Invalid selection." << endl << endl;
                                return;
                            }
                        }
                        else if(choice.size() > 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 3; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(3, "C");
                            userMap.setItemAt(row, column+i, *cruiser);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else if(choice == "vertical" || choice == "v"){
                cout << endl << "Where would you like to place the topmost edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'k'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '8'){
                        if(choice.size() >= 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 3; i++){
                            if(userMap.getItemAt(row+i,column).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 3; i++){
                            Item* cruiser = new Item(3, "C");
                            userMap.setItemAt(row+i, column, *cruiser);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else{
                cout << endl << "ERROR: Invalid choice" << endl;
                return;
            }
            cout << "Would you like to add another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        
        //ADD DESTROYER
        else if (choice == "d"){
            cout << endl << endl << "You chose to add a Destroyer" << endl;
            cout << "The length of a Destroyer is 2" << endl;
            cout << "Which direction would you like your ship?" << endl;
            cout << "H - Horizontal" << endl;
            cout << "V - Vertical" << endl;
            cout << "Choice: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "horizontal" || choice == "h"){
                cout << endl << "Where would you like to place the farthest left edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'j'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() == 3){
                            if(choice[2] == '0'){
                                row = 9;
                            }
                            else{
                                cout << "Invalid selection." << endl << endl;
                                return;
                            }
                        }
                        else if(choice.size() > 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 2; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(3, "D");
                            userMap.setItemAt(row, column+i, *destroyer);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else if(choice == "vertical" || choice == "v"){
                cout << endl << "Where would you like to place the topmost edge? ";
                cin >> choice;
                transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                int column = 0;
                int row = 0;
                
                if(choice[0] >= 'a' && choice[0] < 'k'){
                    column = choice[0] - 'a';
                    if(choice[1] > '0' && choice[1] <= '9'){
                        if(choice.size() >= 3){
                            cout << "Invalid selection." << endl << endl;
                            return;
                        }
                        else{
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 2; i++){
                            if(userMap.getItemAt(row+i,column).getName() != "W"){
                                cout << "Another ship is already here" << endl;
                                return;
                            }
                        }
                        for(int i = 0; i != 2; i++){
                            Item* destroyer = new Item(3, "D");
                            userMap.setItemAt(row+i, column, *destroyer);
                        }
                        cout << endl << endl << "Your new map is: " << endl << endl;
                        userMap.print();
                    }
                    else{
                        cout << "Invalid selection." << endl << endl;
                        return;
                    }
                }
                else{
                    cout << "Invalid selection." << endl << endl;
                    return;
                }
            }
            else{
                cout << endl << "ERROR: Invalid choice" << endl;
                return;
            }
            cout << "Would you like to add another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        else{
            cout << endl << "ERROR: Invalid choice" << endl;
            choice = "no";
        }
    }while(choice == "yes");
}


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

    
    //Make maps
    Map* userMap = new Map();
    Map* computerMap = new Map();
    int menuSelection;
    do{
        menuSelection = menu();
        if(menuSelection == 2){
            userAddShip(*userMap);
        }
        else if(menuSelection == 3){
            //MODIFY SHIPS
        }
        else if(menuSelection == 4){
            userMap->print();
        }
    }while(menuSelection != 5 && menuSelection != 1);
    
    
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
