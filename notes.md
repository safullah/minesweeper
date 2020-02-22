#### to create a makefile
all: 
	gcc -g -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c -o minespr -lncurses -I.
	
#### gdbserver
/home/saif/dev/minespr/cmake-build-debug/minespr
gdbserver localhost:9090 ./minespr 2x2 1
ps -ef |grep gdbserver
kill -9 <pid>

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

##### tasks
- implement restart
- write doc
- valgrind
- free all mallocs

#### thinking process

#### bugs
- do not allow to open a second time
- when a file is opened it has to be closed
take care of exit, abort or any other error where the game is killed

#### TODO
free memory
- implement -help or -h

#### next
do testing!!!
