Here I save commands that I need often.

#### to create a makefile
all: 
	gcc -g -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c -o minespr -lncurses -I.


#### gdbserver
/home/saif/dev/minespr/cmake-build-debug/minespr
gdbserver localhost:9090 ./minespr
ps -ef |grep gdbserver
kill -9 <pid>

od -Ax -t x1z filename
od -c book.dat 


#### get absolute path of a file
readlink -f file.txt

##### doxygen
type in terminal "doxywizard"
renaming in clion and doxy shift+F6
doxy doc view ctrl+Q

#### keep in mind
- error handling

##### tasks
- implement restart
- just one place that throws the error!
- write doc
- valgrind
- free all mallocs
- task 6:
each player gets two board, mines as well
when abort save these boards and mines
when starting a new game ask the player if he wants to load the game
if yes read the assign the boards and mines to BOARDS and MINES

-check count mines

#### thinking process

#### bugs
- do not allow to open a second time
- show mine if flagged

- when a file is opened it has to be closed
take car of exit, abort or any other error where the game is killed

#### TODO
free memory

#### next
refactor load_player
do testing!!!
