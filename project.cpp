#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <algorithm>
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
        }
        else if(selection > 6 || selection < 1){
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
                            Item* aircraftCarrier = new Item(5, "A", false);
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
                            Item* aircraftCarrier = new Item(5, "A", false);
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
                            Item* battleship = new Item(4, "B", false);
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
                            Item* battleship = new Item(4, "B", false);
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
                            Item* submarine = new Item(3, "S", false);
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
                            Item* submarine = new Item(3, "S", false);
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
                            Item* cruiser = new Item(3, "C", false);
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
                            Item* cruiser = new Item(3, "C", false);
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
                            Item* destroyer = new Item(3, "D", false);
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
                            Item* destroyer = new Item(3, "D", false);
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

void modifyShips(Map& userMap){
    string choice = "";
    cout << endl <<"Your current board is:" << endl << endl;
    userMap.print();
    do{
        const char separator    = ' ';
        cout << endl << "Which ship would you like to modify?" << endl << endl;
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
            if(!checkExistence(userMap, "A")){
                cout << "This piece isn't currently on the board."<< endl;
                cout << "Please add current pieces through the main menu" << endl;
                return;
            }
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(userMap.getItemAt(i,j).getName() == "A"){
                        Item* water = new Item(0, "~", false);
                        userMap.setItemAt(i, j, *water);
                    }
                }
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
                            Item* aircraftCarrier = new Item(5, "A", false);
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
                            Item* aircraftCarrier = new Item(5, "A", false);
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
            cout << "Would you like to modify another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        else if(choice == "b"){
            if(!checkExistence(userMap, "B")){
                cout << "This piece isn't currently on the board."<< endl;
                cout << "Please add current pieces through the main menu" << endl;
                return;
            }
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(userMap.getItemAt(i,j).getName() == "B"){
                        Item* water = new Item(0, "~", false);
                        userMap.setItemAt(i, j, *water);
                    }
                }
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
                            Item* battleship = new Item(4, "B", false);
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
                            Item* battleship = new Item(4, "B", false);
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
            cout << "Would you like to modify another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            
        }
        
        //ADD SUBMARINE
        else if (choice == "s"){
            if(!checkExistence(userMap, "S")){
                cout << "This piece isn't currently on the board."<< endl;
                cout << "Please add current pieces through the main menu" << endl;
                return;
            }
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(userMap.getItemAt(i,j).getName() == "S"){
                        Item* water = new Item(0, "~", false);
                        userMap.setItemAt(i, j, *water);
                    }
                }
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
                            Item* submarine = new Item(3, "S", false);
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
                            Item* submarine = new Item(3, "S", false);
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
            cout << "Would you like to modify another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        
        //ADD CRUISER
        else if (choice == "c"){
            if(!checkExistence(userMap, "C")){
                cout << "This piece isn't currently on the board."<< endl;
                cout << "Please add current pieces through the main menu" << endl;
                return;
            }
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(userMap.getItemAt(i,j).getName() == "C"){
                        Item* water = new Item(0, "~", false);
                        userMap.setItemAt(i, j, *water);
                    }
                }
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
                            Item* cruiser = new Item(3, "C", false);
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
                            Item* cruiser = new Item(3, "C", false);
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
            cout << "Would you like to modify another piece? (yes/no) ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        }
        
        //ADD DESTROYER
        else if (choice == "d"){
            if(!checkExistence(userMap, "D")){
                cout << "This piece isn't currently on the board."<< endl;
                cout << "Please add current pieces through the main menu" << endl;
                return;
            }
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(userMap.getItemAt(i,j).getName() == "D"){
                        Item* water = new Item(0, "~", false);
                        userMap.setItemAt(i, j, *water);
                    }
                }
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
                            Item* destroyer = new Item(3, "D", false);
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
                            Item* destroyer = new Item(3, "D", false);
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
            cout << "Would you like to modify another piece? (yes/no) ";
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
int computer_x = 0;
int computer_y = 0;

bool computerGuess(Map& userMap){
    srand(static_cast<unsigned int> (time(NULL)));
    int max_x = 0;
    int max_y = 0;
    int max = 0;
    
    if(previousHit){
        
        if(computer_x != 9){
            if(!userMap.getItemAt(computer_x+1,computer_y).isHit() && chanceArray[computer_x+1][computer_y] > max){
                max_x = computer_x+1;
                max_y = computer_y;
                max = chanceArray[max_x][max_y];
            }
        }
        if(computer_x != 0){
            if(!userMap.getItemAt(computer_x-1,computer_y).isHit() && chanceArray[computer_x-1][computer_y] > max){
                max_x = computer_x-1;
                max_y = computer_y;
                max = chanceArray[max_x][max_y];
            }
        }
        if(computer_y != 9){
            if(!userMap.getItemAt(computer_x,computer_y+1).isHit() && chanceArray[computer_x][computer_y+1] > max){
                max_x = computer_x;
                max_y = computer_y+1;
                max = chanceArray[max_x][max_y];
            }
        }
        if(computer_y != 0){
            if(!userMap.getItemAt(computer_x,computer_y-1).isHit() && chanceArray[computer_x][computer_y-1] > max){
                max_x = computer_x;
                max_y = computer_y-1;
                max = chanceArray[max_x][max_y];
            }
        }
        
        if(max == 0){
            if(computer_x != 9){
                if(!userMap.getItemAt(computer_x+1,computer_y).isHit() || chanceArray[computer_x+1][computer_y] > max){
                    max_x = computer_x+1;
                    max_y = computer_y;
                    max = chanceArray[max_x][max_y];
                }
            }
            if(computer_x != 0){
                if(!userMap.getItemAt(computer_x-1,computer_y).isHit() || chanceArray[computer_x-1][computer_y] > max){
                    max_x = computer_x-1;
                    max_y = computer_y;
                    max = chanceArray[max_x][max_y];
                }
            }
            if(computer_y != 9){
                if(!userMap.getItemAt(computer_x,computer_y+1).isHit() || chanceArray[computer_x][computer_y+1] > max){
                    max_x = computer_x;
                    max_y = computer_y+1;
                    max = chanceArray[max_x][max_y];
                }
            }
            if(computer_y != 0){
                if(!userMap.getItemAt(computer_x,computer_y-1).isHit() || chanceArray[computer_x][computer_y-1] > max){
                    max_x = computer_x;
                    max_y = computer_y-1;
                    max = chanceArray[max_x][max_y];
                }
            }
            previousHit = false;
        }
    }
    
    if(!previousHit){
        
        //find an open index
        
        do{
            max_x = rand()%10;
            max_y = rand()%10;
            max = chanceArray[max_x][max_y];
        } while(userMap.getItemAt(max_x,max_y).isHit());
        
        
        //find max index
        for(int i = 0; i < 10; i++){
            for(int j = 0; j <10; j++){
                if(chanceArray[i][j] > max){
                    if(rand()%10 == 0 && !userMap.getItemAt(i,j).isHit() && chanceArray[i][j] != 1){
                        max_x = i;
                        max_y = j;
                        max = chanceArray[i][i];
                    }
                }
                else if(chanceArray[i][j] == max && !userMap.getItemAt(i,j).isHit() && chanceArray[i][j] != 1){
                    if(rand()%25 == 0){
                        max_x = i;
                        max_y = j;
                        max = chanceArray[i][i];
                    }
                }
            }
        }
        if(max == 0){
            do{
                max_x = rand()%10;
                max_y = rand()%10;
            } while(userMap.getItemAt(max_x,max_y).isHit());
        }
    }
    
    //fire
    string name = userMap.getItemAt(max_x,max_y).getName();
    userMap.getItemAt(max_x,max_y).itemHit();
    if(userMap.getItemAt(max_x,max_y).isShip()){
        previousHit = true;
        computer_x = max_x;
        computer_y = max_y;
        
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(i == max_x){
                    chanceArray[i][j]++;
                }
                if(j == max_y){
                    chanceArray[i][j]++;
                }
            }
        }
        Item* hit = new Item(0, "X", true);
        userMap.setItemAt(max_x,max_y,*hit);
        
        
        if(checkExistence (userMap, name)){
            cout << "The computer hit your ";
            if(name == "S"){
                cout << "Submarine!" << endl;
            }
            else if(name == "A"){
                cout << "Aircraft Carrier!" << endl;
            }
            else if(name == "B"){
                cout << "Battleship!" << endl;
            }
            else if(name == "C"){
                cout << "Cruiser!" << endl;
            }
            else if(name == "D"){
                cout << "Destroyer!" << endl;
            }
        }
        else{
            previousHit = false;
            cout << "The computer sunk your ";
            if(name == "S"){
                cout << "Submarine!" << endl;
            }
            else if(name == "A"){
                cout << "Aircraft Carrier!" << endl;
            }
            else if(name == "B"){
                cout << "Battleship!" << endl;
            }
            else if(name == "C"){
                cout << "Cruiser!" << endl;
            }
            else if(name == "D"){
                cout << "Destroyer!" << endl;
            }
        }
        return true;
    }
    else{
        cout << "The computer missed." << endl;
        Item* hit = new Item(0, "O", true);
        userMap.setItemAt(max_x,max_y,*hit);
        return false;
    }
}

void generateShips(Map& computerMap){
    
    //ADD AIRCRAFT CARRIER
    if(!computerMap.containsItem("A")){
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
                        Item* aircraftCarrier = new Item(5, "A", false);
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
                        Item* aircraftCarrier = new Item(5, "A", false);
                        computerMap.setItemAt(x+i, y, *aircraftCarrier);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD BATTLESHIP
    if(!computerMap.containsItem("B")){
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
                        Item* battleship = new Item(4, "B", false);
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
                        Item* battleship = new Item(4, "B", false);
                        computerMap.setItemAt(x+i, y, *battleship);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD SUBMARINE
    if(!computerMap.containsItem("S")){
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
                        Item* submarine = new Item(3, "S", false);
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
                        Item* submarine = new Item(3, "S", false);
                        computerMap.setItemAt(x+i, y, *submarine);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD cruiser
    if(!computerMap.containsItem("C")){
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
                        Item* cruiser = new Item(3, "C", false);
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
                        Item* cruiser = new Item(3, "C", false);
                        computerMap.setItemAt(x+i, y, *cruiser);
                    }
                }
            }
        } while(!freeSpace);
    }
    
    //ADD destroyer
    if(!computerMap.containsItem("D")){
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
                        Item* destroyer = new Item(2, "D", false);
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
                        Item* destroyer = new Item(2, "D", false);
                        computerMap.setItemAt(x+i, y, *destroyer);
                    }
                }
            }
        } while(!freeSpace);
    }
}

bool userTurn(Map& computerMap, Map& userMap, int& moveCounter){
    //print maps
    moveCounter++;
    cout << "Your map: " << endl << endl;
    userMap.print();
    cout << endl << endl << "Computer's map:" << endl << endl;
    computerMap.printGameMap();
    
    cout << endl << endl << "Where would you like to make move " << moveCounter << "? ";
    
    //get valid move
    string choice;
    int move_x;
    int move_y;
    bool invalidChoice;
    do{
        //make sure user input is valid
        move_x = -1;
        move_y = -1;
        invalidChoice = false;
        do{
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if(choice.size() == 2){
                if(choice[0] >= 'a' && choice[0] <= 'j' && choice[1] > '0' && choice[1] <='9'){
                    move_x = choice[1] - '0' - 1;
                    move_y = choice[0] - 'a';
                }
                else{
                    cout << "Invalid guess. Try again." << endl;
                }
            }
            else if(choice.size() == 3){
                if(choice[0] >= 'a' && choice[0] <= 'j' && choice[2] == '0' && choice[1] == '1'){
                    move_x = 9;
                    move_y = choice[0] - 'a';
                }
                else{
                    cout << "Invalid guess. Try again." << endl;
                }
            }
            else{
                cout << "Invalid guess. Try again." << endl;
            }
        }while(move_x < 0 || move_y < 0);
        
        //make sure spot hasn't already been hit before
        if(computerMap.getItemAt(move_x,move_y).isHit()){
            invalidChoice = true;
            cout << "Invalid guess. Try again." << endl;
        }
    }while(invalidChoice);
    
    //fire
    string name = computerMap.getItemAt(move_x,move_y).getName();
    if(computerMap.getItemAt(move_x,move_y).isShip()){
        Item* hit = new Item(0, "X", true);
        computerMap.setItemAt(move_x,move_y,*hit);
        
        if(checkExistence (computerMap, name)){
            cout << "You hit your opponent's ";
            if(name == "S"){
                cout << "Submarine!" << endl;
            }
            else if(name == "A"){
                cout << "Aircraft Carrier!" << endl;
            }
            else if(name == "B"){
                cout << "Battleship!" << endl;
            }
            else if(name == "C"){
                cout << "Cruiser!" << endl;
            }
            else if(name == "D"){
                cout << "Destroyer!" << endl;
            }
        }
        else{
            cout << "You sunk your opponent's ";
            if(name == "S"){
                cout << "Submarine!" << endl;
            }
            else if(name == "A"){
                cout << "Aircraft Carrier!" << endl;
            }
            else if(name == "B"){
                cout << "Battleship!" << endl;
            }
            else if(name == "C"){
                cout << "Cruiser!" << endl;
            }
            else if(name == "D"){
                cout << "Destroyer!" << endl;
            }
        }
        return true;
    }
    else{
        Item* hit = new Item(0, "O", true);
        computerMap.setItemAt(move_x,move_y,*hit);
        cout << "You missed." << endl;
        return false;
    }
}


int main(int argc, char ** argv){
    srand(static_cast<unsigned int> (time(NULL)));
    string fileLoad;
    transform(fileLoad.begin(), fileLoad.end(), fileLoad.begin(), ::tolower);
    
    if (argc >= 2) {
        fileLoad = argv[1];
    }
    else {
        cout << "Invalid choice. Try again." << endl;
        return 1;
    }
    if(fileLoad != "erase" && fileLoad != "load"){
        cout << "Invalid choice. Try again." << endl;
        return 1;
    }
    
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
            modifyShips(*userMap);
        }
        else if(menuSelection == 5){
            userMap->print();
        }
    }while(menuSelection != 6 && menuSelection != 1);
    
    if(menuSelection == 6){
        return 0;
    }
    if (menuSelection == 1){
        generateShips(*computerMap);
        int moveCounter = 0;
        if(!checkExistence(*userMap, "A") || !checkExistence(*userMap, "B") || !checkExistence(*userMap, "C") || !checkExistence(*userMap, "S") || !checkExistence(*userMap, "D")){
            generateShips(*userMap);
            cout << "You didn't finish placing all of your ships. The computer generated the rest for you." << endl << endl;
        }
        cout << "How to play:" << endl;
        cout << "1. User will go first" << endl;
        cout << "2. On your turn, select a valid spot on the computer's map to fire at" << endl;
        cout << "3. Hits on the map will be denoted with Xs, misses will be denoted with Os" << endl;
        cout << "4. The first player to sink all of their enemies ships will be the winner" << endl;
        cout << "Good luck!" << endl << endl;
        
        bool continuePlaying = true;
        do{
            if(userTurn(*computerMap, *userMap, moveCounter)){
                if(!checkExistence(*computerMap, "A") && !checkExistence(*computerMap, "B") && !checkExistence(*computerMap, "C") && !checkExistence(*computerMap, "S") && !checkExistence(*computerMap, "D")){
                    cout << "Congratulations! You sunk all of your opponent's ships! You won!";
                    break;
                }
            }
            if(computerGuess(*userMap)){
                previousHit = true;
                if(!checkExistence(*userMap, "A") && !checkExistence(*userMap, "B") && !checkExistence(*userMap, "C") && !checkExistence(*userMap, "S") && !checkExistence(*userMap, "D")){
                    cout << "Oh no! The computer sunk all of your ships! You lost. :(";
                    break;
                }
            }
        }while(continuePlaying);
    }
    
    //put stuff here!
    
    
    //write to file at end of program
    ofstream out("likelihood.txt");
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            out << chanceArray[i][j] << " ";
        }
        out << endl;
    }
    out.close();
    return 0;
}
