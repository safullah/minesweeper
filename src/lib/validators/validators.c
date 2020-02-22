/**
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../board/board_variables.h"

// A Utility Function to check whether given cell (row, col) is a valid cell or not
bool is_cell_valid(int row, int col) {
    if ((row >= 0) && (row < ROWS) &&
        (col >= 0) && (col < COLS)) {
        return  true;
    }
    return false;
}
bool is_mine(int row, int col, cell game_brd[ROWS][COLS]) {
    return game_brd[row][col].ch == '*' ? true : false;
}

bool is_rows_cols_valid() {
    if (ROWS < 0 || COLS < 0) {
        printf("Enter positive values\n");
        return false;
    }
    //min row and cols 5
    if (ROWS < 1 || COLS < 1) {
        printf("Error, please enter more than 5 rows and columns!");
        return false;
    }
    //highest row and col is 20
    if (ROWS > 20 || COLS > 20) {
        printf("Error, please enter less than 20 rows and columns!");
        return false;
    }
    return true;
}

bool is_mines_valid() {
    if (MINES < 0) {
        printf("Enter positive values\n");
        return false;
    }
    if (MINES > (ROWS * COLS)) {
        printf("Error, please enter less mines than the number of fields!\n");
        return false;
    }
    if (MINES < 1) { //min mines 10
        printf("Error, please enter more than 9 mines!\n");
        return false;
    }
    if (MINES > 300) { // highest num of mines is 300
        printf("Error, please enter  less than 300 mines!\n");
        return false;
    }
    return true;
}

bool is_crd_valid(int col, int row) {
    bool valid = true;
    if (row > ROWS || row < 0) {
        printf("Please, enter a valid row.\n");
        valid = false;
    }
    if (col > COLS || row < 0) {
        printf("Please, enter a valid column.\n");
        valid = false;
    }
    return valid;
}

bool is_flag(const char *str) {
    return *str == '?' ? true : false;
}

bool is_answer(char *answer) {
    int cnt = 0;
    char options[4][4] = {"y", "yes", "n", "no"};
    while (*(answer + cnt) != '\0') {
        *(answer + cnt) = (char) tolower(*(answer + cnt));
        cnt++;
    }
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (strcmp(answer, options[i]) == 0) {
            result = true;
        }
    }
    return result;
}
