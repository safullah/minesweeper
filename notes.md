Here I save commands that I need often.

#### to create a makefile
all: 
	gcc -g -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c -o minespr -lncurses -I.


#### gdbserver

/home/saif/dev/minespr/cmake-build-debug/minespr
gdbserver localhost:9090 ./minespr
ps -ef |grep gdbserver
kill -9 <pid>

#### get absolute path of a file
readlink -f file.txt

##### doxygen
type in terminal "doxywizard"
renaming in clion and doxy shift+F6
doxy doc view ctrl+Q

##### tasksks
- error handling
- valgrand