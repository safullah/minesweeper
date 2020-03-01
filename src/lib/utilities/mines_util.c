/**
 * \file mines_util.c
 * \brief functins to place and count mines
* Created by saif on 1/14/20.
*/
///

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "mines_util.h"
#include "../board/board.h"
#include "../board/board_variables.h"
#include "../validators/validators.h"

/**
 * \brief places mines in random cells
 *
 * places mines in game board in random manner
 *
 * @param game_brd
 */
void place_mines(cell game_brd[ROWS][COLS]) {
    for (int i = 0; i < MINES;) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (game_brd[x][y].ch != '*') {
            game_brd[x][y].ch = '*';
            i++;
        }
    }
}


/**
 * \brief counts neigbouring mines and save the count in the cell
 * @param game_brd
 */
void count_mines(cell game_brd[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game_brd[i][j].ngh_mines = do_counting(i, j, game_brd);
        }
    }
}

/**
 * \brief counts mines of neighboring cells
 *
 * @param row  row of the cell for which the count is done
 * @param col  col of the cell for which the count is done
 * @param game_brd
 * @return  int      returns the count of neighboring mines
 */
int do_counting(int row, int col, cell game_brd[ROWS][COLS]) {
    int cnt_ngh_mines = 0;
    int neighbors[8][2] = {{-1, -1},
                           {-1, 0},
                           {-1, 1},
                           {0,  -1},
                           {0,  1},
                           {1,  1},
                           {1,  -1},
                           {1,  0}};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 1; ++j) {
            int r = row + neighbors[i][j];
            int c = col + neighbors[i][j + 1];
            if (is_cell_valid(r, c)) {
                if (is_mine(r, c, game_brd)) {
                    cnt_ngh_mines++;
                }
            }
        }
    }
    return cnt_ngh_mines;
}