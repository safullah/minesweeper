/**
* Created by saif on 1/14/20.
*/
///

#include "mines_util.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../boards/board.h"
#include "../boards/board_variables.h"

void place_mines(int mines[][2], cell hidden_brd[ROWS][COLS]) {
    bool mark[ROWS * COLS];
    memset(mark, false, sizeof(mark));
    // Continue until all random mines have been created.
    srand(time(NULL));
    for (int i = 0; i < MINES;) {
        int random = rand() % (ROWS * COLS) + 1;
        int x = random / ROWS;
        int y = random % COLS;
        if (mark[random] == false) {
            mines[i][0] = x;
            mines[i][1] = y;
            hidden_brd[mines[i][0]][mines[i][1]].ch = '*';
            mark[random] = true;
            i++;
        }
    }
}

void replace_mine(int row, int col, cell board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].ch != '*') {
                board[i][j].ch = '*';
                board[row][col].ch = '-';
            }
        }
    }
}