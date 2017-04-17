//Move checkExistence method to this file, remove from project.cpp.
//Add "bomb.h" to head of project.cpp.
#ifndef BOMB_H_
#define BOMB_H_

#include <string>
using namespace std;

class bomb {
private:
	int uses;
public:
	bomb();		//default constructor
	void useBomb(string, Map&);		//method to change a 3x3 area to hits/misses
};
bomb::bomb() {
    uses = 1;	//only can use 1 bomb in game
}

bool checkExistence(Map& map, string item){		//iterates through specified map to find item
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(map.getItemAt(i,j).getName() == item){
                return true;
            }
        }
    }
    return false;
}

void bomb::useBomb(string guess, Map& map) {	//takes point and fires a 3x3 area around it
	int col, row;
	if(uses > 0) {		//if have bomb, change guess to ints
		if(guess[0] >= 'a' && guess[0] <= 'j' && guess[1] > '0' && guess[1] <='9'){
			col = guess[1] - '0' - 1;
		    row = guess[0] - 'a';
		}
		else{
			cout << "Invalid guess. Try again." << endl;
		}

		for(int i = col-1; i < col+2; i++) {	//iterate through 3x3 part of array, with guess as center
			for(int j = row-1; j < row+2; j++) {
				string name = map.getItemAt(i, j).getName();

				if(map.getItemAt(col, row).isShip()){		//if hit, change to item of name X
					Item* hit = new Item(0, "X", true);
					map.setItemAt(col, row, *hit);

					if(checkExistence(map, name)){
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
				}
				else{		//if miss, change to item of name O
					Item* hit = new Item(0, "O", true);
					map.setItemAt(col, row, *hit);
					cout << "You missed." << endl;
				}

			}
		}

		uses--;
	}
	else { 		//have no bombs to use
		cout << "Out of uses of for a bomb.";
	}

}

#endif /* BOMB_H_ */
