# How it works
Every time the program has to make a movement, it **calculates all possible movements and their endings** (machine winning, lossing or ties). It keeps a record of the initial movement that triggered them. 

Once all the arragements has been explored, it takes the movement that obtained the **highest number of winning endings and lowest number of lossing endings**,  and that's the movements the machine takes in that turn.

## In depth
The technique used to calculate all possible movements is **Backtracking**. 

Given the current arrangement of the board at a certain point of the game, a backtracking function **anticipates all possible outcomes** for the movements that the machine can make in that turn. Everytime it finds a sequence of movements that give rise to the machine winning or lossing, it **keeps a record of the initial movement that triggered it**. 

Also it takes into account how many cycles are needed for this outcome to take place, in the sense that it **gives more importance to the arrangments that take less cycles** (i.e. if in the given initial arrangment of the board the machine can win by making one single movement, then this should have a higher weight than a win that takes several cycles to take place).

Finally, having the information of how many wins and losses are related with a machine movement, it takes the movement with **the highest wins-losses ratio**.


# The code behind
Feeling curious? Check the code!

Navigate to ```TicTacToe_AI_VSProject/TicTacToe_AI/Main.cpp``` or click [here](https://github.com/OscarCaro/TicTacToe_AI/blob/master/TicTacToe_AI_VSProject/TicTacToe_AI/Main.cpp)


# How to run it
  1. Navigate to ````TicTacToe_AI_VSProject/Debug/```` or click [here](https://github.com/OscarCaro/TicTacToe_AI/tree/master/TicTacToe_AI_VSProject/Debug).

  2. Download ````TicTacToe_AI.exe```` and run it.
