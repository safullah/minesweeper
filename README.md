#Minesweeper by Saifur Rahman
In this project I implement minesweeper.

##Compilation
ncurses has to be linked in order to run the game.

##Execution
Here comes the description how the game is played

####Starting the application
To start the game you execute minespr with the following parameter [rows]x[cols] [mines]
[example: ./minespr 10x10 20] The x between rows and cols is mandatory.
The parameters define the size of the game board and the amount of mines the game will be played with.

During the game you will be asked to enter your move.
To open a cell you specify the coordinates.
Suppose the drawing below is your game board, then the correct format for choosing the cell is: A0 or a0

  A B C
0 - - -
1 - - -
3 - - -

For marking a cell, you type: ?A0 or ?a0 or ? a0

You can also type in the following commands.
exit        quit the game without saving any data
abort       quit the game with saving the current game. You may continue this game later
restart     restart the game

####Read this hint
Under the folder minespr I have a folder called databank, where I save data of players.
To retrieve the absolute path of this folder I use realpath().
In my case the executable minespr is under cmake-build-debug, therefore when I search for databank with realpath()
my parameter looks the following: realpath("./../databank", buf)
I don't know how you will execute this game. You may adjust the parameter for realpath() in order to run the game successfully.

##Completed Tasks
all tasks are implemented


