/**
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <stdlib.h>

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool is_cell_valid(int row, int col) {
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < SIDE) &&
           (col >= 0) && (col < SIDE);
}

// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool is_mine(int row, int col, char **board) {
    if (board[row][col] == '*') {
        return (true);
    } else {
        return (false);
    }
}

void is_argc_valid(int argc) {
    if (argc != 3) {
        printf("Error, type the size of board and number of mines in the following format:\n"
                        "  rowsxcols mines: 10x10 20");
        exit(1);
    }
}

void is_rows_cols_valid(int rows, int cols) {

    //min row and cols 5
    if (rows < 6 || cols < 6) {
        printf("Error, please enter more than 5 rows and columns!");
        exit(1);
    }
    //highest row and col is 20
    if (rows > 21 || cols > 21) {
        printf("Error, please enter less than 20 rows and columns!");
        exit(1);
    }
}

void is_mines_valid(int mines, int rows, int cols) {

    if (mines > (rows * cols)) {
        printf("Error, please enter less mines than the number of fields!");
        exit(1);
    }
    //min mines 10
    if (mines < 11) {
        printf( "Error, please enter more than 10 mines!");
        exit(1);
    }
    // highest num of mines is 300
    if (mines > 301) {
        printf("Error, please enter  less than 300 mines!");
        exit(1);
    }
}

bool is_coordinate_valid(int x_crd, int y_crd, int rows, int cols) {
    bool valid = true;
    if (x_crd > rows) {

        printf("Please, enter a valid x coordinate.\n");
        valid = false;
    }

    if (y_crd > cols) {
        printf("Please, enter a valid y coordinate.\n");
        valid = false;
    }
    return valid;
}