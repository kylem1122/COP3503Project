# COP3503Project
Term Project

# RUN
./project load
  //Runs project with data from previous games
./project erase
  //Runs project with a 10x10 grid of 1's
  
  
# GUESSING ALGORITHM
1. Load file
2. First fire: Hit a random highest number
3. Second fire:
     a. If hit: hit in clockwise manner until you get another hit OR hit the number surrounding it that is highest. Increment         both the row and column the hit is in up by 1.
     b. If miss: choose another open high number. If the next highest numbers are directly touching the previous hit, choose a         different block.
4. Repeat
5. Update and save file
