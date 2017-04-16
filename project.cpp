#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "project.h"

using namespace std;

//check if piece exists
bool checkExistence(Map& map, string item){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(map.getItemAt(i,j).getName() == item){
                return true;
            }
        }
    }
    return false;
}

bool checkExistence(Map& map, Item& item){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(map.getItemAt(i,j).getName() == item.getName()){
                return true;
            }
        }
    }
    return false;
}

//menu method
int menu(){
    int selection = 0;
    bool tryAgain;
    do{
        tryAgain = false;
        cout<< endl << "Please select an option:"<< endl;
        cout<< "1 - Start Game "<< endl;
        cout<< "2 - Manually Place Pieces" << endl;
        cout<< "3 - Automatically Place Pieces" << endl;
        cout<< "4 - Modify Pieces "<< endl;
        cout<< "5 - Print Current Map" << endl;
        cout<< "6 - Exit "<< endl;
        if(!(cin >> selection)){
            cout << endl << "ERROR: Invalid selection. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if(selection > 5 || selection < 1){
            cout << endl << "ERROR: Invalid selection. Try again." << endl;
            tryAgain = true;
        }
    }while(tryAgain);
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
            if(checkExistence(userMap, "A")){
                cout << "This piece is currently on the board."<< endl;
                cout << "Please modify current pieces through the main menu" << endl;
                return;
            }
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
                            row = choice[1] - '0' - 1;
                        }
                        
                        for(int i = 0; i != 5; i++){
                            if(userMap.getItemAt(row,column+i).getName() != "~"){
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
                            if(userMap.getItemAt(row+i,column).getName() != "~"){
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
            if(checkExistence(userMap, "B")){
                cout << "This piece is currently on the board."<< endl;
                cout << "Please modify current pieces through the main menu" << endl;
                return;
            }
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
                            if(userMap.getItemAt(row,column+i).getName() != "~"){
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
                            if(userMap.getItemAt(row+i,column).getName() != "~"){
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
            if(checkExistence(userMap, "S")){
                cout << "This piece is currently on the board."<< endl;
                cout << "Please modify current pieces through the main menu" << endl;
                return;
            }
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
                            if(userMap.getItemAt(row,column+i).getName() != "~"){
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
                            if(userMap.getItemAt(row+i,column).getName() != "~"){
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
            if(checkExistence(userMap, "C")){
                cout << "This piece is currently on the board."<< endl;
                cout << "Please modify current pieces through the main menu" << endl;
                return;
            }
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
                            if(userMap.getItemAt(row,column+i).getName() != "~"){
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
                            if(userMap.getItemAt(row+i,column).getName() != "~"){
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
            if(checkExistence(userMap, "D")){
                cout << "This piece is currently on the board."<< endl;
                cout << "Please modify current pieces through the main menu" << endl;
                return;
            }
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
                            if(userMap.getItemAt(row,column+i).getName() != "~"){
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
                            if(userMap.getItemAt(row+i,column).getName() != "~"){
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
        srand(static_cast<unsigned int> (time(NULL)));
        bool freeSpace;
        do{
            freeSpace = true;
            //vertical
            if(rand() % 2){
                int x = rand() % 10;
                int y = rand() % 6;
                for(int i = 0; i != 5; i++){
                    if(computerMap.getItemAt(x,y+i).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 5; i++){
                        Item* aircraftCarrier = new Item(5, "A");
                        computerMap.setItemAt(x, y + i, *aircraftCarrier);
                    }
                }
            }
            //horizontal
            else{
                int x = rand() % 6;
                int y = rand() % 10;
                for(int i = 0; i != 5; i++){
                    if(computerMap.getItemAt(x+i,y).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 5; i++){
                        Item* aircraftCarrier = new Item(5, "A");
                        computerMap.setItemAt(x+i, y, *aircraftCarrier);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD BATTLESHIP
    if(!computerMap.containsItem("B")){
        srand(static_cast<unsigned int> (time(NULL)));
        bool freeSpace;
        do{
            freeSpace = true;
            //vertical
            if(rand() % 2){
                int x = rand() % 10;
                int y = rand() % 7;
                for(int i = 0; i !=4; i++){
                    if(computerMap.getItemAt(x,y+i).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 4; i++){
                        Item* battleship = new Item(4, "B");
                        computerMap.setItemAt(x, y+i, *battleship);
                    }
                }
            }
            //horizontal
            else{
                int x = rand() % 7;
                int y = rand() % 10;
                for(int i = 0; i != 4; i++){
                    if(computerMap.getItemAt(x+i,y).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 4; i++){
                        Item* battleship = new Item(4, "B");
                        computerMap.setItemAt(x+i, y, *battleship);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD SUBMARINE
    if(!computerMap.containsItem("S")){
        srand(static_cast<unsigned int> (time(NULL)));
        bool freeSpace;
        do{
            freeSpace = true;
            //vertical
            if(rand() % 2){
                int x = rand() % 10;
                int y = rand() % 8;
                for(int i = 0; i !=3; i++){
                    if(computerMap.getItemAt(x,y+i).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 3; i++){
                        Item* submarine = new Item(3, "S");
                        computerMap.setItemAt(x, y+i, *submarine);
                    }
                }
            }
            //horizontal
            else{
                int x = rand() % 8;
                int y = rand() % 10;
                for(int i = 0; i != 3; i++){
                    if(computerMap.getItemAt(x+i,y).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 3; i++){
                        Item* submarine = new Item(3, "S");
                        computerMap.setItemAt(x+i, y, *submarine);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD cruiser
    if(!computerMap.containsItem("C")){
        srand(static_cast<unsigned int> (time(NULL)));
        bool freeSpace;
        do{
            freeSpace = true;
            //vertical
            if(rand() % 2){
                int x = rand() % 10;
                int y = rand() % 8;
                for(int i = 0; i !=3; i++){
                    if(computerMap.getItemAt(x,y+i).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 3; i++){
                        Item* cruiser = new Item(3, "C");
                        computerMap.setItemAt(x, y+i, *cruiser);
                    }
                }
            }
            //horizontal
            else{
                int x = rand() % 8;
                int y = rand() % 10;
                for(int i = 0; i != 3; i++){
                    if(computerMap.getItemAt(x+i,y).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 3; i++){
                        Item* cruiser = new Item(3, "C");
                        computerMap.setItemAt(x+i, y, *cruiser);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD destroyer
    if(!computerMap.containsItem("D")){
        srand(static_cast<unsigned int> (time(NULL)));
        bool freeSpace;
        do{
            freeSpace = true;
            //vertical
            if(rand() % 2){
                int x = rand() % 10;
                int y = rand() % 9;
                for(int i = 0; i !=2; i++){
                    if(computerMap.getItemAt(x,y+i).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 2; i++){
                        Item* destroyer = new Item(2, "D");
                        computerMap.setItemAt(x, y+i, *destroyer);
                    }
                }
            }
            //horizontal
            else{
                int x = rand() % 9;
                int y = rand() % 10;
                for(int i = 0; i != 2; i++){
                    if(computerMap.getItemAt(x+i,y).getName() != "~"){
                        freeSpace = false;
                        break;
                    }
                }
                if(freeSpace){
                    for(int i = 0; i != 2; i++){
                        Item* destroyer = new Item(2, "D");
                        computerMap.setItemAt(x+i, y, *destroyer);
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
    
    cout<< endl << "Welcome to War Boats!"<< endl;
    
    //Make maps
    Map* userMap = new Map();
    Map* computerMap = new Map();
    int menuSelection;
    do{
        menuSelection = menu();
        if(menuSelection == 2){
            userAddShip(*userMap);
        }
        if(menuSelection == 3){
            generateShips(*userMap);
            cout << "Your new map is: " << endl << endl;
            userMap->print();
        }
        else if(menuSelection == 4){
            //MODIFY SHIPS
        }
        else if(menuSelection == 5){
            userMap->print();
        }
    }while(menuSelection != 6 && menuSelection != 1);
    
    if(menuSelection == 5){
        return 0;
    }
    if (menuSelection == 1){
        generateShips(*computerMap);
        computerMap->print();
    }
    
    
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
