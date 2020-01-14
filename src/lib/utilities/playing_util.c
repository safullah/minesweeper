/**
* Created by saif on 1/14/20.
*/
///

#include "playing_util.h"
#include "../validators/validators.h"
#include <stdbool.h>
#include "adjacent_cells.h"
#include "../playing_board/board.h"
#include <stdio.h>
#include "mines_util.h"

// A Function to get the user's move
void makeMove(int *x, int *y)
{
    // Take the input move
    printf("Enter your move, (row, column) -> ");
    scanf("%d %d", x, y);
    return;
}

// A Recursive Fucntion to play the Minesweeper Game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
                         int mines[][2], int row, int col, int *movesLeft)
{

    // Base Case of Recursion
    if (myBoard[row][col] != '-'){
        return (false);
    }

    int i, j;

    // You opened a mine
    // You are going to lose
    if (realBoard[row][col] == '*')
    {
        myBoard[row][col]='*';

        for (i=0; i<MINES; i++){
            myBoard[mines[i][0]][mines[i][1]]='*';
        }

        printBoard (myBoard);
        printf ("\nYou lost!\n");
        return (true) ;
    }

    else
    {
        // Calculate the number of adjacent mines and put it
        // on the board
        int count = countAdjacentMines(row, col, mines, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';

        if (!count)
        {
            /*
            Recur for all 8 adjacent cells

                N.W   N   N.E
                    \ | /
                    \ | /
                W----Cell----E
                    / | \
                    / | \
                S.W   S  S.E

            Cell-->Current Cell (row, col)
            N --> North	 (row-1, col)
            S --> South	 (row+1, col)
            E --> East		 (row, col+1)
            W --> West		 (row, col-1)
            N.E--> North-East (row-1, col+1)
            N.W--> North-West (row-1, col-1)
            S.E--> South-East (row+1, col+1)
            S.W--> South-West (row+1, col-1)
            */

            //----------- 1st Neighbour (North) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col) == true)
            {
                if (isMine (row-1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
            }

            //----------- 2nd Neighbour (South) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col) == true)
            {
                if (isMine (row+1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
            }

            //----------- 3rd Neighbour (East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col+1) == true)
            {
                if (isMine (row, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
            }

            //----------- 4th Neighbour (West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col-1) == true)
            {
                if (isMine (row, col-1, realBoard) == false){

                    playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
                }
            }

            //----------- 5th Neighbour (North-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col+1) == true)
            {
                if (isMine (row-1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
            }

            //----------- 6th Neighbour (North-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col-1) == true)
            {
                if (isMine (row-1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
            }

            //----------- 7th Neighbour (South-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col+1) == true)
            {
                if (isMine (row+1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
            }

            //----------- 8th Neighbour (South-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col-1) == true)
            {
                if (isMine (row+1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
            }
        }

        return (false);
    }
}

// A Function to play Minesweeper game
void playMinesweeper ()
{
    // Initially the game is not over
    bool gameOver = false;

    // Actual Board and My Board
    char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
    int movesLeft = SIDE * SIDE - MINES, x, y;
    int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines.
    init_boards(realBoard, myBoard);
    placeMines (mines, realBoard);

    // You are in the game until you have not opened a mine
    // So keep playing
    int currentMoveIndex = 0;
    while (gameOver == false)
    {
        printf ("Current Status of Board : \n");
        printBoard (myBoard);
        makeMove (&x, &y);

        // This is to guarantee that the first move is
        // always safe
        // If it is the first move of the game
        if (currentMoveIndex == 0)
        {
            // If the first move itself is a mine
            // then we remove the mine from that location
            if (isMine (x, y, realBoard) == true){
                replaceMine (x, y, realBoard);
            }
        }

        currentMoveIndex ++;

        gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

        if ((gameOver == false) && (movesLeft == 0))
        {
            printf ("\nYou won !\n");
            gameOver = true;
        }
    }
    return;
}