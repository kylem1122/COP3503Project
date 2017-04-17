## COMPILE
g++ -o projecct project.cpp -std=c++11 -Wall

## RUN
### ./project create
If lacking a file with data, this will create a file with a 10x10 grid.

### ./project load
Runs project with data from previous games
  
### ./project erase
Erases previous data, starts over with a 10x10 grid and overwrites the file.
  
## PLACING PIECES
1. Enter in character that represents a ship: A, B, S, C, D.
2. Choose orientation of ship: H or V.
3. Pick point to place ship, leftmost for horizontal and topmost for vertical.
4. Repeat for up to 5 ships.
5. If ships are missing, the computer will randomly assign them placement when the game starts.

## HOW TO PLAY
1. Place pieces manually or automatically.
2. Start game through option in main menu.
3. Enter inputs as letter-number combination, such as A8.
4. Repeat entering inputs until all of one player's ships are sunk.
