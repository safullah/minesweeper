#### to create a makefile
all: 
	gcc -g -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c -o minespr -lncurses -I.
	
#### gdbserver
/home/saif/dev/minespr/cmake-build-debug/minespr
gdbserver localhost:9090 ./minespr
ps -ef | pgrep gdbserver | xargs kill

#### reading binary
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


#### bugs

##### tasks
- valgrind

#### next
- ncurses has to be linked in order to run the game.

#### thinking process


