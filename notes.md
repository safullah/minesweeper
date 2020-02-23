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


#### bugs
- do not allow to open a second time
- when a file is opened it has to be closed
  take care of exit, abort or any other error where the game is killed

##### tasks
- valgrind
- write doc
- free all mallocs
- free memory
- implement -help or -h
- Explain how your application is supposed to be started.
  This should be roughly resembling the common usage message printed by command line programs.
  If your application prints such a message when -h is supplied as parameter you can leave this out.

Give a quick overview about the user inputs your application awaits at runtime.
If your application is completely self-explanatory (i.e., if it clearly prints when the user is supposed to enter something and the required format) you can leave this out.

#### next
- write doc
- do testing!!!

#### thinking process
findout how to use doxygen 
comment one file
check result