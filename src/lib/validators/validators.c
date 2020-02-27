/**
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../board/board_variables.h"

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

bool is_row_valid(int row, char *error) {
    if (row < 0) {
        printf("Enter a positive value!\n");
        printf("your input: %s\n", error);
        return false;
    } else if (row < 2 ) {
        printf("Enter more than 1 row!\n");
        printf("your input: %s\n", error);
        return false;
    } else if (row > 20) {
        printf("Enter less than 20 rows!\n");
        printf("your input: %s\n", error);
        return false;
    } else {
        return  true;
    }
}

bool is_col_valid(int col, char *error) {
    if (col < 0) {
        printf("Enter a positive value\n");
        printf("your input: %s\n", error);
        return false;
    } else if (col < 2 ) {
        printf("Enter more than 1 column!\n");
        printf("your input: %s\n", error);
        return false;
    } else if (col > 20) {
        printf("Enter less than 20 columns!\n");
        printf("your input: %s\n", error);
        return false;
    } else {
        return  true;
    }
}

bool is_mine_valid(int mine, char *error) {
    if (mine < 0) {
        printf("Enter a positive value\n");
        return false;
    }
    if (mine == 0) {
        printf("Enter at least one mine!\n");
        return false;
    }
    if (mine >= (ROWS * COLS)) {
        printf("Enter less mines than the number of rows * columns!\n");
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
