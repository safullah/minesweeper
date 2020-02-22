/**
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../boards/board_variables.h"

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool is_cell_valid(int row, int col) {
    bool valid = false;
    if ((row >= 0) && (row < ROWS) &&
        (col >= 0) && (col < COLS)) {
        valid = true;
    }
    return valid;
}

// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool is_mine(int row, int col, cell board[ROWS][COLS]) {
    if (board[row][col].ch == '*') {
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

void is_rows_cols_valid() {
    //min row and cols 5
    if (ROWS < 1 || COLS < 1) {
        printf("Error, please enter more than 5 rows and columns!");
        exit(1);
    }
    //highest row and col is 20
    if (ROWS > 20 || COLS > 20) {
        printf("Error, please enter less than 20 rows and columns!");
        exit(1);
    }
}

void is_mines_valid() {
    if (MINES > (ROWS * COLS)) {
        printf("Error, please enter less mines than the number of fields!");
        exit(1);
    }
    //min mines 10
    if (MINES < 1) {
        printf("Error, please enter more than 9 mines!");
        exit(1);
    }
    // highest num of mines is 300
    if (MINES > 300) {
        printf("Error, please enter  less than 300 mines!");
        exit(1);
    }
}

bool is_crd_valid(int x_crd, int y_crd) {
    bool valid = true;
    if (x_crd > ROWS) {
        printf("Please, enter a valid x coordinate.\n");
        valid = false;
    }

    if (y_crd > COLS) {
        printf("Please, enter a valid y coordinate.\n");
        valid = false;
    }
    return valid;
}

bool is_flag(char *str) {
    if (*str == '?') {
        return true;
    } else {
        return false;
    }
}


bool is_answer(char *answer) {
    int cnt = 0;
    char options[4][4] = {"y", "yes", "n", "no"};
    while (*(answer+cnt) != '\0') {
        *(answer+cnt) = (char) tolower(*(answer+cnt));
        cnt++;
    }
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (strcmp(answer, options[i]) == 0)  {
            result =  true;
        }
    }
    return result;
}
