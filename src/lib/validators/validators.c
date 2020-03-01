/**
 * \file validators.c
 * \brief validation functions
* Created by saif on 1/14/20.
*/
///

#include "validators.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../board/board_variables.h"

/**
 * \brief is cell valid?
 * @param row       row of the cell
 * @param col       col of the cell
 * @return bool
 */
bool is_cell_valid(int row, int col) {
    if ((row >= 0) && (row < ROWS) &&
        (col >= 0) && (col < COLS)) {
        return  true;
    }
    return false;
}

/**
 * \brief is cell a mine
 * @param row   row of the cell
 * @param col   col of the cell
 * @param game_brd
 * @return bool
 */
bool is_mine(int row, int col, cell game_brd[ROWS][COLS]) {
    return game_brd[row][col].ch == '*' ? true : false;
}

/**
 * \brief is row valid
 * @param row
 * @param error
 * @return bool
 */
bool is_row_valid(int row, char *error) {
    if (row < 0) {
        printf("Error, wrong input!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else if (row < 2 ) { /*min row*/
        printf("Enter more than 1 row!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else if (row > 20) { /* max row */
        printf("Enter less than 20 rows!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else {
        return  true;
    }
}

/**
 * \brief is column valid
 * @param col
 * @param error
 * @return bool
 */
bool is_col_valid(int col, char *error) {
    if (col < 0) {
        printf("Error, wrong input!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else if (col < 2 ) { /*min col*/
        printf("Enter more than 1 column!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else if (col > 20) { /*max col*/
        printf("Enter less than 20 columns!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    } else {
        return  true;
    }
}

/**
 * \brief is mine valid
 * @param mine      number of mines
 * @param error     invalid input of player for the number of mine
 * @return bool
 */
bool is_mine_valid(int mine, char *error) {
    if (mine < 0) {
        printf("Error, wrong input!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    }
    if (mine == 0) {
        printf("Enter at least one mine!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    }
    if (mine >= (ROWS * COLS)) {
        printf("Enter less mines than the number of rows * columns!\n");
        printf("your input: \"%s\"\n", error);
        return false;
    }
    return true;
}

/**
 * \brief is coordinate valid
 * @param col
 * @param row
 * @return bool
 */
bool is_crd_valid(int col, int row) {
    bool valid = true;
    if (row > ROWS || row < 0) {
        printf("Please, enter a valid row.\n");
        printf("your input: \"%d\"\n", row);
        valid = false;
    }
    if (col > COLS || row < 0) {
        printf("Please, enter a valid column.\n");
        printf("your input: \"%c\"\n", (char)col);
        valid = false;
    }
    return valid;
}

/**
 * \brief says if player wants to flag or not
 * @param str
 * @return bool
 */
bool is_flag(const char *str) {
    return *str == '?' ? true : false;
}

/**
 * \brief if input is yes, y, no or n then input is correct
 * @param answer
 * @return bool
 */
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
