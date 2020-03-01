##Minesweeper by Saifur Rahman
In this project I implement minesweeper in C.

##Compilation
You can use my executable if you don't want to write a make file. <br>
My executable is minespr/cmake-build-debug/minespr <br>
If you want to make a makefile maybe my CMakeLists.txt could be helpful.


##Execution
Run the game with cmake-build-debug/minespr -h to see help instructions.<br>
If you are in the minepsr directory, then start the game from there.<br>
Otherwise please first cd to minespr directory and then start the game.<br>
This game can be started form anywhere, but if you want to be fast, start as recommended.<br>
 
The game can be started with or without any parameters<br>
with parameter:<br>
cmake-build-debug/minespr -n saif -r10 -c10 -m20<br>

no parameter:<br>
cmake-build-debug/minespr<br>
After the game is started, you will be prompted to enter the required parameters<br>

##Starting the application
cmake-build-debug/minespr -n saif -r10 -c10 -m20<br>
-n name<br>
-r row<br>
-c cols<br>
-m mines<br>

You will be prompted to enter your move.<br>
To open a cell you specify coordinates.<br>
First comes column and then the row.<br>
example: A5<br>

To mark a mine first type "?" and then enter the coordinated of the cell.<br>
example: ?A5
You cam also type in small letter. Capital and small letters are treated equally.<br>


You can also type in the following commands.<br>
exit        quit the game without saving any data<br>
abort       quit the game with saving the current game. You may continue this game later<br>
restart     restart the game<br>
help        opens help instructions<br>

##Completed Tasks
all tasks are implemented except ncurses


