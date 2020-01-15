/**
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <stdlib.h>

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < SIDE) &&
           (col >= 0) && (col < SIDE);
}

// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool isMine (int row, int col, char board[][MAXSIDE])
{
    if (board[row][col] == '*'){
        return (true);
    } else {
        return (false);
    }
}

void argc_is_valid(int argc) {
    if (argc != 3) {
        fprintf(stderr, "Error, type the size of board and number of mines in the following format\n");
        printf("rowsxcols mines: 10x10 20");
        exit(1);
    }
}