/*
 * bomb.h
 *
 *  Created on: Apr 15, 2017
 *     a special type of attack the user can use when firing upon the enemy. It fires in  3x3 space and hits any ships in the area
 *
 */



#ifndef BOMB_H_
#define BOMB_H_

#include <string>
using namespace std;
//create the bomb class, which has 3 methods, useBomb, getUses, and setUses
class bomb {
private:
	int uses;
public:
	bomb();
	void useBomb(string, Map&);

	int getUses();
	void setUses(int newUses);

};
//default constructor
bomb::bomb() {
    uses = 1;

}
//getter method to get the number of uses
int bomb::getUses()
{
	return uses;
}
//setter method for the number of uses
void bomb::setUses(int newUses)
{
	uses = newUses;
}
//checkExistence which checks to see if the item matches in the array
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
//use bomb, the main method of bomb, this fires on a 3x3 space with the center where the user specifies
void bomb::useBomb(string guess, Map& map) {
	bool validInput = false;
	int col, row;
	bool hitAny = false;
	if(uses > 0) {
		//checks to see if the guess is on the edges, if it is, asks the user to input something else
		while (validInput == false)
		{
			//checks to see if the user put in the right amount of coordinates
			if (guess.size() == 2)
			{
				//converts the input into ints to be used in loop
		if(guess[0] >= 'b' && guess[0] <= 'i' && guess[1] > '1' && guess[1] <='9'){
			col = guess[1] - '0' - 1;
		    row = guess[0] - 'a';
		    validInput = true;
		}
		else{
			cout << "Invalid guess. Try again." << endl;
			cin >> guess;
			}
			}
			else
			{
				cout << "Invalid guess. Try again." << endl;
				cin >> guess;
			}

		}
		//loop to iterate thru the 3x3 space on the board
		for(int i = col-1; i < col+2; i++) {
			for(int j = row-1; j < row+2; j++) {
				string name = map.getItemAt(i, j).getName();
				//checks to make sure none of the spots have already been fired upon, if they have, skips over them
				if(!(map.getItemAt(i,j).isHit())){
					//checks to see if the spot on the board contains a ship, if it does, marks it as a hit
				if(map.getItemAt(i, j).isShip()){
					Item* hit = new Item(0, "X", true);
					map.setItemAt(i, j, *hit);
					hitAny = true;
					//checks to see what type of ship was hit
					if(checkExistence(map, name)){
						if(name == "S"){
							cout << "You hit your opponent's ";
							cout << "Submarine!" << endl;
						}
						else if(name == "A"){
							cout << "You hit your opponent's ";
							cout << "Aircraft Carrier!" << endl;
						}
						else if(name == "B"){
							cout << "You hit your opponent's ";
							cout << "Battleship!" << endl;
						}
						else if(name == "C"){
							cout << "You hit your opponent's ";
							cout << "Cruiser!" << endl;
						}
						else if(name == "D"){
							cout << "You hit your opponent's ";
							cout << "Destroyer!" << endl;
						}
						else {
							cout<< endl;
						}
					}
					//if the ship is sunk, prints this out to the user
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
				//if the shot misses, marks the spot as an O
				else{
					Item* hit = new Item(0, "O", true);
					map.setItemAt(i,j,*hit);

				}

			}
			}
		}
		//if nothing in the 3x3 space is a hit, tells the user that they didnt hit anything
		if(hitAny == false)
		{
			cout << "You didn't hit anything" << endl;
		}

		uses--;
	}
	//prints when the user runs out of bombs
	else {
		cout << "Out of bombs.";
	}

}

#endif /* BOMB_H_ */





