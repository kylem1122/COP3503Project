/*
 * ComputerFire.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Jack Schulte
 */

#include <stdlib.h>

void computerFire() {

	//int to keep track of # of hits around hit & row and column to target
	int aroundHitCounter = 0;
	int columnGuess;
	int rowGuess;

	//iterate through previous hit attempts
	for (int i = 3; i > -1; i--) {
		//if previous attack hit ship, hit spots around it to find ships
		if (lastHits[i]->name == "Hit") {
			int row = lastHits[i]->row;
			int col = lastHits[i]->col;

			if (aroundHitCounter == 0) { //first shot to right of hit
				col++;
				aroundHitCounter++;
			}
			else if (aroundHitCounter == 1) { //second shot to top of hit
				col--;
				row--;
				aroundHitCounter++;
			}
			else if (aroundHitCounter == 2) { //third shot to left of hit
				row++;
				col--;
				aroundHitCounter++;
			}
			else { //fourth shot to bottom of hit
				col++;
				row++;
				aroundHitCounter++;
			}

			//make final selection of column and row & reset hit counter
			rowGuess = row;
			columnGuess = col;

		}
		//if no previous hits are found, make a random guess in the board
		else {
			do {
				columnGuess = rand() % 10;
				rowGuess = rand() % 10;
			} while(gameBoard.isHit()); 	//check to see if spot has been hit before
		}
	}

	if (gameBoard[rowGuess][columnGuess].getType == Ship) {		//if the spot shot is a ship object, change it to a "hit" object
		gameBoard[rowGuess][columnGuess]->name = "Hit";
		aroundHitCounter = 0;
	}
	else {
		gameBoard[rowGuess][columnGuess]->name = "Miss"; 	//if not a ship object, become a "miss" object
	}

	gameBoard[rowGuess][columnGuess]->isShot = true; 	//change the spot's shot status to have being shot before

}
